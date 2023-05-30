#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <chrono>

enum class ActType {
    reg,
    change,
    send
};

struct ResultForUsers {
    std::uint32_t id, total, top_count, top_id;

    ResultForUsers(std::uint32_t id, std::uint32_t total, std::uint32_t top_count, std::uint32_t top_id) :
            id(id), total(total), top_count(top_count), top_id(top_id) {}
};

struct Action {
    std::uint32_t t;
    std::uint32_t id;
    std::string h_1, h_2;
    ActType type;

    Action(std::uint32_t t, std::uint32_t id, std::string &h_1) : t(t), id(id), h_1(std::move(h_1)),
                                                                  type(ActType::reg) {}

    Action(std::uint32_t t, std::string &h_1, std::string &h_2, ActType type) : t(t), h_1(std::move(h_1)),
                                                                                h_2(std::move(h_2)), type(type) {}

    bool operator<(const Action &action) const { return t < action.t; }
};

struct User {
    std::uint32_t total_msg_get;
    std::map<std::uint32_t, std::uint32_t> get_count_on_id;

    User(std::uint32_t total_msg_get = 0) : total_msg_get(total_msg_get) {}
};

int main() {
    auto start = std::chrono::steady_clock::now();
    std::ifstream in_file("in.txt");
    std::ofstream out_file("out.txt");
    std::uint32_t T;
    in_file >> T;
    std::string temp1, temp2, temp3;
    std::vector<std::vector<ResultForUsers>> results(T);
    for (auto &&result: results) {
        std::set<Action> actions;
        std::map<std::string, std::uint32_t> id_on_handle;
        std::set<std::uint32_t> ids;
        std::map<std::uint32_t, User> users;
        std::uint32_t reg_cnt, change_cnt, send_cnt;
        in_file >> reg_cnt;
        for (std::uint32_t i = 0, id, t; i < reg_cnt; ++i) {
            in_file >> temp1 >> id >> temp1 >> temp2 >> temp1 >> t;
            actions.emplace(t, id, temp2);
        }
        in_file >> change_cnt;
        for (std::uint32_t i = 0, t; i < change_cnt; ++i) {
            in_file >> temp1 >> temp2 >> temp1 >> temp3 >> temp1 >> t;
            actions.emplace(t, temp2, temp3, ActType::change);
        }
        in_file >> send_cnt;
        for (std::uint32_t i = 0, t; i < send_cnt; ++i) {
            in_file >> temp1 >> temp1 >> temp2 >> temp1 >> temp3 >> temp1 >> t;
            actions.emplace(t, temp2, temp3, ActType::send);
        }
        for (const auto &action: actions) {
            if (action.type == ActType::reg) {
                if (id_on_handle.find(action.h_1) != id_on_handle.end()) continue;
                ids.insert(action.id);
                id_on_handle.emplace(action.h_1, action.id);
                users.emplace(action.id, 0);
            } else if (action.type == ActType::change) {
                if (id_on_handle.find(action.h_2) != id_on_handle.end()) continue;
                auto kk = id_on_handle.extract(action.h_1);
                kk.key() = action.h_2;
                id_on_handle.emplace(kk.key(), kk.mapped());
            } else {
                std::uint32_t id_from = id_on_handle.find(action.h_1)->second,
                        id_to = id_on_handle.find(action.h_2)->second;
                auto us = users.find(id_to);
                ++us->second.total_msg_get;
                auto asda = us->second.get_count_on_id.find(id_from);
                if (asda == us->second.get_count_on_id.end()) us->second.get_count_on_id.emplace(id_from, 1);
                else ++asda->second;
            }
        }
        result.reserve(ids.size());
        for (const auto &user: users) {
            if (user.second.total_msg_get == 0) {
                result.emplace_back(user.first, 0, 0, *ids.begin());
                continue;
            }
            auto max_it = std::max_element(user.second.get_count_on_id.begin(), user.second.get_count_on_id.end(),
                                           [](const std::pair<const std::uint32_t, std::uint32_t> &a,
                                              const std::pair<const std::uint32_t, std::uint32_t> &b) {
                                               return a.second < b.second;
                                           });
            result.emplace_back(user.first, user.second.total_msg_get, max_it->second, max_it->first);
        }
    }
    for (const auto &result: results) {
        out_file << result.size() << "\n";
        for (const auto &us: result)
            out_file << us.id << " RECEIVED " << us.total << " TOP " << us.top_count << " FROM " << us.top_id << "\n";
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return 0;
}
