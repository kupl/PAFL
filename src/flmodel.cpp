#include "model/flmodel.h"

namespace PAFL
{
std::vector<std::pair<Localizer*, float>> FLModel::localize(TestSuite* suite, const aggregated_ast::Ast::vector_t& trees)
{
    auto embedding(_embed(suite->getTestCases(), trees));
    auto similar_embeddings(_chooseEmbedding(embedding, TOP_K));
    for (auto embd : similar_embeddings)
        embd.first->localize(suite, trees, embd.second);

    return similar_embeddings;
}



std::vector<std::pair<Localizer*, float>> FLModel::train(TestSuite* suite, const aggregated_ast::Ast::vector_t& trees, const TestSuite::fault_set_t& faults, size_t thread_num)
{
    // Train existed localizers
    auto embedding(_embed(suite->getTestCases(), trees));
    auto similar_embeddings(_chooseEmbedding(embedding, TOP_K));
    for (auto embd : similar_embeddings)
        embd.first->train(suite, trees, faults, embd.second, thread_num);
    auto& new_embedding = _embedding_list.emplace_back(std::move(embedding));

    // Train new localizer
    new_embedding.localizer = std::make_unique<Localizer>(_depth, TOP_K, ++_id);
    new_embedding.localizer->train(suite, trees, faults, 1.0f, thread_num);
    similar_embeddings.emplace_back(new_embedding.localizer.get(), 0.0f);
    return similar_embeddings;
}



std::string FLModel::convertResultToString(const std::vector<std::pair<Localizer*, float>>& result)
{
    std::string buffer;
    buffer.reserve(StringEditor::MiB(1));

    for (auto item : result) {

        StringEditor::append(buffer.append("---[ ID: "), item.first->getID()).append(", weight: ");
        StringEditor::append(buffer, item.second).append(" ]---\n");
        buffer.append(item.first->toString()).append("\n\n");
    }
    StringEditor::eraseEndIf(buffer, "\n\n");
    return buffer;
}



FLModel::Embedding FLModel::_embed(const std::vector<TestSuite::TestCase>& cases, const aggregated_ast::Ast::vector_t& trees)
{
    Embedding embedding;
    std::unordered_map<std::string, uint64_t> passing;
    std::unordered_map<std::string, uint64_t> failing;
    uint64_t max_passing = 0;
    uint64_t max_failing = 0;
    passing.reserve(_dimension.size() * 2);
    failing.reserve(_dimension.size() * 2);

    // Count every passing, failing test case
    for (auto& testcase : cases) {

        auto& vector_ref = testcase.is_passed ? passing : failing;
        auto& max_ref = testcase.is_passed ? max_passing : max_failing;

        for (auto item : testcase.lines) {

            auto node_vector = trees.at(item.first)->at(item.second);
            if (node_vector)
                for (auto node : *node_vector)
                    for (auto& tok : node->token_vector) {

                        _dimension.insert(tok);
                        uint64_t new_max = vector_ref.contains(tok) ? (vector_ref.at(tok) += 1) : (vector_ref.emplace(tok, 1).second);
                        if (new_max > max_ref)
                            max_ref = new_max;
                    }
        }
    }

    // Normalize count
    embedding.passing.reserve(passing.size());
    embedding.failing.reserve(failing.size());
    for (auto& item : passing)
        embedding.passing.emplace(item.first, std::sqrt(item.second / float(max_passing)));
    for (auto& item : failing)
        embedding.failing.emplace(item.first, std::sqrt(item.second / float(max_failing)));
    return embedding;
}



float FLModel::_similarity(const Embedding& feature, const Embedding& current) const
{
    float between_passing = 0.0f;
    float between_failing = 0.0f;

    // Calculate distance
    for (auto& tok : _dimension) {

        float feature_val = feature.failing.contains(tok) ? feature.failing.at(tok) : 0.0f;
        float failing_val = current.failing.contains(tok) ? current.failing.at(tok) : 0.0f;
        float passing_val = current.passing.contains(tok) ? current.passing.at(tok) : 0.0f;
        
        {// Distance between feature's failing and current's passing
            float diff = feature_val - passing_val;
            between_passing += diff * diff;
        }
        {// Distance between feature's failing and current's failing
            float diff = feature_val - failing_val;
            between_failing += diff * diff;
        }
    }

    // Calculate similarity
    between_passing = std::sqrt(between_passing);
    between_failing = std::sqrt(between_failing);
    return between_passing > 0.0f ? (between_passing - between_failing) / between_passing : -std::numeric_limits<float>::infinity();
}



std::vector<std::pair<Localizer*, float>> FLModel::_chooseEmbedding(const Embedding& current, size_t top_k) const
{
    std::vector<std::pair<Localizer*, float>> ret;
    ret.reserve(_embedding_list.size() + 1);

    // Calculate similarity
    for (auto& embedding : _embedding_list) {

        auto sim = _similarity(embedding, current);
        if (sim > SIMILARITY_THRESHOLD)
            ret.emplace_back(embedding.localizer.get(), sim);
    }
    if (ret.size() == 0)
        return ret;

    // Sort
    std::sort(ret.begin(), ret.end(),
        [](decltype(ret)::value_type lhs, decltype(ret)::value_type rhs) {
            return lhs.second > rhs.second;
        });
 
    // Chose Top-K embeddings
    if (ret.size() > top_k)
        ret.erase(ret.begin() + top_k, ret.end());
    return ret;
}
}
