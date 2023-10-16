#include "index.h"


/*PAFL::CppTokenTree tree(fs::path("sample/temp.cpp"), std::make_shared<PAFL::TokenTree::Matcher>());
    tree.log("token.txt");
    return 0;*/
// python - keras:45 , luigi:33 , matplotlib , pandas , scrapy:40 , youtube-dl:43

int main(int argc, char *argv[])
{
    // Test
    /*char *_argv[] = {
        "/Users/user/Documents/C++/PAFL/main", "openssl:cpp","13,1,2,9,12,19,14,28,11,15,5,18,16,22,10,23,26,8,24,25,17,6,4,7,3,27,20,21","pafl,ochiai",
        "-P/Users/user/defects4cpp/openssl","-T/Users/user/defects4cpp","-B/Users/user/Documents/C++/oracle","-l","--dev-cache" };
    constexpr int _argc = 9;
    std::system(PAFL::Command::CLEAR);
    PAFL::UI ui(_argc, _argv);*/

    // Run
    const PAFL::UI ui(argc, argv);

    // Collect coverage of every version
    std::vector<PAFL::TestSuite> suite(ui.numVersion());
    const auto cache_path(PAFL::createDirRecursively(ui.getExePath() / "cache" / ui.getProject()));

    for (size_t iter = 0; iter != ui.numVersion(); iter++) {

        const auto path((cache_path / (std::string("ts#") + std::to_string(ui.getVersion(iter)) + ".txt")));
        if (ui.hasCache() && suite[iter]._read(path)) {

            std::cout << "Load " << ui.getProject() << " - " << ui.getVersion(iter) << '\n';
            continue;
        }

        // Collect Coverage data
        for (auto& item : ui.getCoverageList(iter))
            suite[iter].addTestCase(item.first, item.second, ui.getExtensions());

        if (ui.hasCache())
            suite[iter]._write(path);
    }

    // Method map
    const std::string method2string[5] { "PAFL", "Tarantula", "Ochiai", "Dstar", "Barinel" };
    decltype(PAFL::Coef::Ochiai)* method2coef[5] { PAFL::Coef::Ochiai, PAFL::Coef::Tarantula, PAFL::Coef::Ochiai, PAFL::Coef::Dstar, PAFL::Coef::Barinel };

    // Project Aware FL Model
    PAFL::FLModel flmodel;
    PAFL::createDirRecursively(ui.getExePath() / "coverage");
    if (ui.hasLogger())
        flmodel.setLogger(std::make_unique<PAFL::FLModel::Logger>(PAFL::createDirRecursively(ui.getExePath() / "log/model") / ui.getProject()));
    auto matcher = std::make_shared<PAFL::TokenTree::Matcher>(); // Tokenize files


    // Localizing & Learning
    for (auto method : ui.getMethodSet()) {

        std::cout << "\n < " << method2string[static_cast<size_t>(method)] << " >\n\n";
        std::string prefix(ui.getExePath().string() + "/coverage/" + method2string[static_cast<size_t>(method)] + '-' + ui.getProject() + '#');

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
                    tkt_vector.push_back(PAFL::CppTokenTree(ui.getFilePath(iter, file), matcher));

                    /*if (ui.hasLogger()) {

                        std::replace(file.begin(), file.end(), '/', '.');
                        tkt_vector[idx].log(PAFL::createDirRecursively(ui.getExePath() / "log/token_tree"
                                            / (ui.getProject() + '#' + std::to_string(iter+1))) / (file + ".txt"));
                    }*/
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
