#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>

std::uint64_t
remove_cur_corp_el(bool cur_corp, std::map<std::size_t, std::pair<bool, std::vector<std::uint32_t>>> &skills,
                   std::vector<std::size_t> &learned, std::size_t index) {
    if (skills.size() <= index)
        return 0;
    if (skills[index].first != cur_corp) {
        return 0;
    }
    try {
        skills.at(index);
    } i = 0; i < skills[index].first)
}

std::uint64_t remove_l_t(const std::uint32_t &a, const std::uint32_t &b, bool cur_corp,
                         std::map<std::size_t, std::pair<bool, std::vector<std::uint32_t>>> &skills) {
    if (skills.empty())
        return 0;
}

std::uint64_t learn_time(const std::uint32_t &a, const std::uint32_t &b, bool cur_corp,
                         std::map<std::size_t, std::pair<bool, std::vector<std::uint32_t>>> &skills) {
    if (skills.empty())
        return 0;

}

int main() {
    std::ifstream f_in("jediacademy.in");
    std::size_t n, nn;
    f_in >> nn;
    std::map<std::size_t, std::pair<bool, std::vector<std::uint32_t>>> skills;
    for (std::size_t i = 0; i < nn; ++i) {
        skills[i] = std::pair<bool, std::vector<std::uint32_t>>();
        auto &cur_skill = skills[i];
        f_in >> n;
        cur_skill.first = (n == 2);
        f_in >> n;
        cur_skill.second.resize(n);
        for (auto &req_skill: cur_skill.second) {
            f_in >> req_skill;
        }
    }
    std::uint32_t a, b;
    f_in >> a >> b;
    f_in.close();
    std::uint64_t min_timeneed = UINT64_MAX;
    for (int sasdasdewr = 0; sasdasdewr < 2; ++sasdasdewr) {
        bool cur_corp = sasdasdewr;
        std::uint64_t timeneed = a + learn_time(a, b, cur_corp, skills);
        if (timeneed < min_timeneed)
            min_timeneed = timeneed;
    }
    std::ofstream f_out("jediacademy.out");
    f_out << min_timeneed;
    f_out.close();
    return 0;
}
