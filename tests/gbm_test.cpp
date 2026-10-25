#include "gbm.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

namespace {

constexpr double kS0 = 100.0;
constexpr double kMu = 0.05;
constexpr double kSigma = 0.2;
constexpr double kT = 1.0;
constexpr std::size_t kSteps = 252;
constexpr std::uint64_t kSeed = 42;

}  // namespace

TEST(GbmPath, ZeroSigmaIsDeterministicExponent) {
    const auto path = mc::generate_gbm_path(kS0, kMu, 0.0, kT, kSteps, kSeed);
    ASSERT_EQ(path.size(), kSteps + 1);
    const double dt = kT / static_cast<double>(kSteps);
    for (std::size_t k = 0; k < path.size(); ++k) {
        const double expected = kS0 * std::exp(kMu * dt * static_cast<double>(k));
        EXPECT_NEAR(path[k], expected, 1e-12 * expected) << "k = " << k;
    }
}

TEST(GbmPath, SameSeedGivesSamePath) {
    const auto a = mc::generate_gbm_path(kS0, kMu, kSigma, kT, kSteps, kSeed);
    const auto b = mc::generate_gbm_path(kS0, kMu, kSigma, kT, kSteps, kSeed);
    EXPECT_EQ(a, b);
}

TEST(GbmPath, DifferentSeedsGiveDifferentPaths) {
    const auto a = mc::generate_gbm_path(kS0, kMu, kSigma, kT, kSteps, kSeed);
    const auto b = mc::generate_gbm_path(kS0, kMu, kSigma, kT, kSteps, kSeed + 1);
    EXPECT_NE(a, b);
}

TEST(GbmPath, SizeAndFirstElement) {
    const auto path = mc::generate_gbm_path(kS0, kMu, kSigma, kT, kSteps, kSeed);
    ASSERT_EQ(path.size(), kSteps + 1);
    EXPECT_EQ(path.front(), kS0);
}

TEST(GbmPath, ZeroStepsReturnsOnlyS0) {
    const auto path = mc::generate_gbm_path(kS0, kMu, kSigma, kT, 0, kSeed);
    EXPECT_EQ(path, std::vector<double>{kS0});
}

TEST(GbmPath, AllPricesPositive) {
    const auto path = mc::generate_gbm_path(kS0, kMu, kSigma, kT, kSteps, kSeed);
    for (double s : path) {
        EXPECT_GT(s, 0.0);
    }
}

TEST(GbmPath, NegativeSigmaThrows) {
    EXPECT_THROW(mc::generate_gbm_path(kS0, kMu, -0.1, kT, kSteps, kSeed),
                 std::invalid_argument);
}

TEST(GbmPath, NonPositiveS0Throws) {
    EXPECT_THROW(mc::generate_gbm_path(0.0, kMu, kSigma, kT, kSteps, kSeed),
                 std::invalid_argument);
    EXPECT_THROW(mc::generate_gbm_path(-1.0, kMu, kSigma, kT, kSteps, kSeed),
                 std::invalid_argument);
}

TEST(GbmPath, NonPositiveTThrows) {
    EXPECT_THROW(mc::generate_gbm_path(kS0, kMu, kSigma, 0.0, kSteps, kSeed),
                 std::invalid_argument);
    EXPECT_THROW(mc::generate_gbm_path(kS0, kMu, kSigma, -1.0, kSteps, kSeed),
                 std::invalid_argument);
}
