#include "write_wave.h"

int main(int argc, char* argv[]) {

    struct Input I1("input1", {0, 0, 1, 0, 1, 1, 1, 1, 0, 0});
    struct Input I2("input2", {1, 1, 0, 0, 0, 1, 0, 1, 0, 1});
    vector<Signal*> V1 = {&I1, &I2};

    create_file(V1);

    return 0;
}