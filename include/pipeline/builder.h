#ifndef __PIPELINE_BUILDER_H__
#define __PIPELINE_BUILDER_H__

#include "aggregated_ast/index.h"


namespace PAFL
{
class BuilderBase
{
public:
    virtual aggregated_ast::Ast* build(const std::filesystem::path& source_path) = 0;
};



class CppBuilder : public BuilderBase
{
public:
    CppBuilder(const std::filesystem::path& source_dir) : _include_dir(aggregated_ast::CppAst::collectIncludeDir(source_dir)) {}
    aggregated_ast::Ast* build(const std::filesystem::path& source_path) override
    {
        return new aggregated_ast::CppAst(source_path, _include_dir);
    }
private:
    const std::string _include_dir;
};



class PyBuilder : public BuilderBase
{
public:
    aggregated_ast::Ast* build(const std::filesystem::path& source_path) override
    {
        return new aggregated_ast::PyAst(source_path);
    }
};
}
#endif
