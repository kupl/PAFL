#include "index.h"
#include <array>
#include <iostream>
#include "tokentree_cpp.h"

int main(int argc, char *argv[])
{
    PAFL::CppTokenTree sample("sample/temp.cpp", std::make_shared<PAFL::CppTokenTree::Matcher>());
    std::ofstream ofs("token.txt");
    sample.log(ofs);
    return 0;


    const std::filesystem::path global_path = "/Users/user/defects4cpp";
    //std::array<std::string, 17> proj{ "coreutils", "cpp_peglib", "cppcheck", "dlt_daemon", "exiv2", "jerryscript", "libchewing", "libssh", "libtiff", "libucl", "libxml2", "ndpi", "proj", "wget2", "wireshark", "xbps", "zsh" };
    //std::array<int, 17> tax{ 2, 10, 30, 1, 20, 11, 8, 1, 5, 6, 7, 3, 28, 3, 6, 5, 5 };
    std::array<std::string, 2> proj{ "cppcheck", "proj" };
    std::array<int, 2> tax{ 30, 28 };
    
    for (size_t i = 0; i != 2/*proj.size()*/; ++i) {
 
        // Initialize coverage
        std::vector<PAFL::TestSuite> suite(tax[i]);
/*
        // Collect coverage of every tax
        for (auto t = 0; t != tax[i]; ++t) {
            
            std::string tax(std::to_string(t + 1));
            std::cout << proj[i] << " # " << tax << '\n';
            
            // folder name of buggy project
            auto buggy_proj(proj[i] + "-buggy-" + tax + '-');
            // test case list of target project
            std::list<std::filesystem::path> test_case_path;
            std::list<unsigned short> test_case_num;
            
            // Add every test case to test suite
            for (auto const& dir_entry : std::filesystem::directory_iterator(global_path)) {
                
                auto& path = dir_entry.path();
                auto folder(path.filename().string());
                if (folder.find(buggy_proj) != std::string::npos) {
                    
                    folder.erase(0, buggy_proj.length());
                    std::cout << "case " << folder << '\n';

                    Document doc;
                    PAFL::Parse(doc, path / "summary.json");
                    suite[t].AddTestCase(doc, PAFL::IsTestPassed(path, folder));
                    std::cout << suite[t].GetTestSuite().size() << '\n';
                }
            }
        }

        // Save data
        {
            std::cout << "Saving...\n";
            std::string prefix = std::string("_line_param/") + proj[i] + '#';
            
            for (auto t = 0; t != tax[i]; t++) {
                
                std::ofstream ofs(prefix + std::to_string(t + 1) + ".txt");
                suite[t]._write(ofs);
                ofs.close();
            }
            std::cout << "Done\n";
        }

*/
        // Load data
        {
            std::cout << "Loading...\n";
            std::string prefix = std::string("_line_param/") + proj[i] + '#';
            
            for (auto t = 0; t != tax[i]; t++) {

                std::cout << t << '\n';
                std::ifstream ifs(prefix + std::to_string(t + 1) + ".txt");
                suite[t]._read(ifs);
                ifs.close();
                suite[t].CalculateSus();
            }
            std::cout << "Done\n";
        }

        // Buggy line
        auto bug_info(PAFL::ReadBugList("_buggy_line/" + proj[i] + ".json"));

        // Project Aware FL
        // Tokenize files
        auto proj_path(global_path / proj[i]);
        std::string buggy("buggy#");
        /*std::string prefix = std::string("_coverage/Ochiai-") + proj[i] + '#';*/
        std::string prefix = std::string("_coverage/PAFL-") + proj[i] + '#';
        // Model
        PAFL::FLModel flmodel;
        flmodel.setLogger("_log", proj[i]);
        auto matcher = std::make_shared<PAFL::CppTokenTree::Matcher>();


        for (auto t = 0; t != tax[i]; ++t) {
/*
            // Save as json
            std::cout << "Saving...\n";
            suite[t].CalculateSus();
            suite[t].Rank();
            std::ofstream ofs(prefix + std::to_string(t + 1) + ".json");
            suite[t].Save(ofs);
            ofs.close();
            std::cout << "Done\n";
*/
            /*std::cout << "tax " << t + 1 << '\n';
            PAFL::TokenTree::Vector tkt_container;
            tkt_container.reserve(suite[t].MaxIndex());

            std::cout.write("Tokenizing...\n", 15);
            for (PAFL::index_t idx = 0;  idx != suite[t].MaxIndex(); ++idx)
                tkt_container.emplace_back(proj_path / (buggy + std::to_string(t + 1)) / suite[t].GetFileFromIndex(idx), matcher);
            std::cout.write("Done\n", 6);
        
            // new sus of FL Model
            std::cout << "Evaluating...\n";
            flmodel.Localize(tkt_container, suite[t]);
            std::cout << "Done\n";

            // Save as json
            std::cout << "Saving...\n";
            std::ofstream ofs(prefix + std::to_string(t + 1) + ".json");
            suite[t].Save(ofs);
            ofs.close();
            std::cout << "Done\n";
            
            // Learning
            if (t + 1 != tax[i]) {

                std::cout << "Learning...\n";
                flmodel.Step(tkt_container, suite[t], suite[t].GetIndexFromFile(bug_info[t].first), bug_info[t].second);
                std::cout << "Done\n";
            }*/


            /*if (t == 1) {

                std::ofstream ofs("log.txt");
                for(line_t i = 1; i != tks_container[model.GetIndexFromFile("lib/checkother.cpp")].GetLastLine(); i++) {

                    auto ptr = tks_container[model.GetIndexFromFile("lib/checkother.cpp")].GetTokens(i);
                    if (ptr) {
                        
                        for (auto& tok : *ptr) {

                            ofs << i << " | name: " << tok._name << " | parent: ";
                            if (tok._parent)
                                ofs << tok._parent->_name;
                            ofs << "\n\tcond : ";
                            for (auto& cond : tok._cond_children)
                                ofs << cond->_name << ", ";
                            ofs << "\n\tstm: ";
                            for (auto& stm : tok._stm_children)
                                ofs << stm->_name << ", ";
                            ofs << '\n';
                        }
                    }
                }
                ofs.close();
            }*/
        }
        /*
        std::cout << "similarity test";
        std::ofstream similarity("distance.txt");
        for (size_t t1 = 0; t1 != tax[i]; t1++)
            for (size_t t2 = 0; t2 != tax[i]; t2++) {
                
                if (t1 == t2)
                    continue;

                float dist = 0.0f;
                for (auto& item : feat_vecs[t1]) {
                    
                    if (!feat_vecs[t2].contains(item.first))
                        dist += feat_vecs[t1].at(item.first) * feat_vecs[t1].at(item.first);
                    else
                        dist += (feat_vecs[t1].at(item.first) - feat_vecs[t2].at(item.first)) * (feat_vecs[t1].at(item.first) - feat_vecs[t2].at(item.first));
                }
                for (auto& item : feat_vecs[t2])
                    if (!feat_vecs[t1].contains(item.first))
                        dist += feat_vecs[t2].at(item.first) * feat_vecs[t2].at(item.first);

                similarity << '(' << t1+1 << ' ' << t2+1 << ")\t: " << dist << '\n';
            }*/
    }

    return 0;
}
