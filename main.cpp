#include "index.h"



int main(int argc, char *argv[])
{
    /*PAFL::CppTokenTree tree(fs::path("sample/temp.cpp"), std::make_shared<PAFL::TokenTree::Matcher>());
    std::ofstream ofs("token.txt");
    tree.log(ofs);
    return 0;*/

    // Test
    /*char *_argv[] = {
        "", "cppcheck:cpp", "30", "pafl,ochiai", "-P/Users/user/defects4cpp/cppcheck", 
        "-T/Users/user/defects4cpp", "-B/Users/user/Documents/C++/PAFL/_bug_info"
    };
    int _argc = 7;
    PAFL::UI ui(_argc, _argv);*/

    PAFL::UI ui(argc, argv);
    
    // Collect coverage of every version
    std::vector<PAFL::TestSuite> suite(ui.numVersion());
    for (size_t v = 0; v != ui.numVersion(); v++) {

        for (auto& item : ui.getCoverageList(v+1))
            suite[v].addTestCase(item.first, item.second);
        suite[v].setSbflSus(PAFL::Coef::Ochiai);
        PAFL::normalizeSbfl(suite[v], PAFL::Normalizer::CbrtOchiai);
    }
    
    // Project Aware FL
    // Model
    PAFL::FLModel flmodel;
    //flmodel.setLogger("log", ui.getProject());
    auto matcher = std::make_shared<PAFL::TokenTree::Matcher>(); // Tokenize files

    std::string prefix(std::string("coverage/PAFL-") + ui.getProject() + '#');
    for (size_t v = 0; v != ui.numVersion(); v++) {

        std::cout << "ver " << v+1 << '\n';
        PAFL::TokenTree::Vector tkt_vector;
        tkt_vector.reserve(suite[v].MaxIndex());

        std::cout << "Tokenizing...\n";
        for (PAFL::index_t idx = 0;  idx != suite[v].MaxIndex(); idx++)
            tkt_vector.push_back(PAFL::CppTokenTree(ui.getProjectPath(v) / suite[v].getFileFromIndex(idx), matcher));
        std::cout << "Done\n";
    
        // new sus of FL Model
        std::cout << "Evaluating...\n";
        flmodel.localize(suite[v], tkt_vector);
        std::cout << "Done\n";

        // Save as json
        std::cout << "Saving...\n";
        std::ofstream ofs(prefix + std::to_string(v+1) + ".json");
        suite[v].save(ofs);
        ofs.close();
        std::cout << "Done\n";
        
        // Learning
        if (v + 1 != ui.numVersion()) {

            std::cout << "Learning...\n";
            flmodel.step(suite[v], tkt_vector, ui.getFaultLocation(v));
            std::cout << "Done\n";
        }
    }

    return 0;
}
