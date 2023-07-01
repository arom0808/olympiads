#include <iostream>
#include <vector>

inline std::uint32_t GetDif(std::uint32_t a, std::uint32_t b) {
    if (a < b) return b - a;
    else return a - b;
}

int main() {
    std::uint32_t N, M;
    std::cin >> N;
    std::vector<std::uint32_t> shirts(N);
    for (auto &&shirt: shirts) std::cin >> shirt;
    std::cin >> M;
    std::vector<std::uint32_t> pants(M);
    for (auto &&pant: pants) std::cin >> pant;
    std::uint32_t pants_nergy_grater_i = pants.size();
    for (std::uint32_t i = 0; i < pants.size(); ++i) {
        if (pants[i] > shirts.front()) {
            pants_nergy_grater_i = i;
            break;
        }
    }
    std::uint32_t min_dif, res_1, res_2;
    if (pants_nergy_grater_i > 0 && pants_nergy_grater_i < pants.size()) {
        res_1 = shirts.front();
        if (GetDif(shirts.front(), pants[pants_nergy_grater_i]) <
            GetDif(shirts.front(), pants[pants_nergy_grater_i - 1])) {
            min_dif = GetDif(shirts.front(), pants[pants_nergy_grater_i]);
            res_2 = pants[pants_nergy_grater_i];
        } else {
            min_dif = GetDif(shirts.front(), pants[pants_nergy_grater_i - 1]);
            res_2 = pants[pants_nergy_grater_i - 1];
        }
    } else if (pants_nergy_grater_i == 0) {
        min_dif = GetDif(shirts.front(), pants[pants_nergy_grater_i]);
        res_1 = shirts.front();
        res_2 = pants[pants_nergy_grater_i];
    } else {
        std::cout << shirts.front() << " " << pants.back();
        return 0;
    }
    for (std::uint32_t sh_i = 1; sh_i < shirts.size(); ++sh_i) {
        for (; pants[pants_nergy_grater_i] < shirts[sh_i] &&
               pants_nergy_grater_i < pants.size(); ++pants_nergy_grater_i) {}
        auto this_dif = GetDif(shirts[sh_i], pants[pants_nergy_grater_i]);
        if (this_dif < min_dif) {
            min_dif = this_dif;
            res_1 = shirts[sh_i];
            res_2 = pants[pants_nergy_grater_i];
        }
        if (pants_nergy_grater_i > 0) {
            this_dif = GetDif(shirts[sh_i], pants[pants_nergy_grater_i - 1]);
            if (this_dif < min_dif) {
                min_dif = this_dif;
                res_1 = shirts[sh_i];
                res_2 = pants[pants_nergy_grater_i - 1];
            }
        }
        if (min_dif == 0) {
            std::cout << res_1 << " " << res_2;
            return 0;
        }
    }
    std::cout << res_1 << " " << res_2;
    return 0;
}
