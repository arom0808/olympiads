#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>

class Nodes {
    std::vector<char> pc;
    std::vector<std::map<char, std::uint32_t>> go;
    std::vector<std::int32_t> suflink;
    std::vector<std::int32_t> parent;
    std::vector<std::set<std::uint32_t>> end_of_what_str_ids;
    std::vector<std::uint32_t> char_in_word_id;

public:

    char GetPC(std::uint32_t id) { return pc[id]; }

    std::uint32_t GetSufLink(std::uint32_t s_id) {
        if (suflink[s_id] != -1) return suflink[s_id];
        if (s_id == 0 || parent[s_id] == 0) suflink[s_id] = 0;
        else suflink[s_id] = GetGo(GetSufLink(parent[s_id]), GetPC(s_id));
        return suflink[s_id];
    }

    std::uint32_t GetGo(std::uint32_t s_id, char c) {
        auto it = go[s_id].find(c);
        if (it != go[s_id].end()) return it->second;
        if (s_id == 0) go[s_id].emplace(c, 0);
        else go[s_id].emplace(c, GetGo(GetSufLink(s_id), c));
        return go[s_id][c];
    }

    void GetAllEquals(const std::string &str, std::vector<std::set<std::uint32_t>> &results) {
        std::uint32_t node = 0;
        for (std::uint32_t i = 0; i < str.size(); ++i) {
            node = GetGo(node, str[i]);
            auto v = node;
            while (v != 0) {
                for (const auto &f: end_of_what_str_ids[v])
                    results[f].emplace(i + 2 - char_in_word_id[v]);
                v = GetSufLink(v);
            }
        }
    }

    explicit Nodes(const std::vector<std::string> &strs) : pc(1, '\0'), go(1), parent(1, -1), suflink(1, 0),
                                                           end_of_what_str_ids(1), char_in_word_id(1, 0) {
        pc.reserve(1000001);
        go.reserve(1000001);
        parent.reserve(1000001);
        suflink.reserve(1000001);
        end_of_what_str_ids.reserve(1000001);
        char_in_word_id.reserve(1000001);
        for (std::uint32_t str_id = 0; str_id < strs.size(); ++str_id) {
            if (strs[str_id].empty()) end_of_what_str_ids.front().emplace(str_id);
            std::uint32_t node = 0;
            for (char c: strs[str_id]) {
                auto it = go[node].find(c);
                if (it != go[node].end()) node = it->second;
                else {
                    std::uint32_t new_id = pc.size();
                    pc.push_back(c);
                    go.emplace_back();
                    go[node].emplace(c, new_id);
                    parent.emplace_back(node);
                    suflink.emplace_back(-1);
                    end_of_what_str_ids.emplace_back();
                    char_in_word_id.emplace_back(char_in_word_id[node] + 1);
                    node = new_id;
                }
            }
            end_of_what_str_ids[node].emplace(str_id);
        }
    }
};

int main() {
    std::ifstream in_f("inputik.txt");
    std::string S;
    std::getline(in_f, S);
    std::vector<std::string> strs;
    std::string tmp;
    std::getline(in_f, tmp);
    std::uint32_t size_strs = std::stoi(tmp);
    strs.resize(size_strs);
    for (auto &&str: strs) std::getline(in_f, str);
    Nodes nodes(strs);
    std::vector<std::set<std::uint32_t>> results(strs.size());
    nodes.GetAllEquals(S, results);
    std::ofstream out_f("outputik.txt");
    for (const auto &res: results) {
        out_f << res.size();
        for (const auto &v: res) out_f << " " << v;
        out_f << "\n";
    }
    return 0;
}