#include "gbm.hpp"

#include <cmath>
#include <random>
#include <stdexcept>

namespace mc {

std::vector<double> generate_gbm_path(double s0, double mu, double sigma, double t,
                                      std::size_t n_steps, std::uint64_t seed) {
    if (s0 <= 0.0) {
        throw std::invalid_argument("s0 must be positive");
    }
    if (sigma < 0.0) {
        throw std::invalid_argument("sigma must be non-negative");
    }
    if (t <= 0.0) {
        throw std::invalid_argument("t must be positive");
    }

    std::vector<double> path;
    path.reserve(n_steps + 1);
    path.push_back(s0);
    if (n_steps == 0) {
        return path;
    }

    std::mt19937_64 rng(seed);
    std::normal_distribution<double> normal(0.0, 1.0);

    const double dt = t / static_cast<double>(n_steps);
    const double drift = (mu - 0.5 * sigma * sigma) * dt;
    const double vol = sigma * std::sqrt(dt);

    double s = s0;
    for (std::size_t k = 0; k < n_steps; ++k) {
        s *= std::exp(drift + vol * normal(rng));
        path.push_back(s);
    }
    return path;
}

}  // namespace mc
