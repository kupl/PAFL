#include "pipeline.h"

int run(int argc, char* argv[])                                     { PAFL::Pipeline(argc, argv).run(); return 0; }
int makeMatrix(int argc, char *argv[], const fs::path& path)        { PAFL::Pipeline(argc, argv).makeMatrix("/home/donguk/aeneas/manybugs"); return 0; }
int testTokenTreeCpp(const fs::path& path)                          { PAFL::TokenTreeCpp tree(path, std::make_shared<PAFL::TokenTree::Matcher>()); tree.log("__log.txt"); return 0; }
int testTokenTreePy(const fs::path& path)                           { PAFL::TokenTreePy tree(path, std::make_shared<PAFL::TokenTree::Matcher>(), "pytree.py"); tree.log("__log.txt"); return 0; }



int main(int argc, char *argv[])
{
    return run(argc, argv);
}
