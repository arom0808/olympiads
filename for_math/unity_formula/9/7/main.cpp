//#include <iostream>
//
//bool IsZerosExists(std::uint32_t num) {
//    while (true) {
//        if (num % 10 == 0) return true;
//        num /= 10;
//        if (num == 0) break;
//    }
//    return false;
//}
//
//bool IsSum20AndMultiPair(std::uint32_t num) {
//    std::uint32_t amount = 0, pre_digit = 10;
//    while (true) {
//        if (pre_digit < 10) if (pre_digit * (num % 10) < 5) return false;
//        pre_digit = num % 10;
//        amount += num % 10;
//        num /= 10;
//        if (num == 0) break;
//    }
//    return amount == 20;
//}
//
//int main() {
//    std::uint32_t previous_percent_num = 987654321, one_percent = 9876543;
//    for (std::uint32_t num = 987654321; num > 0; --num) {
//        if (IsZerosExists(num)) {}
//        else if (IsSum20AndMultiPair(num)) {
//            std::cout << num;
//            return 0;
//        }
//        if (previous_percent_num - num >= one_percent) {
//            std::cout << 100 - static_cast<double>(num) / static_cast<double>(one_percent) << "%"
//                      << std::endl;
//            previous_percent_num = num;
//        }
//    }
//    return 0;
//}

//#include <iostream>
//#include <vector>
//
//std::uint32_t
//cnt_in(const std::vector<std::vector<bool>> &table, std::uint32_t x_1, std::uint32_t y_1, std::uint32_t x_2,
//       std::uint32_t y_2) {
//    std::uint32_t result = 0;
//    for (std::uint32_t i = y_1; i <= y_2; ++i) {
//        for (std::uint32_t j = x_1; j <= x_2; ++j) {
//            if (table[i][j]) ++result;
//        }
//    }
//    return result;
//}
//
//void Rec(std::vector<std::vector<bool>> &table, std::uint32_t pos) {
//    std::uint32_t x = pos % 4;
//    std::uint32_t y = pos / 4;
//    if (pos == 16) {
//        std::uint32_t block_1_1_cnt = cnt_in(table, 0, 0, 1, 1);
//        std::uint32_t block_1_2_cnt = cnt_in(table, 0, 0, 2, 1);
//        std::uint32_t block_1_3_cnt = cnt_in(table, 0, 0, 3, 1);
//        std::uint32_t block_1_4_cnt = cnt_in(table, 0, 0, 3, 1);
//        std::uint32_t block_1_5_cnt = cnt_in(table, 1, 0, 3, 1);
//        std::uint32_t block_1_6_cnt = cnt_in(table, 2, 0, 3, 1);
//        std::uint32_t block_2_1_cnt = cnt_in(table, 0, 0, 1, 2);
//        std::uint32_t block_2_6_cnt = cnt_in(table, 2, 0, 3, 2);
//        std::uint32_t block_3_1_cnt = cnt_in(table, 0, 0, 1, 3);
//        std::uint32_t block_3_6_cnt = cnt_in(table, 2, 0, 3, 3);
//        std::uint32_t block_4_1_cnt = cnt_in(table, 0, 0, 1, 3);
//        std::uint32_t block_4_6_cnt = cnt_in(table, 2, 0, 3, 3);
//        std::uint32_t block_5_1_cnt = cnt_in(table, 0, 1, 1, 3);
//        std::uint32_t block_5_6_cnt = cnt_in(table, 2, 1, 3, 3);
//        std::uint32_t block_6_1_cnt = cnt_in(table, 0, 2, 1, 3);
//        std::uint32_t block_6_2_cnt = cnt_in(table, 0, 2, 2, 3);
//        std::uint32_t block_6_3_cnt = cnt_in(table, 0, 2, 3, 3);
//        std::uint32_t block_6_4_cnt = cnt_in(table, 0, 2, 3, 3);
//        std::uint32_t block_6_5_cnt = cnt_in(table, 1, 2, 3, 3);
//        std::uint32_t block_6_6_cnt = cnt_in(table, 2, 2, 3, 3);
//        if (block_1_1_cnt != 1) return;
//        if (block_1_2_cnt != 2) return;
//        if (block_1_3_cnt != 2) return;
//        if (block_1_4_cnt != 2) return;
//        if (block_1_5_cnt != 2) return;
//        if (block_1_6_cnt != 1) return;
//        if (block_2_1_cnt != 2) return;
//        if (block_2_6_cnt != 2) return;
//        if (block_3_1_cnt != 2) return;
//        if (block_3_6_cnt != 2) return;
//        if (block_4_1_cnt != 2) return;
//        if (block_4_6_cnt != 2) return;
//        if (block_5_1_cnt != 2) return;
//        if (block_5_6_cnt != 1) return;
//        if (block_6_1_cnt != 1) return;
//        if (block_6_2_cnt != 1) return;
//        if (block_6_3_cnt != 2) return;
//        if (block_6_4_cnt != 2) return;
//        if (block_6_5_cnt != 1) return;
//        if (block_6_6_cnt != 1) return;
//        for (std::uint32_t i = 0; i < 4; ++i) {
//            for (std::uint32_t j = 0; j < 4; ++j) {
//                std::cout << (table[i][j] ? "1" : "_");
//            }
//            std::cout << std::endl;
//        }
//        for (std::uint32_t i = 0; i < 4; ++i) {
//            for (std::uint32_t j = 0; j < 4; ++j) {
//                if (table[i][j]) {
//                    std::cout << i + 2 << j + 2;
//                }
//            }
//        }
//        std::cout << std::endl << std::endl;
//    } else {
//        table[y][x] = false;
//        Rec(table, pos + 1);
//        table[y][x] = true;
//        Rec(table, pos + 1);
//    }
//}
//
//int main() {
//    std::vector<std::vector<bool>> table(4, std::vector<bool>(4, false));
//    Rec(table, 0);
//}

//#include <iostream>
//
//int main() {
//    for (std::int32_t a = -100; a <= 100; ++a) {
//        for (std::int32_t b = -100; b <= 100; ++b) {
//            for (std::int32_t c = -100; c <= 100; ++c) {
//                if (a + b + c != 0) continue;
//                if (a * 7 * 7 + b * 7 + c <= 60 || a * 7 * 7 + b * 7 + c >= 70) continue;
//                if (a * 8 * 8 + b * 8 + c <= 80 || a * 8 * 8 + b * 8 + c >= 90) continue;
//                std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
//                std::cout << "a * 9^2 + b * 9 + c = " << a * 9 * 9 + b * 9 + c;
//            }
//        }
//    }
//}

//#include <iostream>
//
//int main() {
//    std::uint32_t result = 0;
//    for (std::uint32_t i = 100; i < 1000; ++i)
//        if (i % 3 == 1 && i % 4 == 2) ++result;
//    std::cout << result;
//}


//#include <iostream>
//#include <vector>
//
//std::vector<double> result{27, 16};
//
//double f(std::uint32_t n) {
//    if (n < result.size()) return result[n];
//    double xn = result[n - 2] - (2 / result[n - 1]);
//    result.push_back(xn);
//    return xn;
//}
//
//int main() {
//    result.reserve(1000000000);
//    double r = f(2);
//    std::uint32_t n = 3;
//    while (std::abs(r) > 0.0001) {
//        r = f(n);
//        ++n;
//        std::cout << r << std::endl;
//    }
//    std::cout << r << "\n" << n;
//}



//#include <iostream>
//#include <set>
//
//std::set<std::pair<std::uint32_t, std::uint32_t>> used;
//std::set<std::uint32_t> finish_values;
//
//void rec(std::uint32_t n = 0, std::uint32_t step = 1) {
//    if (used.find({n, step}) != used.end()) return;
//    used.emplace(n, step);
//    if (step >= 28) {
//        finish_values.insert(n);
//        return;
//    }
//    if (step % 2 == 1) {
//        for (std::uint32_t c = 1; c < 5; ++c)
//            rec(n + c, step + 1);
//    } else {
//        for (std::uint32_t c = 1; c < 5; ++c) {
//            if (n >= c) {
//                rec(n - c, step + 1);
//            }
//        }
//    }
//}
//
//int main() {
//    rec();
//    for (const auto &f: finish_values) {
//        std::cout << f << " ";
//    }
//    std::cout << finish_values.size();
//}

//#include <iostream>
//#include <vector>
//
//void cc(std::uint32_t N, std::vector<std::uint32_t> &res) {
//    res.clear();
//    res.reserve(N);
//    std::uint32_t p = 2, i = 0, c = 2;
//    std::vector<std::uint32_t> a(N);
//    while (i < N) {
//        a[i] = i + 2;
//        ++i;
//    }
//    while (p < N) {
//        if (a[p] != 0) {
//            c = 2;
//            while (p * c < N) {
//                a[p * c] = 0;
//                c = c + 1;
//            }
//            res.push_back(p);
//        }
//        ++p;
//        c = 2;
//    }
//}
//
//int main() {
//    std::vector<std::uint32_t> res;
//    for (std::uint32_t N = 0; N < 10000; ++N) {
//        cc(N, res);
//        if (res.size() == 21) {
//            std::cout << "N: " << N << std::endl;
//            for (const auto &r: res) std::cout << r << " ";
//            std::cout << std::endl;
//            break;
//        }
//    }
//}

//#include <iostream>
//#include <vector>
//
//std::uint32_t GetDigitsNumber(std::uint32_t number) {
//    std::uint32_t digits = 0;
//    while (number) {
//        number /= 10;
//        ++digits;
//    }
//    return digits;
//}
//
//std::uint32_t GetDigit(std::uint32_t number, std::uint32_t n) {
//    auto d_n = GetDigitsNumber(number);
//    if (n >= d_n) throw std::exception();
//    for (std::uint32_t i = 0; i < d_n - 1 - n; ++i) number /= 10;
//    return number % 10;
//}
//
//void asd(std::vector<std::vector<std::uint32_t>> &M, std::uint32_t N) {
//    std::uint32_t i = 0, j = 0, C = 4;
//    while (i < C) {
//        j = 0;
//        while (j < C) {
//            std::uint32_t k = i;
//            while (k <= i + j) {
//                M[i][j] = M[i][j] + GetDigit(N, k);
//                ++k;
//            }
//            ++j;
//        }
//        ++i;
//    }
//}
//
//bool IsEq(const std::vector<std::vector<std::uint32_t>> &a, const std::vector<std::vector<std::uint32_t>> &b) {
//    if (a.size() != b.size()) return false;
//    for (std::uint32_t i = 0; i < a.size(); ++i) {
//        if (a[i].size() != b[i].size()) return false;
//        for (std::uint32_t j = 0; j < a[i].size(); ++j) {
//            if (a[i][j] != b[i][j]) return false;
//        }
//    }
//    return true;
//}
//
//int main() {
//    std::vector<std::vector<std::uint32_t>> zeros(4, std::vector<std::uint32_t>(4, 0));
//    auto M = zeros;
//    std::vector<std::vector<std::uint32_t>> need_res{{2, 5,  10, 18},
//                                                     {3, 8,  16, 23},
//                                                     {5, 13, 20, 24},
//                                                     {8, 15, 19, 25}};
//    for (std::uint32_t N = 2358746;; ++N) {
//        M = zeros;
//        asd(M, N);
//        bool asdasd = IsEq(M, need_res);
//        if (asdasd || N % 99991 == 0) {
//            std::cout << std::endl;
//            if (asdasd) std::cout << "FINISH!" << std::endl;
//            std::cout << "N: " << N << std::endl;
//            std::cout << "M: ";
//            std::cout << "[";
//            for (const auto &r: M) {
//                std::cout << "[";
//                for (const auto &t: r)
//                    std::cout << t << ", ";
//                std::cout << "], ";
//            }
//            std::cout << "]";
//            std::cout << std::endl;
//        }
//        if (asdasd) break;
//    }
//}

//#include <iostream>
//#include <algorithm>
//
//int main() {
//    const std::uint32_t b = 120;
//    for (std::uint32_t c = 1; c < 100000; ++c) {
//        for (std::uint32_t a = 1; a < c + b; ++a) {
//            if (!(a < b && b < c)) continue;
//            if (std::__gcd(a, b) != 1 || std::__gcd(a, c) != 1 || std::__gcd(b, c) != 1) continue;
//            if (a + b <= c || a + c <= b || c + b <= a) continue;
//            std::cout << a << " " << b << " " << c << std::endl;
//        }
//    }
//}

#include <iostream>

int main() {
    std::uint32_t min_sq = 123123123;
    std::uint32_t m_x, m_y, m_z, m_t;
    for (std::uint32_t x = 0; x < 150; ++x) {
        for (std::uint32_t y = 0; y < 150; ++y) {
            for (std::uint32_t z = 0; z < 150; ++z) {
                for (std::uint32_t t = 0; t < 150; ++t) {
                    if (x * y + z * t + 5 * (x * z + y * t) == 150) {
                        std::cout << x << " " << y << " " << z << " " << t << std::endl;
                        if (x * x + y * y + z * z + t * t < min_sq) {
                            min_sq = x * x + y * y + z * z + t * t;
                            m_x = x;
                            m_y = y;
                            m_z = z;
                            m_t = t;
                        }
                    }
                }
            }
        }
    }
    std::cout << std::endl;
    std::cout << "x: " << m_x << ", y: " << m_y << ", z: " << m_z << ", t: " << m_t << std::endl;
    std::cout << "min squares sum: " << min_sq;
}