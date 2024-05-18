#ifndef __PIPELINE_BUILDER_H__
#define __PIPELINE_BUILDER_H__

#include "stmt_graph/index.h"


namespace PAFL
{
class BuilderBase
{
public:
    virtual stmt_graph::Graph* build(const std::filesystem::path& source_path) = 0;
};



class CppBuilder : public BuilderBase
{
public:
    CppBuilder(const std::filesystem::path& source_dir) : _include_dir(stmt_graph::CppGraph::collectIncludeDir(source_dir)) {}
    stmt_graph::Graph* build(const std::filesystem::path& source_path) override
    {
        return new stmt_graph::CppGraph(source_path, _include_dir);
    }
private:
    const std::string _include_dir;
};



class PyBuilder : public BuilderBase
{
public:
    stmt_graph::Graph* build(const std::filesystem::path& source_path) override
    {
        return new stmt_graph::PyGraph(source_path);
    }
};
}
#endif
