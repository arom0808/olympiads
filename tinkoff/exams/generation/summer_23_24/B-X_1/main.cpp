#include <iostream>
#include <fstream>

bool get_value(std::uint64_t table, std::uint32_t n, std::uint32_t i, std::uint32_t j) {
    std::uint32_t cc = 1 << (n * n - 1);
    cc >>= i * n;
    cc >>= j;
    return (table & cc) != 0;
}

bool col_ok(std::uint64_t table, std::uint32_t n) {
    for (std::uint32_t j = 0; j < n; ++j) {
        std::int32_t pre_i = -1;
        for (std::uint32_t i = 0; i < n; ++i) {
            if (get_value(table, n, i, j)) {
                if (pre_i == -1 || pre_i == i - 1) pre_i = i;
                else return false;
            }
        }
        if (pre_i == -1) return false;
    }
    return true;
}

bool row_ok(std::uint64_t table, std::uint32_t n, std::uint32_t a, std::uint32_t b) {
    for (std::uint32_t i = 0; i < n; ++i) {
        std::uint32_t cnt = 0;
        for (std::uint32_t j = 0; j < n; ++j) if (get_value(table, n, i, j)) ++cnt;
        if (cnt < a || cnt > b) return false;
    }
    return true;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    if (n > 7) {
        std::cout << "error, big n";
        return 0;
    }
    std::uint32_t a, b;
    std::cin >> a >> b;
    std::ofstream of("out.txt");
    for (std::uint64_t table = 0; table < (1 << (n * n)); ++table) {
        if (!col_ok(table, n) || !row_ok(table, n, a, b)) continue;
        for (std::uint32_t i = 0; i < n; ++i) {
            for (std::uint32_t j = 0; j < n; ++j) {
                of << (get_value(table, n, i, j) ? '1' : '0');
            }
            of << '\n';
        }
        of << '\n';
    }
}
