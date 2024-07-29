#ifndef __MODEL_FLMODEL_H__
#define __MODEL_FLMODEL_H__

#include <cmath>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/string.hpp>

#include "model/localizer.h"


namespace PAFL
{
class FLModel
{
public:
    static constexpr size_t TOP_K = 3;
    static constexpr float SIMILARITY_THRESHOLD = 0.01f;

    using feature_vector_t = std::unordered_map<std::string, float>;
    struct Embedding
    {
        feature_vector_t passing, failing; std::unique_ptr<Localizer> localizer;
        template <class Archive> void serialize(Archive& ar) { ar(passing, failing, localizer); }
    };
    
public:
    FLModel() : _depth{true, 1, 1, 1, 1} { _dimension.reserve(1024); }

    std::vector<std::pair<Localizer*, float>> localize(TestSuite* suite, const aggregated_ast::Ast::vector_t& trees);
    std::vector<std::pair<Localizer*, float>> train(TestSuite* suite, const aggregated_ast::Ast::vector_t& trees, const TestSuite::fault_set_t& faults, size_t thread_num = 1);

    size_t getMaxID() const { return _id; }
    void setUpdaterDepth(Updater::Depth depth)              { _depth = depth; }

    template <class Archive> void serialize(Archive& ar)    { ar(_dimension, _embedding_list, _id, _depth.target_depth, _depth.pred_depth, _depth.succ_depth, _depth.parent_depth, _depth.child_depth); }
    static std::string convertResultToString(const std::vector<std::pair<Localizer*, float>>& result);

private:
    Embedding _embed(const std::vector<TestSuite::TestCase>& cases, const aggregated_ast::Ast::vector_t& trees);
    float _similarity(const Embedding& feature, const Embedding& current) const;
    std::vector<std::pair<Localizer*, float>> _chooseEmbedding(const Embedding& current, size_t top_k) const;

private:
    std::unordered_set<std::string> _dimension;
    std::list<Embedding> _embedding_list;
    Updater::Depth _depth;
    size_t _id = 0;
};
}
#endif
