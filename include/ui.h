#ifndef __UI_H__
#define __UI_H__

#include <iostream>
#include <cstdio>
#include <vector>

#include "argparser.h"
#include "config.h"
#include "method.h"
#include "normalizer.h"
#include "rapidjson.h"


namespace PAFL
{
class UI
{
public:
    using method_list = std::list<std::unique_ptr<Method>>;
    using docs = std::list<std::pair<rapidjson::Document, bool>>;

public:
    UI(int argc, char *argv[]);

    const std::string& getProject() const                   { return _project; }
    PrgLang getLanguage() const                             { return _pl; }
    size_t numVersion() const                               { return _version.size(); }
    const method_list& getMethodList() const                { return _method; }
    const Normalizer* getNormalizer() const                 { return _normalizer.get(); }

    const fs::path& getDirectoryPath() const                { return _parser.getDirectoryPath(); }
    const fs::path& getProjectPath(size_t iter) const       { return _src_path[iter]; }
    const fault_loc& getFaultLocation(size_t iter) const    { return _faults[iter]; }
    size_t getVersion(size_t iter) const                    { return _version[iter]; }
    const string_set& getExtensions() const                 { return _extensions; }

    bool hasDebugger() const                                { return _debug; }
    bool hasCache() const                                   { return _cache; }
    bool isProjectAware() const                             { return _is_project_aware; }

    fs::path getFilePath(size_t iter, const std::string& file) const;
    docs getCoverageList(size_t iter) const;


private:
    void _readIn();
    void _setContainer();
    void _throwInvalidInput(const std::string& msg) const       { std::cerr << msg; throw std::invalid_argument(msg); }
    void _assert(bool condition, const std::string& msg) const  { if (!condition) _throwInvalidInput(msg); }
    static std::list<fs::path> _collectDir(const fs::path& path, std::string key);

private:
    const ArgParser _parser;
    std::string _project;
    PrgLang _pl;
    std::vector<size_t> _version;
    std::list<fs::path> _sub_dir;
    string_set _extensions;

    method_list _method;
    std::unique_ptr<Normalizer> _normalizer;

    fs::path _project_path;
    fs::path _testsuite_path;
    fs::path _oracle_path;

    bool _debug;
    bool _cache;
    bool _is_project_aware;

    Config _config;
    std::vector<fs::path> _src_path;
    std::vector<fault_loc> _faults;
};
}
#endif
