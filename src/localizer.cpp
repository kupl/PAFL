#include "model/localizer.h"

namespace PAFL
{
void Localizer::localize(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, float coef) const
{
    if (!_isFresh)
        _localize(suite, graphs, coef * _maturity / _updater_num);
}



void Localizer::train(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, const TestSuite::fault_set_t& faults, float coef, size_t thread_num)
{
    if (_isFresh)
        _isFresh = false;
    _maturity += coef / 2;
    if (_maturity > 1.0f)
        _maturity = 1.0f;

    // base first ranking
    suite->setSusToBase();
    _localize(suite, graphs, 1.0f);
    suite->rank();
    auto base_fr = suite->getFirstRanking(faults);

    // Collect buggy nodes
    std::vector<const stmt_graph::Node*> buggy_nodes;
    for (auto item : faults) {

        auto node_vector = graphs.at(item.first)->at(item.second);
        if (node_vector)
            for (auto node : *node_vector)
                buggy_nodes.push_back(node);
    }

    // Make the future suspiciousness values
    suite->setSusToBase();
    auto mutants(_updater.makeMutant(buggy_nodes, 0.0f, 1.0f));
    // Single thread
    if (thread_num <= 1)
        for (auto& mut : mutants)
            _trainMutant(suite, graphs, faults, mut, base_fr, coef);
    // Multi threads
    else {

        BS::thread_pool pool(thread_num);
        pool.detach_loop<size_t>(0, mutants.size(),
            [this, suite, &graphs, &faults, &mutants, base_fr, coef](size_t i)
            {
                _trainMutant(suite, graphs, faults, mutants[i], base_fr, coef);
            });
        pool.wait();
    }
    
    // Assign new suspiciousness values
    for (auto& mut : mutants)
        mut.block->setValue(mut.token, mut.mutated_value);
    _updater.eraseIf(0.1f);
}



void Localizer::_localize(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, float coef) const
{
    std::vector<std::pair<TestSuite::Ranking*, float>> future;
    future.reserve(suite->size());

    for (TestSuite::index_t index = 0; index != suite->maxIndex(); ++index) {
        
        auto& file = suite->content().at(index);
        for (auto& node : *graphs.at(index)) {

            // If node is not coverable, continue
            if (!node.coverable)
                continue;

            float node_value = -1.0f;
            for (auto line = node.begin; line <= node.end; ++line)
                if (file.contains(line)) {

                    auto ranking_ptr = file.at(line).ranking_ptr;
                    // If the line is covered by a failing test case
                    if (ranking_ptr->base_sus > 0.0f) {
                        
                        // Init node's value
                        if (node_value < 0.0f)
                            node_value = _updater.max(&node);
                        // Reservation of update of suspiciousness value with node's value
                        future.emplace_back(ranking_ptr, ranking_ptr->sus + coef * node_value);
                    }
                }
        }
    }

    // Update all suspiciousness values (maximum)
    for (auto& item : future)
        if (item.first->sus < item.second)
            item.first->sus = item.second;
}



void Localizer::_localize(TestSuite::Copy& suite_copy, const stmt_graph::Graph::vector_t& graphs, float coef, const Updater::Mutant& mutant) const
{
    std::vector<std::pair<TestSuite::Ranking*, float>> future;
    future.reserve(suite_copy.ranking.size());

    for (TestSuite::index_t index = 0; index != suite_copy.content.size(); ++index) {
        
        auto& file = suite_copy.content.at(index);
        for (auto& node : *graphs.at(index)) {

            // If node is not coverable, continue
            if (!node.coverable)
                continue;
                
            float node_value = -1.0f;
            for (auto line = node.begin; line <= node.end; ++line)
                if (file.contains(line)) {

                    auto ranking_ptr = file.at(line);
                    // If the line is covered by a failing test case
                    if (ranking_ptr->base_sus > 0.0f) {
                        
                        // Init node's value
                        if (node_value < 0.0f)
                            node_value = _updater.max(&node, mutant);
                        // Reservation of update of suspiciousness value with node's value
                        future.emplace_back(ranking_ptr, ranking_ptr->sus + coef * node_value);
                    }
                }
        }
    }

    // Update all suspiciousness values (maximum)
    for (auto& item : future)
        if (item.first->sus < item.second)
            item.first->sus = item.second;
}



void Localizer::_trainMutant(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, const TestSuite::fault_set_t& faults, Updater::Mutant& mutant, float base_fr, float coef) const
{
    // new first ranking
    TestSuite::Copy suite_copy(*suite);
    _localize(suite_copy, graphs, 1.0f, mutant);
    suite_copy.rank();
    auto new_fr = suite_copy.getFirstRanking(faults);

    // Positive update
    if (new_fr < base_fr) {

        auto grad = _gradientFormula(base_fr, new_fr, coef, (1.0f / _updater_num));
        mutant.mutated_value = mutant.original_value + (1.0f - mutant.original_value) * grad;
    }

    // Negative update
    else if (new_fr > base_fr) {

        auto grad = _gradientFormula(new_fr, base_fr, coef, (1.0f / _updater_num));
        mutant.mutated_value = mutant.original_value * (mutant.original_value * grad + (1.0f - grad));
    }
    else
        mutant.mutated_value = mutant.original_value;
}
}
