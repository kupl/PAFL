#include "model/localizer.h"

namespace PAFL
{
void Localizer::train(TestSuite* suite, const aggregated_ast::Ast::vector_t& trees, const TestSuite::fault_set_t& faults,
                      float coef, size_t thread_num)
{
    if (_isFresh)
        _isFresh = false;
    else if (_maturity <= 0.1f)
        _maturity = 0.1f;
    else {

        _maturity += 0.2f;
        if (_maturity > 1.0f)
            _maturity = 1.0f;
    }

    // Collect buggy nodes
    std::vector<const aggregated_ast::Node*> buggy_nodes;
    for (auto item : faults) {

        auto node_vector = trees.at(item.first)->at(item.second);
        if (node_vector)
            for (auto node : *node_vector)
                buggy_nodes.push_back(node);
    }

    // Get the base suspiciousness values
    suite->setSusToBase();
    _localize(suite, trees, 1.0f);
    suite->rank();
    auto base_fr = suite->getFirstRanking(faults);

    // Make the future suspiciousness values
    suite->setSusToBase();
    auto mutants(_updater.makeMutant(buggy_nodes, 0.0f, MAX_WEIGHT));

    // Single thread
    if (thread_num <= 1)
        for (auto& mut : mutants)
            _trainMutant(suite, trees, faults, mut, base_fr, coef);
    
    // Multi thread
    else {

        BS::thread_pool pool(thread_num);
        pool.detach_loop<size_t>(0, mutants.size(),
            [this, suite, &trees, &faults, &mutants, base_fr, coef](size_t i)
            {
                _trainMutant(suite, trees, faults, mutants[i], base_fr, coef);
            });
        pool.wait();
    }

    // Update the suspiciousness values
    for (auto& mut : mutants)
        mut.block->setValue(mut.token, mut.mutated_value);
    _updater.eraseIf(0.1f);

    // If the updater is empty, reset the maturity
    if (_updater.empty())
        _maturity = 0.0f;
}



void Localizer::_localize(TestSuite* suite, const aggregated_ast::Ast::vector_t& trees, float coef) const
{
    std::vector<std::pair<TestSuite::Ranking*, float>> future;
    future.reserve(suite->size());

    for (TestSuite::index_t index = 0; index != suite->maxIndex(); ++index) {
        
        auto& file = suite->content().at(index);
        for (auto& node : *trees.at(index)) {

            // If node is not coverable, continue
            if (!node.coverable)
                continue;

            float node_value = -1.0f;
            for (auto line = node.begin; line <= node.end; ++line)
                if (file.contains(line)) {

                    auto param = file.at(line);
                    // If the line is covered by a failing test case
                    if (param.Ncf) {
                        
                        // Init node's value
                        if (node_value < 0.0f)
                            node_value = _updater.max(&node);
                        // Reservation of update of suspiciousness value with node's value
                        future.emplace_back(param.ranking_ptr, param.ranking_ptr->sus + coef * node_value);
                    }
                }
        }
    }

    // Update all suspiciousness values (maximum)
    for (auto& item : future)
        if (item.first->sus < item.second)
            item.first->sus = item.second;
}



void Localizer::_localize(TestSuite::Copy& suite_copy, const aggregated_ast::Ast::vector_t& trees, float coef, const Updater::Mutant& mutant) const
{
    std::vector<std::pair<TestSuite::Ranking*, float>> future;
    future.reserve(suite_copy.ranking.size());

    for (TestSuite::index_t index = 0; index != suite_copy.content.size(); ++index) {
        
        auto& file = suite_copy.content.at(index);
        for (auto& node : *trees.at(index)) {

            // If node is not coverable, continue
            if (!node.coverable)
                continue;
                
            float node_value = -1.0f;
            for (auto line = node.begin; line <= node.end; ++line)
                if (file.contains(line)) {

                    auto param = file.at(line);
                    // If the line is covered by a failing test case
                    if (param.Ncf) {
                        
                        // Init node's value
                        if (node_value < 0.0f)
                            node_value = _updater.max(&node, mutant);
                        // Reservation of update of suspiciousness value with node's value
                        future.emplace_back(param.ranking_ptr, param.ranking_ptr->sus + coef * node_value);
                    }
                }
        }
    }

    // Update all suspiciousness values (maximum)
    for (auto& item : future)
        if (item.first->sus < item.second)
            item.first->sus = item.second;
}



void Localizer::_trainMutant(TestSuite* suite, const aggregated_ast::Ast::vector_t& trees, const TestSuite::fault_set_t& faults, Updater::Mutant& mutant, float base_fr, float coef) const
{
    // new first ranking
    TestSuite::Copy suite_copy(*suite);
    _localize(suite_copy, trees, 1.0f, mutant);
    suite_copy.rank();
    auto new_fr = suite_copy.getFirstRanking(faults);

    // Positive update
    if (new_fr < base_fr) {

        auto grad = _gradientFormula(base_fr, new_fr, coef, 1.0f / _updater_num);
        mutant.mutated_value = mutant.original_value + (mutant.mutated_value - mutant.original_value) * grad;
    }

    // Negative update
    else if (new_fr > base_fr) {

        auto grad = _gradientFormula(new_fr, base_fr, coef, 1.0f / _updater_num);
        mutant.mutated_value = mutant.original_value * (mutant.original_value * grad + (mutant.mutated_value - grad));
    }
    else
        mutant.mutated_value = mutant.original_value;
}
}
