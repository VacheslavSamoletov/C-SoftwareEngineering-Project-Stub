#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace mc {

/**
 * \brief Generates a geometric Brownian motion price path.
 *
 * Uses the exact (log-space) scheme:
 * S[k+1] = S[k] * exp((mu - sigma^2 / 2) * dt + sigma * sqrt(dt) * Z),
 * where dt = t / n_steps and Z ~ N(0, 1).
 * Random numbers come from std::mt19937_64 seeded with \p seed,
 * so the same arguments always produce the same path.
 *
 * \param s0 Initial price, must be positive.
 * \param mu Drift (annualized).
 * \param sigma Volatility (annualized), must be non-negative.
 * \param t Time horizon in years, must be positive.
 * \param n_steps Number of time steps.
 * \param seed Seed for the random number generator.
 * \return Vector of n_steps + 1 prices; the first one is \p s0.
 *         If n_steps == 0, returns {s0}.
 * \throws std::invalid_argument If s0 <= 0, sigma < 0 or t <= 0.
 */
std::vector<double> generate_gbm_path(double s0, double mu, double sigma, double t,
                                      std::size_t n_steps, std::uint64_t seed);

}  // namespace mc
