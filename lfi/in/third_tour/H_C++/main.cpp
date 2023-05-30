#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

class SegmentsTree {
private:
    std::uint32_t N;
    std::vector<std::uint64_t> data;

    void Build(const std::vector<std::uint32_t> &vec, std::uint32_t v, std::uint32_t s_left, std::uint32_t s_right) {
        if (s_left == s_right) data[v] = vec[s_left];
        else {
            std::uint32_t s_middle = (s_left + s_right) / 2;
            Build(vec, v * 2, s_left, s_middle);
            Build(vec, v * 2 + 1, s_middle + 1, s_right);
            data[v] = data[v * 2] + data[v * 2 + 1];
        }
    }

    std::uint64_t
    InGetSum(std::uint32_t v, std::uint32_t s_left, std::uint32_t s_right, std::uint32_t left, std::uint32_t right) {
        if (left > right) return 0;
        if (left == s_left & right == s_right) return data[v];
        std::uint32_t s_middle = (s_left + s_right) / 2;
        return InGetSum(v * 2, s_left, s_middle, left, std::min(right, s_middle)) +
               InGetSum(v * 2 + 1, s_middle + 1, s_right, std::max(left, s_middle + 1), right);
    }

public:
    std::uint64_t GetSum(std::uint32_t left, std::uint32_t right) {
        return InGetSum(1, 0, N - 1, left, right);
    }

    explicit SegmentsTree(const std::vector<std::uint32_t> &vec) : N(vec.size()), data(4 * N, 0) {
        Build(vec, 1, 0, N - 1);
    }
};

int main() {
    std::uint32_t N, Q;
    std::cin >> N >> Q;
    std::vector<std::map<std::uint32_t, std::uint32_t>> changed(N);
    std::vector<std::uint32_t> start_nums(N);
    for (auto &&num: start_nums) std::cin >> num;
    SegmentsTree start_st(start_nums);
    char temp;
    std::uint32_t x, y, s, f, t;
    for (std::uint32_t i = 0; i < Q; ++i) {
        std::cin >> temp;
        if (temp == '1') {
            std::cin >> x >> y;
            --x;
            --y;
            changed[y] = changed[x];
        } else if (temp == '2') {
            std::cin >> x >> s >> y >> t;
            --x;
            --s;
            --y;
            --t;
            std::uint32_t new_x_value = start_nums[t];
            auto it_for_x = changed[y].find(t);
            if (it_for_x != changed[y].end()) new_x_value = it_for_x->second;
            std::uint32_t new_y_value = start_nums[s];
            auto it_for_y = changed[x].find(s);
            if (it_for_y != changed[x].end()) new_y_value = it_for_y->second;
            if (new_x_value == start_nums[s]) {
                if (it_for_y != changed[x].end()) changed[x].erase(it_for_y);
            } else {
                if (it_for_y == changed[x].end()) it_for_y = changed[x].emplace(s, 0).first;
                it_for_y->second = new_x_value;
            }
            if (new_y_value == start_nums[t]) {
                if (it_for_x != changed[y].end()) changed[y].erase(it_for_x);
            } else {
                if (it_for_x == changed[y].end()) it_for_x = changed[y].emplace(t, 0).first;
                it_for_x->second = new_y_value;
            }
        } else {
            std::cin >> x >> s >> f;
            --x;
            --s;
            --f;
            std::uint64_t sum = start_st.GetSum(s, f);
            auto first_it = changed[x].lower_bound(s);
            auto last_it = changed[x].upper_bound(f);
            if (first_it != last_it) {
                for (auto it = first_it; it != last_it; ++it) {
                    sum -= start_nums[it->first];
                    sum += it->second;
                }
            }
            std::cout << sum << "\n";
        }
    }
    return 0;
}
