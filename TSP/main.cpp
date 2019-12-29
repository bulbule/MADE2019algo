#include "tests.h"

int main() {
    /* 
     Single test: for the same system size
     run nruns of system realizations
    */
    unsigned size = 9;
    unsigned nruns = 50;
    std::vector<unsigned> seeds(nruns);
    std::iota(seeds.begin(), seeds.end(), 1);
    std::ofstream fileout1("test1.txt");
    run_and_print_single_test(seeds, size, fileout1, true);

    /* multiple tests for different sizes of the graph */
    nruns = 50;
    seeds.resize(nruns);
    std::iota(seeds.begin(), seeds.end(), 1);
    std::ofstream fileout2("multiple_tests.txt");
    run_tests(4, 10, seeds, fileout2);
}
