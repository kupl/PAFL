#include "index.h"


// python : keras , luigi , matplotlib , pandas , scrapy , youtube-dl
int main(int argc, char *argv[])
{
    /*PAFL::CppTokenTree tree(fs::path("sample/temp.cpp"), std::make_shared<PAFL::TokenTree::Matcher>());
    tree.log("token.txt");
    return 0;*/

    // Test
    char *_argv[] = {
        "./main", "cppcheck:cpp", "7,1,27,2,15,29,14,6,23,5,17,30,24,8,16,25,3,19,9,18,12,11,21,28,13,20,22,4,26,10", "pafl,ochiai", "-P/Users/user/defects4cpp/cppcheck", 
        "-T/Users/user/defects4cpp", "-B/Users/user/Documents/C++/PAFL/_bug_info", "-l", "--dev-cache"
    };
    constexpr int _argc = 9;
    std::system(PAFL::Command::CLEAR);

    PAFL::UI ui(_argc, _argv);

    // PAFL::UI ui(argc, argv);
    

    // Collect coverage of every version
    std::vector<PAFL::TestSuite> suite(ui.numVersion());
    const auto cache_path(PAFL::createDirRecursively(fs::path("./cache") / ui.getProject()));

    for (size_t iter = 0; iter != ui.numVersion(); iter++) {

        const auto path((cache_path / (std::string("ts#") + std::to_string(ui.getVersion(iter)) + ".txt")));
        if (ui.hasCache() && suite[iter]._read(path)) {

            std::cout << "Load " << ui.getProject() << " - " << ui.getVersion(iter) << '\n';
            continue;
        }

        // Collect Coverage data
        for (auto& item : ui.getCoverageList(iter))
            suite[iter].addTestCase(item.first, item.second);

        if (ui.hasCache())
            suite[iter]._write(path);
    }

    // Method map
    const std::string method2string[5] { "PAFL", "Tarantula", "Ochiai", "Dstar", "Barinel" };
    decltype(PAFL::Coef::Ochiai)* method2coef[5] { PAFL::Coef::Ochiai, PAFL::Coef::Tarantula, PAFL::Coef::Ochiai, PAFL::Coef::Dstar, PAFL::Coef::Barinel };

    // Project Aware FL Model
    PAFL::FLModel flmodel;
    if (ui.hasLogger())
        flmodel.setLogger(std::make_unique<PAFL::FLModel::Logger>(PAFL::createDirRecursively(fs::path("./log/model")) / ui.getProject()));
    auto matcher = std::make_shared<PAFL::TokenTree::Matcher>(); // Tokenize files


    // Localizing & Learning
    for (auto method : ui.getMethodSet()) {

        std::cout << "\n < " << method2string[static_cast<size_t>(method)] << " >\n\n";
        std::string prefix(std::string("./coverage/") + method2string[static_cast<size_t>(method)] + '-' + ui.getProject() + '#');

        for (size_t iter = 0; iter != ui.numVersion(); iter++) {
            std::cout << "ver " << iter+1 << '\n';


            // SBFL
            if (method != PAFL::UI::Method::PAFL) {

                std::cout << "Evaluating...\n";
                suite[iter].setSbflSus(method2coef[static_cast<size_t>(method)]);
                suite[iter].rank();
                std::cout << "Done\n";

                // Save as json
                std::cout << "Saving...\n";
                suite[iter].save(prefix + std::to_string(iter+1) + ".json");
                std::cout << "Done\n";
            }


            // PAFL
            else {
                
                // Baseline = Ochiai
                suite[iter].setSbflSus(PAFL::Coef::Ochiai);
                PAFL::normalizeSbfl(suite[iter], PAFL::Normalizer::CbrtOchiai);

                // Set token tree
                PAFL::TokenTree::Vector tkt_vector;
                tkt_vector.reserve(suite[iter].MaxIndex());
                std::cout << "Tokenizing...\n";
                for (PAFL::index_t idx = 0;  idx != suite[iter].MaxIndex(); idx++) {
                    
                    auto file = suite[iter].getFileFromIndex(idx);
                    tkt_vector.push_back(PAFL::CppTokenTree(ui.getProjectPath(iter) / file, matcher));

                    if (ui.hasLogger()) {

                        std::replace(file.begin(), file.end(), '/', '.');
                        tkt_vector[idx].log(PAFL::createDirRecursively(fs::path("./log/token_tree")\
                                            / (ui.getProject() + '#' + std::to_string(iter+1))) / (file + ".txt"));
                    }
                }
                std::cout << "Done\n";
            
                // New sus of FL Model
                std::cout << "Evaluating...\n";
                flmodel.localize(suite[iter], tkt_vector);
                std::cout << "Done\n";

                // Save as json
                std::cout << "Saving...\n";
                suite[iter].save(prefix + std::to_string(iter+1) + ".json");
                std::cout << "Done\n";
                    
                // Learning
                if (iter + 1 != ui.numVersion()) {

                    std::cout << "Learning...\n";
                    flmodel.step(suite[iter], tkt_vector, ui.getFaultLocation(iter));
                    std::cout << "Done\n";
                }
            }
        }
    }

    return 0;
}
