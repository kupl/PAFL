#include "pipeline.h"

int run(int argc, const char* argv[])           { PAFL::Pipeline(argc, argv).run(); return 0; }
int makeMatrix(int argc, const char *argv[])    { PAFL::Pipeline(argc, argv).makeMatrix("/home/donguk/aeneas/manybugs"); return 0; }
int testTokenTreeCpp(const fs::path& path)      { PAFL::CppTokenTree tree(path, ".", 0, std::list<std::string>(), 0); std::ofstream("log.txt") << (tree.log()); return tree.good(); }
int testTokenTreePy(const fs::path& path)       { PAFL::TokenTree tree(path, ".", "pytree.py"); std::ofstream("log.txt") << (tree.log()); return 0; }



int main(int argc, const char *argv[])
{
    std::cout << testTokenTreeCpp("sample.cpp") << '\n';
    return 0;

    if (std::string(argv[1]) == "vscode-debug") {

        std::vector<std::string> string_argv;
        string_argv.push_back(argv[0]);

        //std::istringstream iss("-p cppcheck -l cpp -m ochiai,dstar,barinel -v 7,1,27,2,15,29,14,6,23,5,17,30,24,8,16,25,3,19,9,18,12,11,21,28,13,20,22,4,26,10 -d /4tb/donguk/bugscpp/cppcheck -t /4tb/donguk/bugscpp/test_cppcheck -i /home/donguk/PAFL/oracle -c --pafl");
        std::istringstream iss("-p cppcheck -l cpp -m ochiai,dstar,barinel -v 1,27,2,15,29,14,6,23,5,17,30,24,8,16,25,3,19,9,18,12,11,21,28,13,20,22,4,26,10 -d /4tb/donguk/bugscpp/cppcheck -t /4tb/donguk/bugscpp/test_cppcheck -i /home/donguk/PAFL/oracle -c --pafl");
        std::string buffer;

        while(iss >> buffer)
            string_argv.push_back(buffer);

        auto argv_debug = new const char*[string_argv.size()];
        for (int i = 0; i != string_argv.size(); i++)
            argv_debug[i] = string_argv[i].c_str();
        return run(string_argv.size(), argv_debug);
    }
    return run(argc, argv);
}
