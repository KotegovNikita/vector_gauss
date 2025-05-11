#include "gaussian.hpp"
#include <stdexcept>
#include <cmath>

namespace { constexpr double eps = 1e-12; }

/*  Простой Гаусс с частичным выбором главного элемента.
    Память O(n²), время O(n³). Работает над расширенной матрицей n×(n+1). */
Eigen::VectorXd gaussian_solve(Eigen::MatrixXd a)
{
    const int n = a.rows();
    if (a.cols() != n + 1)
        throw std::invalid_argument("augmented matrix size mismatch");

    // ---------- прямой ход ----------
    for (int k = 0; k < n; ++k)
    {
        // 1) ищем строку-пивот
        int piv = k;
        double maxv = std::abs(a(k, k));
        for (int i = k + 1; i < n; ++i)
        {
            const double v = std::abs(a(i, k));
            if (v > maxv) { maxv = v; piv = i; }
        }
        if (maxv < eps) throw std::runtime_error("singular matrix");
        if (piv != k) a.row(k).swap(a.row(piv));

        // 2) нормируем ведущую строку
        const double diag = a(k, k);
        for (int j = k; j < n + 1; ++j) a(k, j) /= diag;

        // 3) зануляем элементы под диагональю
        for (int i = k + 1; i < n; ++i)
        {
            const double f = a(i, k);
            if (std::abs(f) < eps) continue;
            for (int j = k; j < n + 1; ++j)
                a(i, j) -= f * a(k, j);
        }
    }

    // ---------- обратный ход ----------
    Eigen::VectorXd x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        double sum = a(i, n);            // свободный член
        for (int j = i + 1; j < n; ++j)
            sum -= a(i, j) * x(j);
        x(i) = sum;                      // a(i,i) уже единица
    }
    return x;                            // скопированный, безопасный вектор
}
