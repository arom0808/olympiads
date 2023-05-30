#include <iostream>
#include <vector>
#include <map>
#include <set>

class Nodes {
    std::vector<char> pc;
    std::vector<std::map<char, std::uint32_t>> go;
    std::vector<std::int32_t> suflink;

public:

    static std::int32_t GetParentId(std::uint32_t id) { return static_cast<std::int32_t>(id) - 1; }

    char GetPC(std::uint32_t id) { return pc[id]; }

    bool IsTerminal(std::uint32_t s_id) { return s_id == suflink.size() - 1; }

    std::uint32_t GetSufLink(std::uint32_t s_id) {
        if (suflink[s_id] != -1) return suflink[s_id];
        if (s_id == 0 || s_id == 1) suflink[s_id] = 0;
        else suflink[s_id] = GetGo(GetSufLink(s_id - 1), GetPC(s_id));
        return suflink[s_id];
    }

    std::uint32_t GetGo(std::uint32_t s_id, char c) {
        auto it = go[s_id].find(c);
        if (it != go[s_id].end()) return it->second;
        if (s_id == 0) go[s_id].emplace(c, 0);
        else go[s_id].emplace(c, GetGo(GetSufLink(s_id), c));
        return go[s_id][c];
    }

    void GetAllEquals(const std::string &str, std::set<std::uint32_t> &results) {
        std::uint32_t node = 0;
        for (std::uint32_t i = 0; i < str.size(); ++i) {
            node = GetGo(node, str[i]);
            auto v = node;
            while (v != 0) {
                if (IsTerminal(v)) results.emplace(i);
                v = GetSufLink(v);
            }
        }
    }

    Nodes(const std::string &str) : pc(str.size() + 1, '\0'), go(str.size() + 1),
                                    suflink(str.size() + 1, -1) {
        for (std::uint32_t i = 0; i < str.size(); ++i) {
            pc[i + 1] = str[i];
            go[i].emplace(str[i], i + 1);
        }
    }
};

int main() {
    std::string S, T;
    std::cin >> S >> T;
    Nodes nodes(T);
    std::set<std::uint32_t> results;
    nodes.GetAllEquals(S, results);
    for (const auto &i: results) std::cout << i + 1 - T.size() << " ";
    return 0;
}