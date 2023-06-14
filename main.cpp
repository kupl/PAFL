#include "index.h"
#include <array>
#include <list>
#include <iostream>

int main(int argc, char *argv[])
{
    const std::filesystem::path global_path = "/Users/user/defects4cpp";
    // std::array<std::string, 17> proj{ "coreutils", "cpp_peglib", "cppcheck", "dlt_daemon", "exiv2", "jerryscript", "libchewing", "libssh", "libtiff", "libucl", "libxml2", "ndpi", "proj", "wget2", "wireshark", "xbps", "zsh" };
    // std::array<int, 17> tax{ 2, 10, 30, 1, 20, 11, 8, 1, 5, 6, 7, 3, 28, 3, 6, 5, 5 };
    std::array<std::string, 2> proj{ "cppcheck", "proj" };
    std::array<int, 2> tax{ 30, 28 };
    
    for (size_t i = 0; i != proj.size(); ++i) {
 
        // Initialize coverage
        std::vector<PAFL::Coverage> covs(tax[i]);
/*
        // Collect coverage of every tax
        for (auto t = 0; t != tax[i]; ++t) {
            
            std::string tax(std::to_string(t + 1));
            std::cout << proj[i] << " # " << tax << '\n';
            
            // folder name of buggy project
            auto buggy_proj(proj[i] + "-buggy#" + tax + '-');
            // test case list of target project
            std::list<std::filesystem::path> test_case_path;
            std::list<unsigned short> test_case_num;
            
            // Add every test case to coverage
            for (auto const& dir_entry : std::filesystem::directory_iterator(global_path)) {
                
                auto& path = dir_entry.path();
                auto folder(path.filename().string());
                if (folder.find(buggy_proj) != std::string::npos) {
                    
                    folder.erase(0, buggy_proj.length());
                    std::cout << "case " << folder << '\n';

                    Document doc;
                    PAFL::Parse(doc, path);
                    covs[t].AddTestCase(doc, PAFL::IsTestPassed(path, folder));
                }
            }

            std::cout << "Evaluating...\n";
            covs[t].CalculateSus();
            //covs[t].Rank();
            std::cout << "Done\n";
        }

        // Save as json
        {
            std::cout << "Saving...\n";
            std::string prefix = std::string("_coverage/python-") + proj[i] + '#';
            
            for (auto t = 0; t != tax[i]; t++) {

                std::ofstream ofs(prefix + std::to_string(t + 1) + ".json");
                covs[t].Save(ofs);
                ofs.close();
            }
            std::cout << "Done\n";
        }

        // Save data
        {
            std::cout << "Saving...\n";
            std::string prefix = std::string("_line_param/") + proj[i] + '#';
            
            for (auto t = 0; t != tax[i]; t++) {

                std::ofstream ofs(prefix + std::to_string(t + 1) + ".txt");
                covs[t]._write(ofs);
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

                std::ifstream ifs(prefix + std::to_string(t + 1) + ".txt");
                covs[t]._read(ifs);
                ifs.close();
                covs[t].CalculateSus();
                covs[t].Rank();
            }
            std::cout << "Done\n";
        }

        // Project Aware FL
        // Tokenize files
        std::ofstream debug_log("debug-log.txt");

        auto proj_path(global_path / proj[i]);
        std::string buggy("buggy#");
        std::string prefix = std::string("_coverage/PAFL-") + proj[i] + '#';

        for (auto t = 0; t != tax[i]; ++t) {
            
            std::cout << "tax " << t + 1 << '\n';
            std::vector<PAFL::TokenStream> tks_container;
            tks_container.reserve(covs[t].MaxIndex());

            std::cout.write("Tokenizing...\n", 15);
            for (PAFL::index_type idx = 0;  idx != covs[t].MaxIndex(); ++idx)
                tks_container.emplace_back(proj_path / (buggy + std::to_string(t + 1)) / covs[t].GetFileFromIndex(idx));
            std::cout.write("Done\n", 6);

            // new sus of FL Model
            std::cout << "Evaluating...\n";
            PAFL::FlModel model(covs[t]);
            model.CalculateSus(tks_container);
            model.Rank();
            std::cout << "Done\n";

            // Save as json
            std::cout << "Saving...\n";
            std::ofstream ofs(prefix + std::to_string(t + 1) + ".json");
            model.Save(ofs);
            ofs.close();
            std::cout << "Done\n";

            /*if (t == 1) {

                std::ofstream ofs("log.txt");
                for(line_type i = 1; i != tks_container[model.GetIndexFromFile("lib/checkother.cpp")].GetLastLine(); i++) {

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

    }

    return 0;
}
