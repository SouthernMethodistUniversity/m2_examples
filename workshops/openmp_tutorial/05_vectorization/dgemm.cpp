#include <iostream>
#include <chrono>
#include <armadillo>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " i j k" << std::endl;
        return 1;
    }
    const unsigned long int m = std::stoul(argv[1]);
    const unsigned long int n = std::stoul(argv[2]);
    const unsigned long int p = std::stoul(argv[3]);
    arma::arma_rng::set_seed_random();
    arma::mat A(m, n, arma::fill::randu);
    arma::mat B(n, p, arma::fill::randu);
    arma::mat C(m, p, arma::fill::zeros);
    arma::mat D(m, p, arma::fill::zeros);
    auto t1 = std::chrono::high_resolution_clock::now();
    D = A*B;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_armadillo = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for simd
    for (unsigned long int k = 0; k < p; ++k) { 
        for (unsigned long int j = 0; j < n; ++j) {
            for (unsigned long int i = 0; i < m; ++i) {
                C.at(i, k) += A.at(i, j) * B.at(j, k);
            }
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    auto duration_openmp = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    std::cout << "Armadillo: " << duration_armadillo << " ms" << std::endl;
    std::cout << "OpenMP: " << duration_openmp << " ms" << std::endl;
    if (arma::approx_equal(C, D, "absdiff", 1E-8)) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Failure!" << std::endl;
    }
    return 0;
}

