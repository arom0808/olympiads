#include <iostream>
#include <functional>

void AlphabetCycle(const std::function<void(char)> &func) {
    for (char i = 'a'; i <= 'z'; ++i) func(i);
}

std::vector<std::vector<std::uint32_t>>
        a_hashes{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,},
                 {1, 2, 3, 0,
                              1, 2, 3, 0, 1, 2,  3,  0,  1,  2,  3,  0,  1,  2,  3,  0,  1,  2,  3,  0,  1,  2,},
                 {1, 2, 3, 4, 5, 6, 7, 0, 1, 2,  3,  4,  5,  6,  7,  0,  1,  2,  3,  4,  5,  6,  7,  0,  1,  2,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9,
                                             10, 11, 12, 13, 14, 15, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2,
                        3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2,
                        3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2,
                        3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2,
                        3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},
                 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,},};

int main() {
    std::uint32_t n, M, h;
    std::cin >> n >> M >> h;
    std::uint32_t two_in_M = 1;
    std::uint64_t result = 0;
    if (M > 0) for (std::uint32_t i = 0; i < M; ++i) two_in_M *= 2;
    if (n == 1) {
        AlphabetCycle([two_in_M, h, &result](char a) {
            std::uint32_t hash = (0 ^ (a - 'a' + 1)) % two_in_M;
            if (hash == h) ++result;
        });
    } else if (n == 2) {
        AlphabetCycle([two_in_M, h, &result](char a) {
            std::uint32_t hash_a = ((0 ^ (a - 'a' + 1)) % two_in_M) * 57;
            AlphabetCycle([two_in_M, h, &result, hash_a](char b) {
                std::uint32_t hash = ((hash_a) ^ (b - 'a' + 1)) % two_in_M;
                if (hash == h) ++result;
            });
        });
    } else if (n == 3) {
        AlphabetCycle([two_in_M, h, &result](char a) {
            std::uint32_t hash_a = ((0 ^ (a - 'a' + 1)) % two_in_M) * 57;
            AlphabetCycle([two_in_M, h, &result, hash_a](char b) {
                std::uint32_t hash_b = (((hash_a) ^ (b - 'a' + 1)) % two_in_M) * 57;
                AlphabetCycle([two_in_M, h, &result, hash_b](char c) {
                    std::uint32_t hash = ((hash_b) ^ (c - 'a' + 1)) % two_in_M;
                    if (hash == h) ++result;
                });
            });
        });
    } else if (n == 4) {
        AlphabetCycle([two_in_M, h, &result](char a) {
            std::uint32_t hash_a = ((0 ^ (a - 'a' + 1)) % two_in_M) * 57;
            AlphabetCycle([two_in_M, h, &result, hash_a](char b) {
                std::uint32_t hash_b = (((hash_a) ^ (b - 'a' + 1)) % two_in_M) * 57;
                AlphabetCycle([two_in_M, h, &result, hash_b](char c) {
                    std::uint32_t hash_c = (((hash_b) ^ (c - 'a' + 1)) % two_in_M) * 57;
                    AlphabetCycle([two_in_M, h, &result, hash_c](char d) {
                        std::uint32_t hash = ((hash_c) ^ (d - 'a' + 1)) % two_in_M;
                        if (hash == h) ++result;
                    });
                });
            });
        });
    } else if (n == 5) {
        AlphabetCycle([two_in_M, h, &result](char a) {
            std::uint32_t hash_a = ((0 ^ (a - 'a' + 1)) % two_in_M) * 57;
            AlphabetCycle([two_in_M, h, &result, hash_a](char b) {
                std::uint32_t hash_b = (((hash_a) ^ (b - 'a' + 1)) % two_in_M) * 57;
                AlphabetCycle([two_in_M, h, &result, hash_b](char c) {
                    std::uint32_t hash_c = (((hash_b) ^ (c - 'a' + 1)) % two_in_M) * 57;
                    AlphabetCycle([two_in_M, h, &result, hash_c](char d) {
                        std::uint32_t hash_d = (((hash_c) ^ (d - 'a' + 1)) % two_in_M) * 57;
                        AlphabetCycle([two_in_M, h, &result, hash_d](char e) {
                            std::uint32_t hash = ((hash_d) ^ (e - 'a' + 1)) % two_in_M;
                            if (hash == h) ++result;
                        });
                    });
                });
            });
        });
    } else if (n == 6) {
        AlphabetCycle([two_in_M, h, &result](char a) {
            std::uint32_t hash_a = a_hashes[two_in_M][a - 'a'] * 57;
            AlphabetCycle([two_in_M, h, &result, hash_a](char b) {
                std::uint32_t hash_b = (((hash_a) ^ (b - 'a' + 1)) % two_in_M) * 57;
                AlphabetCycle([two_in_M, h, &result, hash_b](char c) {
                    std::uint32_t hash_c = (((hash_b) ^ (c - 'a' + 1)) % two_in_M) * 57;
                    AlphabetCycle([two_in_M, h, &result, hash_c](char d) {
                        std::uint32_t hash_d = (((hash_c) ^ (d - 'a' + 1)) % two_in_M) * 57;
                        AlphabetCycle([two_in_M, h, &result, hash_d](char e) {
                            std::uint32_t hash_e = (((hash_d) ^ (e - 'a' + 1)) % two_in_M) * 57;
                            AlphabetCycle([two_in_M, h, &result, hash_e](char f) {
                                std::uint32_t hash = ((hash_e) ^ (f - 'a' + 1)) % two_in_M;
                                if (hash == h) ++result;
                            });
                        });
                    });
                });
            });
        });
    }
    std::cout << result;
    return 0;
}
