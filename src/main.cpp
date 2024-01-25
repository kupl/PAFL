#include "pipeline.h"

int main(int argc, char *argv[])
{
    //PAFL::Pipeline(argc, argv).makeMatrix("/home/donguk/aeneas/manybugs");
    //return 0;
    PAFL::Pipeline(argc, argv).run();
    return 0;
}
/*
    PAFL::CppTokenTree tree(fs::path("sample/temp.cpp"), std::make_shared<PAFL::TokenTree::Matcher>());
    tree.log("token.txt");
    return 0;
*/
