#include <chrono>
#include <iostream>
#include <vector>
#include <iomanip>

std::vector<int> max_kernel(const std::vector<int>& num_list, int k) {
    int n = static_cast<int>(num_list.size());
    if (n <= 0 || k <= 0 || k > n) {
        return {};
    }

    std::vector<int> result;
    result.reserve(n - k + 1);

    for (int i = 0; i <= n - k; ++i) {
        int cur_max = num_list[i];
        for (int j = 1; j < k; ++j) {
            if (num_list[i + j] > cur_max) {
                cur_max = num_list[i + j];
            }
        }
        result.push_back(cur_max);
    }

    return result;
}

int main() {
    std::vector<int> num_list = {3, 4, 5, 1, -44, 5, 10, 12, 33, 1};
    int k = 3;

    auto start = std::chrono::steady_clock::now();
    std::vector<int> kq = max_kernel(num_list, k);
    auto end = std::chrono::steady_clock::now();

    std::cout << "[";
    for (size_t i = 0; i < kq.size(); ++i) {
        std::cout << kq[i] << (i + 1 < kq.size() ? ", " : "");
    }
    std::cout << "]\n";

    std::chrono::duration<double, std::micro> elapsed_us = end - start;
    std::cout << "Run in: " << std::fixed << std::setprecision(2)
              << elapsed_us.count() << " µs\n";

    return 0;
}