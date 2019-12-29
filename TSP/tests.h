#ifndef tester_h
#define tester_h

#include "graph.h"
#include "TSP_MST.h"
#include "TSP_EXACT.h"
#include "dots.h"
#include <fstream>
#include <iomanip>
#include <numeric>

std::pair<double, double> get_mean_and_sigma(std::vector<double> input);

void run_and_print_single_test(std::vector<unsigned> seeds, unsigned size, std::ofstream& fileout, bool print_all=false);
   /* For a size = size of the graph run nruns = seeds.size() realizations of the system. For each calculate the exact TSP distance of a loop 
   and an approximate one based on the Kruskal's MST. 
   Output: function prints the average and standard deviation for the error, calculated as (APPROX - EXACT) / EXACT (%) for each realization.
   In this algorithm it is <= 100 %. If print_all = true, then the exact and average values for each realization are also printed.*/

void run_tests(unsigned min_size, unsigned max_size, std::vector<unsigned> seeds, std::ofstream& fileout);
   /* For sizes of the graphs in range [min_size, max_size] run run_and_print_single_test with dafult options.*/

#endif