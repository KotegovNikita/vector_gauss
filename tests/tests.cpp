#include <gtest/gtest.h>
#include "gaussian.hpp"
#include <random>

TEST(Gauss, Small2x2)
{
    Eigen::MatrixXd aug(2,3);
    aug << 3, 2, 5,
           1, 4, 6;

    Eigen::VectorXd x   = gaussian_solve(aug);
    Eigen::VectorXd ref = aug.leftCols(2)
                             .fullPivLu()
                             .solve(aug.col(2))
                             .eval();          // <-- ключ!

    EXPECT_TRUE(x.isApprox(ref, 1e-12));
}

TEST(Gauss, Random50)
{
    constexpr int n = 50;
    std::mt19937 gen(42);
    std::uniform_real_distribution<> d(-5, 5);

    Eigen::MatrixXd aug(n, n+1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n+1; ++j)
            aug(i, j) = d(gen);

    Eigen::VectorXd x   = gaussian_solve(aug);
    Eigen::VectorXd ref = aug.leftCols(n)
                             .fullPivLu()
                             .solve(aug.col(n))
                             .eval();          // <-- ключ!

    EXPECT_LT((x - ref).norm(), 1e-9);
}

