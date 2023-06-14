#ifndef __COV_h__
#define __COV_h__

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <charconv>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "type.h"

using namespace rapidjson;



namespace PAFL
{
using count_type = unsigned short;
using index_type = unsigned short;

struct ranking_info { index_type index; line_type line; float ochiai_sus, sus; line_type ranking; };
struct param { count_type Ncf, Ncs; ranking_info* ptr_ranking; };
using dict = std::unordered_map<line_type, param>;
using file2index_type = std::unordered_map<std::string, index_type>;



class Coverage
{
public:
    Coverage() : _is_initialized(false), _fail(0) {}
    Coverage(const Coverage& rhs);
    void AddTestCase(const Document& d, bool is_successed);
    void CalculateSus();
    const std::list<ranking_info>& Rank();
    void Save(std::ofstream& ofs) const;

    index_type GetIndexFromFile(const std::string& file)
        { return _file2index.contains(file) ? _file2index[file] : throw std::out_of_range(file + " is out of range"); }
    index_type MaxIndex() const
        { return _index2file.size(); }
    std::string GetFileFromIndex(index_type idx) const
        { return _index2file[idx]; }
    float GetOchiaiSus(index_type idx, line_type line)
        { return _line_param[idx].contains(line) ? _line_param[idx][line].ptr_ranking->ochiai_sus : 0.0f; }\

    void _write(std::ofstream& ofs);
    void _read(std::ifstream& ifs);

    decltype(auto) cbegin(index_type idx) const
        { return _line_param[idx].cbegin(); }
    decltype(auto) cend(index_type idx)  const
        { return _line_param[idx].cend(); }


protected:
    std::vector<dict> _line_param;
    std::list<ranking_info> _ranking;
    

private:
    bool _is_initialized;
    count_type _fail;
    count_type _success;

    std::vector<std::string> _index2file;
    file2index_type _file2index;
};
}






namespace PAFL
{
Coverage::Coverage(const Coverage& rhs) :
    _line_param(rhs._line_param), _ranking(rhs._ranking), _is_initialized(rhs._is_initialized), _fail(rhs._fail), _index2file(rhs._index2file), _file2index(rhs._file2index)
{
    for (auto& iter : _ranking)
        _line_param[iter.index][iter.line].ptr_ranking = &iter;
}



void Coverage::AddTestCase(const Document& d, bool is_successed)
{
    const auto& json_files = d["files"].GetArray();
    const auto sizeof_files = json_files.Size();
    
    // Reserve containers' capacity
    if (!_is_initialized) {
        
        _file2index.reserve(sizeof_files + 4);
        _index2file.reserve(sizeof_files + 4);
        _line_param.reserve(sizeof_files + 4);
        _is_initialized = true;
    }
    is_successed ? _success++ : _fail++;
    

    for (SizeType i = 0; i != sizeof_files; ++i) {
        
        const auto& json_file = json_files[i].GetObject();
        const auto& json_lines = json_file["lines"].GetArray();
        std::string key(json_file["file"].GetString());
        
        // If the file is a test, ignore
        if (key.rfind("test/", 0) == 0 || key.rfind("tests/", 0) == 0 || json_lines.Size() == 0)
            continue;
        
        // "file" is not in filelist --> initialize
        if (std::find(_index2file.begin(), _index2file.end(), key) == _index2file.end()) {
            
            auto index_now = static_cast<index_type>(_index2file.size());
            _file2index.emplace(key, index_now);
            _index2file.emplace_back(key);
            _line_param.emplace_back();
            
            for (SizeType j = 0; j != json_lines.Size(); j++) {
                
                const auto& json_line = json_lines[j].GetObject();
                if (!json_line["gcovr/noncode"].GetBool()) {
                    
                    line_type line_now = json_line["line_number"].GetUint();
                    _ranking.push_back(ranking_info{ index_now, line_now, 0.0f, 0.0f, 0 });

                    auto val = json_line["count"].GetUint64() ? (is_successed ? param{ 0, 1, &*_ranking.rbegin() } : param{ 1, 0, &*_ranking.rbegin() } ) : param{ 0, 0, &*_ranking.rbegin() };
                    _line_param[index_now].emplace(line_now, val);
                }
            }
        }
        
        
        // "file" is in filelist
        else
            for (SizeType j = 0; j != json_lines.Size(); j++) {
                
                const auto& json_line = json_lines[j].GetObject();
                if (!json_line["gcovr/noncode"].GetBool()) {
                    
                    index_type index_now(_file2index[key]);
                    line_type line_now = json_line["line_number"].GetUint();

                    // line is not in _line_param
                    if (!_line_param[index_now].contains(line_now)) {
                        
                        auto& ptr = _ranking.emplace_back(ranking_info{ index_now, line_now, 0.0f, 0.0f, 0 });
                        auto val = json_line["count"].GetUint64() ? (is_successed ? param{ 0, 1, &ptr } : param{ 1, 0, &ptr } ) : param{ 0, 0, &ptr };
                        _line_param[index_now].emplace(line_now, val);
                    }

                    // line is in _line_param
                    else {

                        auto& line = _line_param[index_now][line_now];
                        // Is 'count' greater than 0 ?
                        if (json_line["count"].GetUint64())
                            is_successed ? line.Ncs++ : line.Ncf++;
                    }
                }
            }
    }
}

void Coverage::CalculateSus()
{
    for (auto& dict_iter : _line_param)
        for (auto& param_iter : dict_iter) {

            auto& p = param_iter.second;
            int denom = _fail * (p.Ncf + p.Ncs);
            p.ptr_ranking->sus = p.ptr_ranking->ochiai_sus = denom ? p.Ncf / std::sqrt(denom) : 0.0f;
        }
    
}

const std::list<ranking_info>& Coverage::Rank()
{
    // Sort
    _ranking.sort([](const ranking_info& lhs, const ranking_info& rhs){ return lhs.sus > rhs.sus; });
    
    // Rank
    line_type ranking;
    line_type virtual_ranking = 1;
    float sus = std::numeric_limits<float>::infinity();

    for (auto& iter : _ranking) {

        if (sus > iter.sus) {

            sus = iter.sus;
            ranking = virtual_ranking;
        }
        iter.ranking = ranking;
        virtual_ranking++;
    }

    return _ranking;
}

void Coverage::Save(std::ofstream& ofs) const
{
    char buf[10];

    // files
    ofs.write("{\n\t\"files\": [\n", 14);
    for (size_t i = 0; i != _index2file.size(); ++i) {

        ofs.write("\t\t\"", 3);
        ofs.write(_index2file[i].c_str(), _index2file[i].size());
        i != _index2file.size() - 1 ? ofs.write("\",\n", 3) : ofs.write("\"\n", 2);
    }      
    ofs.write("\t],\n", 4);

    // total                                                                                                                                                                                                                                                 
    ofs.write("\t\"total\": ", 10);
    auto result_ptr = std::to_chars(buf, buf + 10, _ranking.size()).ptr;
    ofs.write(buf, result_ptr - buf);
    ofs.write(",\n\t\"lines\": [\n", 14);

    // lines
    auto end = _ranking.end();
    end--;
    for (auto iter = _ranking.cbegin(); iter != _ranking.cend(); iter++) {
        
        // index
        ofs.write("\t\t{ \"index\": ", 13);
        auto result_ptr = std::to_chars(buf, buf + 10, iter->index).ptr;
        ofs.write(buf, result_ptr - buf);
        // line
        ofs.write(", \"line\": ", 10);
        result_ptr = std::to_chars(buf, buf + 10, iter->line).ptr;
        ofs.write(buf, result_ptr - buf);
        // sus
        ofs.write(", \"sus\": ", 9);
        ofs << iter->sus;
        // ranking
        ofs.write(", \"ranking\": ", 13);
        result_ptr = std::to_chars(buf, buf + 10, iter->ranking).ptr;
        ofs.write(buf, result_ptr - buf);
        iter != end ? ofs.write(" },\n", 4) : ofs.write("}\n", 2);
    }
    ofs.write("\t]\n}", 4);
    ofs.put(' ');
}






void Coverage::_write(std::ofstream& ofs)
{
    ofs << _is_initialized << '\n' << _fail << '\n' << _index2file.size() << '\n';
    
    for (auto& iter : _index2file) {

        ofs.write(iter.c_str(), iter.size());
        ofs.put('\n');
    }

    for (auto& file : _line_param) {

        ofs << file.size() << '\n';
        for (auto& iter : file)
            ofs << iter.first << '\n' << iter.second.Ncf << '\n' << iter.second.Ncs << '\n';
    }
}

void Coverage::_read(std::ifstream& ifs)
{
    index_type index_size = 0;
    ifs >> _is_initialized >> _fail >> index_size;

    _index2file.clear();
    _index2file.reserve(index_size);
    _file2index.clear();
    _file2index.reserve(index_size);
    for (index_type i = 0; i != index_size; i++) {

        std::string buf;
        ifs >> buf;
        _index2file.emplace_back(buf);
        _file2index.emplace(buf, i);
    }

    _ranking.clear();
    _line_param.clear();
    _line_param.reserve(index_size);
    for (index_type idx = 0; idx != index_size; idx++) {
        
        line_type file_size;
        ifs >> file_size;
        _line_param.emplace_back();
        _line_param[idx].reserve(file_size);

        for (line_type j = 0; j != file_size; j++) {

            line_type line;
            count_type Ncf, Ncs;
            ifs >> line >> Ncf >> Ncs;

            auto& ptr = _ranking.emplace_back(ranking_info{ idx, line, 0.0f, 0.0f, 0 });
            _line_param[idx].emplace(line, param{ Ncf, Ncs, &ptr });
        }
    }
}
}
#endif
