#include <stdlib.h>
#include "example.h"

int test_data[5][2] = {
  {1, 1},
  {99, 99},
  {100, 100},
  {101, -101},
  {200, -200}
};

int main(int argc, char *argv[]) {
    int test_index = atoi(argv[1]);
    int output = func1(test_data[test_index][0]);
    int expected_output = test_data[test_index][1];
    return output == expected_output ? 0 : 1;
}