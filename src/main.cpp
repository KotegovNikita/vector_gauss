#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "gaussian.hpp"

static Eigen::MatrixXd read_aug(const std::string& path)
{
    std::ifstream f(path);
    if (!f) throw std::runtime_error("cannot open file");

    std::vector<std::vector<double>> rows;
    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> row;
        while (std::getline(ss, cell, ',')) row.push_back(std::stod(cell));
        if (!row.empty()) rows.push_back(std::move(row));
    }
    const int n = rows.size(), m = rows.front().size();
    Eigen::MatrixXd A(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) A(i, j) = rows[i][j];
    return A;
}

static void write_vec(const Eigen::VectorXd& x, const std::string& path)
{
    std::ofstream ofs(path);
    for (int i = 0; i < x.size(); ++i) ofs << x(i) << '\n';
}

int main(int argc, char** argv)
{
    if (argc != 3) { std::cerr << "usage: solve in.csv out.csv\n"; return 1; }
    try {
        auto aug = read_aug(argv[1]);
        write_vec(gaussian_solve(std::move(aug)), argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}
