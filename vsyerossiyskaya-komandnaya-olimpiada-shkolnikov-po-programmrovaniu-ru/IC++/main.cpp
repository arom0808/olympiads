#include <fstream>
#include <iostream>

int main() {
    std::uint64_t n, m;
    std::ifstream in_f("python.in");
    in_f >> n >> m;
    in_f.close();
    long double min, max;
    n += 1;
    max = (static_cast<long double>(n) - 0.0000000001) / static_cast<long double>(m);
    n -= 1;
    m += 1;
    min = static_cast<long double>(n) / (static_cast<long double>(m) - 0.0000000001);
    std::ofstream out_f("python.out");
    out_f << static_cast<std::uint64_t>(min) << '\n' << static_cast<std::uint64_t>(max);
    out_f.close();
    return 0;
}
