#include <iostream>
#include <cmath>
#include <vector>
#include <map>


int main() {
    std::uint32_t N;
    std::cin >> N;
    auto cbrt = static_cast<std::uint32_t>(powl(N, static_cast<long double>(1) / static_cast<long double>(3)) +
                                           2);
    std::vector<std::uint32_t> cubes(cbrt);
    std::map<std::uint32_t, std::uint32_t> NumbersOnCubes;
    std::uint32_t c_c = 0;
    for (std::uint32_t x = 0; x < cbrt; ++x) {
        c_c = x * x * x;
        cubes[x] = c_c;
        NumbersOnCubes.insert({c_c, x});
    }
    std::uint32_t sum_cache = 0;
    for (const auto AC: cubes) {
        sum_cache = AC;
        if (sum_cache == N) {
            std::cout << NumbersOnCubes.at(AC);
            return 0;
        }
        for (const auto BC: cubes) {
            sum_cache += BC;
            if (sum_cache == N) {
                std::cout << (NumbersOnCubes.at(AC) == 0 ? "" :
                              std::to_string(NumbersOnCubes.at(AC)) + " ")
                          << NumbersOnCubes.at(BC);
                return 0;
            }
            for (const auto CC: cubes) {
                sum_cache += CC;
                if (sum_cache == N) {
                    std::cout << (NumbersOnCubes.at(AC) == 0 ? "" :
                                  std::to_string(NumbersOnCubes.at(AC)) + " ")
                              << (NumbersOnCubes.at(BC) == 0 ? "" :
                                  std::to_string(NumbersOnCubes.at(BC)) + " ")
                              << NumbersOnCubes.at(CC);
                    return 0;
                }
                for (const auto DC: cubes) {
                    sum_cache += DC;
                    if (sum_cache == N) {
                        std::cout << (NumbersOnCubes.at(AC) == 0 ? "" :
                                      std::to_string(NumbersOnCubes.at(AC)) + " ")
                                  << (NumbersOnCubes.at(BC) == 0 ? "" :
                                      std::to_string(NumbersOnCubes.at(BC)) + " ")
                                  << (NumbersOnCubes.at(CC) == 0 ? "" :
                                      std::to_string(NumbersOnCubes.at(CC)) + " ")
                                  << NumbersOnCubes.at(DC);
                        return 0;
                    }
                    for (const auto EC: cubes) {
                        sum_cache += EC;
                        if (sum_cache == N) {
                            std::cout << (NumbersOnCubes.at(AC) == 0 ? "" :
                                          std::to_string(NumbersOnCubes.at(AC)) + " ")
                                      << (NumbersOnCubes.at(BC) == 0 ? "" :
                                          std::to_string(NumbersOnCubes.at(BC)) + " ")
                                      << (NumbersOnCubes.at(CC) == 0 ? "" :
                                          std::to_string(NumbersOnCubes.at(CC)) + " ")
                                      << (NumbersOnCubes.at(DC) == 0 ? "" :
                                          std::to_string(NumbersOnCubes.at(DC)) + " ")
                                      << NumbersOnCubes.at(EC);
                            return 0;
                        }
                        for (const auto FC: cubes) {
                            sum_cache += FC;
                            if (sum_cache == N) {
                                std::cout << (NumbersOnCubes.at(AC) == 0 ? "" :
                                              std::to_string(NumbersOnCubes.at(AC)) +
                                              " ")
                                          << (NumbersOnCubes.at(BC) == 0 ? "" :
                                              std::to_string(NumbersOnCubes.at(BC)) +
                                              " ")
                                          << (NumbersOnCubes.at(CC) == 0 ? "" :
                                              std::to_string(NumbersOnCubes.at(CC)) +
                                              " ")
                                          << (NumbersOnCubes.at(DC) == 0 ? "" :
                                              std::to_string(NumbersOnCubes.at(DC)) +
                                              " ")
                                          << (NumbersOnCubes.at(EC) == 0 ? "" :
                                              std::to_string(NumbersOnCubes.at(EC)) +
                                              " ")
                                          << NumbersOnCubes.at(FC);
                                return 0;
                            }
                            for (const auto GC: cubes) {
                                sum_cache += GC;
                                if (sum_cache == N) {
                                    std::cout << (NumbersOnCubes.at(AC) == 0 ? "" :
                                                  std::to_string(NumbersOnCubes.at(AC)) + " ")
                                              << (NumbersOnCubes.at(BC) == 0 ? "" :
                                                  std::to_string(NumbersOnCubes.at(BC)) + " ")
                                              << (NumbersOnCubes.at(CC) == 0 ? "" :
                                                  std::to_string(NumbersOnCubes.at(CC)) + " ")
                                              << (NumbersOnCubes.at(DC) == 0 ? "" :
                                                  std::to_string(NumbersOnCubes.at(DC)) + " ")
                                              << (NumbersOnCubes.at(EC) == 0 ? "" :
                                                  std::to_string(NumbersOnCubes.at(EC)) + " ")
                                              << (NumbersOnCubes.at(FC) == 0 ? "" :
                                                  std::to_string(NumbersOnCubes.at(FC)) + " ")
                                              << NumbersOnCubes.at(GC);
                                    return 0;
                                }
                                for (const auto HC: cubes) {
                                    sum_cache += HC;
                                    if (sum_cache == N) {
                                        std::cout << (NumbersOnCubes.at(AC) == 0 ? "" :
                                                      std::to_string(NumbersOnCubes.at(AC)) + " ")
                                                  << (NumbersOnCubes.at(BC) == 0 ? "" :
                                                      std::to_string(NumbersOnCubes.at(BC)) + " ")
                                                  << (NumbersOnCubes.at(CC) == 0 ? "" :
                                                      std::to_string(NumbersOnCubes.at(CC)) + " ")
                                                  << (NumbersOnCubes.at(DC) == 0 ? "" :
                                                      std::to_string(NumbersOnCubes.at(DC)) + " ")
                                                  << (NumbersOnCubes.at(EC) == 0 ? "" :
                                                      std::to_string(NumbersOnCubes.at(EC)) + " ")
                                                  << (NumbersOnCubes.at(FC) == 0 ? "" :
                                                      std::to_string(NumbersOnCubes.at(FC)) + " ")
                                                  << (NumbersOnCubes.at(GC) == 0 ? "" :
                                                      std::to_string(NumbersOnCubes.at(GC)) + " ")
                                                  << NumbersOnCubes.at(HC);
                                        return 0;
                                    }
                                    sum_cache -= HC;
                                }
                                sum_cache -= GC;
                            }
                            sum_cache -= FC;
                        }
                        sum_cache -= EC;
                    }
                    sum_cache -= DC;
                }
                sum_cache -= CC;
            }
            sum_cache -= BC;
        }
    }
    std::cout << "IMPOSSIBLE";
    return 0;
}
