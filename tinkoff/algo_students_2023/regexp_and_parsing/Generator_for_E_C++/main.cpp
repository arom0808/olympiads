#include <iostream>
#include <random>
#include <fstream>

std::random_device dev;
std::uint32_t seed = dev();
std::mt19937 rng(seed);

std::uniform_int_distribution<std::uint32_t> n_1_100(1, 10), n_1_2(1, 2), n_0_25(0, 25);
std::bernoulli_distribution b_dist(0.1);

std::string GenerateSeq();

std::string GenerateChemElem() {
    std::uint32_t size = n_1_2(rng);
    std::string res;
    res += ('A' + n_0_25(rng));
    if (size > 1) res += ('a' + n_0_25(rng));
    return res;
}

std::string GenerateElem() {
    if (b_dist(rng)) return std::string("(") + GenerateSeq() + ")";
    return GenerateChemElem();
}

std::string GeneratePieceOfSeq() {
    std::uint32_t n = n_1_100(rng);
    return GenerateElem() + (n == 1 ? std::string("") : std::to_string(n));
}

std::string GenerateSeq() {
    std::uint32_t n = n_1_100(rng);
    std::string res;
    for (std::uint32_t i = 0; i < n; ++i) res += GeneratePieceOfSeq();
    return res;
}

std::string GeneratePieceOfFormula() {
    std::uint32_t n = n_1_100(rng);
    return (n == 1 ? std::string("") : std::to_string(n)) + GenerateSeq();
}

std::string GenerateFormula() {
    std::uint32_t n = n_1_100(rng);
    std::string res;
    for (std::uint32_t i = 0; i < n - 1; ++i) {
        res += GeneratePieceOfFormula();
        res += '+';
    }
    res += GeneratePieceOfFormula();
    return res;
}

int main() {
    std::ofstream o_f("out.txt");
    o_f << GenerateFormula() << "\n";
    std::uint32_t N = n_1_100(rng);
    o_f << N << "\n";
    for (std::uint32_t i = 0; i < N; ++i) o_f << GenerateFormula() << "\n";
    o_f.close();
    return 0;
}
