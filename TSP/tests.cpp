#include "tests.h"

std::pair<double, double> get_mean_and_sigma(std::vector<double> input) {
    double mean = std::accumulate(input.begin(), input.end(), 0.0) / input.size();   
    double sigma = 0;
    for (double el: input) {
        sigma += (el - mean) * (el - mean);
    }
    sigma = std::sqrt(sigma / input.size());
    return std::make_pair(mean, sigma); 
}

void run_and_print_single_test(std::vector<unsigned> seeds, unsigned size,   \
                               std::ofstream& fileout, bool print_all) {
    unsigned nruns = seeds.size();
    std::vector<double> errors(nruns);
    fileout << "Size = " << size << ", runs = "  << nruns << std::endl;
    for (unsigned nrun = 0; nrun < nruns; ++nrun) {
        Graph graph(size);
        unsigned seed = seeds[nrun];
        generate_graph(seed, graph);
        TSP_MST tsp_solver;
        TSP_EXACT exact_solver;
        double mst_len = tsp_solver.get_mst_len(graph);
        double exact_len = exact_solver.get_exact_len(graph);
        errors[nrun] = (mst_len - exact_len) / exact_len * 100;
        if (print_all) {
            fileout << "seed = " << seed << ", nrun = " << nrun << std::endl;
            fileout << "[Error: " << std::setprecision(4) << errors[nrun] \
                    << std::setprecision(3) <<"%] exact: "  \
                    << exact_len << ", " << "approx.: "   \
                    << mst_len << "\n" << std::endl;
        }  
    }
    std::pair<double, double> mean_and_sigma = get_mean_and_sigma(errors);
    fileout << "Average error: " << std::setprecision(3)  \
            << mean_and_sigma.first  << "%, standard deviation: " \
            << mean_and_sigma.second <<"%" << std::endl;
}


void run_tests(unsigned min_size, unsigned max_size,  \
               std::vector<unsigned> seeds, std::ofstream& fileout) {
    for (unsigned size = min_size; size <= max_size; ++size) {
        run_and_print_single_test(seeds, size, fileout);
    }
}