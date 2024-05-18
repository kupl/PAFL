#ifndef __MODEL_LOCALIZER_H__
#define __MODEL_LOCALIZER_H__

#include <algorithm>
#include <thread_pool/BS_thread_pool.hpp>

#include "testsuite/testsuite.h"
#include "stmt_graph/graph.h"
#include "model/updater.h"


namespace PAFL
{
class Localizer
{
public:
    static constexpr float MAX_WEIGHT = 1.0f;

public:
    Localizer() : _id(0), _updater(Updater::Depth{false, 0, 0, 0, 0}), _updater_num(0), _isFresh(true), _maturity(0.0f) {}
    Localizer(Updater::Depth depth, size_t updater_num, size_t id) : _updater(depth), _updater_num(updater_num), _id(id), _isFresh(true), _maturity(0.0f) {}

    void localize(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, float coef) const;
    void train(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, const TestSuite::fault_set_t& faults,
               float coef, size_t thread_num = 1);

    size_t getID() const                                    { return _id; }
    std::string toString() const                            { return _updater.toString(); }
    template <class Archive> void serialize(Archive& ar)    { ar(_updater, _updater_num, _isFresh, _id, _maturity); }

private:
    void _localize(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, float coef) const;
    void _localize(TestSuite::Copy& suite_copy, const stmt_graph::Graph::vector_t& graphs, float coef, const Updater::Mutant& mutant) const;
    void _trainMutant(TestSuite* suite, const stmt_graph::Graph::vector_t& graphs, const TestSuite::fault_set_t& faults,
                      Updater::Mutant& mutant, float base_fr, float coef) const;

    static constexpr float _gradientFormula(size_t base_ranking, size_t new_ranking, float coef, float max = 1.0f) {
        float grad = coef * (base_ranking - new_ranking) / (float)base_ranking; return grad > max ? max : grad;
    }

private:
    size_t _id;
    Updater _updater;
    size_t _updater_num;
    bool _isFresh;
    float _maturity;
};
}
#endif
