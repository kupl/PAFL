#include "pipeline/pipeline.h"

int main(int argc, const char *argv[])
{
    PAFL::Pipeline pipe(argc, argv);
    pipe.run();
}
