#include <iostream>
#include <vector>

using namespace std;

template<typename T>
inline int32_t num_len(T num) {
    int32_t len = 0;
    while (num) {
        num /= 10;
        ++len;
    }
    return len;
}

struct Block {
    char c = 'A';
    int32_t len = 0;

    Block() = default;

    Block(char c, int32_t len) : c(c), len(len) {}

    int32_t s_len() const {
        return len == 0 ? 0 : (len == 1 ? 1 : num_len(len) + 1);
    }
};

string g_gens = "AGCT";

vector<Block> blocks;
vector<Block> temp_blocks;
int32_t full_s_len = 0;
int32_t min_x, min_y, max_x, max_y;
char min_z, max_z;
int64_t min_res = 2e9, max_res = 0;

int32_t zipped_temp_blocks_size() {
    for (int32_t i = 0; i < temp_blocks.size();) {
        if (!temp_blocks[i].len) temp_blocks.erase(next(temp_blocks.begin(), i));
        else ++i;
    }
    for (int32_t i = 0; i + 1 < temp_blocks.size();) {
        if (temp_blocks[i].c == temp_blocks[i + 1].c) {
            temp_blocks[i + 1].len += temp_blocks[i].len;
            temp_blocks.erase(next(temp_blocks.begin(), i));
        } else ++i;
    }
    int32_t sz = 0;
    for (auto block: temp_blocks) sz += block.s_len();
    return sz;
}

int32_t add_pre_temp_blocks(int32_t block_id, int32_t cnt) {
    if (block_id != 0) temp_blocks.push_back(blocks[block_id - 1]);
    if (cnt != 0) temp_blocks.emplace_back(blocks[block_id].c, cnt);
    return block_id != 0 ? blocks[block_id - 1].s_len() : 0;
}

int32_t add_post_temp_blocks(int32_t block_id, int32_t cnt) {
    if (cnt != 0) temp_blocks.emplace_back(blocks[block_id].c, cnt);
    if (block_id + 1 != blocks.size()) temp_blocks.push_back(blocks[block_id + 1]);
    return block_id + 1 != blocks.size() ? blocks[block_id + 1].s_len() : 0;
}

int32_t change_if_change(int32_t block_id, int32_t pos, char c) {
    temp_blocks.clear();
    int32_t change = -blocks[block_id].s_len();
    change -= add_pre_temp_blocks(block_id, pos);
    temp_blocks.emplace_back(c, 1);
    change -= add_post_temp_blocks(block_id, blocks[block_id].len - pos - 1);
    change += zipped_temp_blocks_size();
    return change;
}

int32_t change_if_insert(int32_t block_id, int32_t pos, char c) {
    temp_blocks.clear();
    int32_t change = -blocks[block_id].s_len();
    change -= add_pre_temp_blocks(block_id, pos);
    temp_blocks.emplace_back(c, 1);
    change -= add_post_temp_blocks(block_id, blocks[block_id].len - pos);
    change += zipped_temp_blocks_size();
    return change;
}

int32_t change_if_erase(int32_t block_id, int32_t pos) {
    temp_blocks.clear();
    int32_t change = -blocks[block_id].s_len();
    change -= add_pre_temp_blocks(block_id, pos);
    change -= add_post_temp_blocks(block_id, blocks[block_id].len - pos - 1);
    change += zipped_temp_blocks_size();
    return change;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    string s;
    cin >> s;
    for (int32_t start = 0, end = 0;; start = end = end + 1) {
        for (; end < s.size() && s[end] != 'A' && s[end] != 'G' && s[end] != 'C' && s[end] != 'T'; ++end);
        if (end == s.size()) break;
        blocks.emplace_back(s[end], start != end ? std::stoi(s.substr(start, end - start)) : 1);
    }
    for (auto block: blocks) full_s_len += block.s_len();
    for (int32_t block_id = 0, pre_len = 0; block_id < blocks.size(); pre_len += blocks[block_id].len, ++block_id) {
        for (int32_t j = 1; j - 1 < blocks[block_id].len; j *= 10) {
            for (int32_t k = j - 1; k <= j + 1 && k < blocks[block_id].len; ++k) {
                for (int32_t _ = 0, pos = k; _ < 2; ++_, pos = blocks[block_id].len - k - 1) {
                    int32_t ch = change_if_erase(block_id, pos);
                    if (ch > max_res) max_res = ch, max_x = 2, max_y = pre_len + pos + 1;
                    if (ch < min_res) min_res = ch, min_x = 2, min_y = pre_len + pos + 1;
                    for (auto c: g_gens) {
                        ch = change_if_change(block_id, pos, c);
                        if (ch > max_res) max_res = ch, max_x = 3, max_y = pre_len + pos + 1, max_z = c;
                        if (ch < min_res) min_res = ch, min_x = 3, min_y = pre_len + pos + 1, min_z = c;
                        ch = change_if_insert(block_id, pos, c);
                        if (ch > max_res) max_res = ch, max_x = 1, max_y = pre_len + pos, max_z = c;
                        if (ch < min_res) min_res = ch, min_x = 1, min_y = pre_len + pos, min_z = c;
                    }
                }
            }
        }
    }
    if (min_x == 2) cout << min_x << " " << min_y << "\n";
    else cout << min_x << " " << min_y << " " << min_z << "\n";
    if (max_x == 2) cout << max_x << " " << max_y << "\n";
    else cout << max_x << " " << max_y << " " << max_z << "\n";
    return 0;
}
