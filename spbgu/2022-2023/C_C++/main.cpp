#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_map>
#include <bitset>


using one_block_t = std::uint_fast8_t;
const std::uint32_t one_block_size = 8;
const std::uint32_t one_block_variants_count = 256;

struct Queue_El {
    one_block_t num;
    std::uint32_t rate;
    Queue_El *first_child, *second_child;

    Queue_El(one_block_t num, std::uint32_t rate, Queue_El *first_child = nullptr, Queue_El *second_child = nullptr)
            : num(num), rate(rate), first_child(first_child), second_child(second_child) {}
};

void
TreeAnalise(Queue_El *root, std::unordered_map<one_block_t, std::string> &huffman_codes_for_blocks,
            std::string &now_str,
            std::uint64_t &res_bits_size) {
    if (root == nullptr) return;
    if (root->first_child == nullptr && root->second_child == nullptr) {
        huffman_codes_for_blocks.emplace(root->num, now_str);
        res_bits_size += static_cast<std::uint64_t>(root->rate) * now_str.size();
    }
    now_str.append("0");
    TreeAnalise(root->first_child, huffman_codes_for_blocks, now_str, res_bits_size);
    now_str.pop_back();
    now_str.append("1");
    TreeAnalise(root->second_child, huffman_codes_for_blocks, now_str, res_bits_size);
    now_str.pop_back();
}

void First() {
    std::uint32_t n, k1;
    std::cin >> n >> k1;
    std::vector<one_block_t> raw_bits_in_numbers(n / one_block_size + 1, 0);
    std::uint32_t buf;
    for (std::uint32_t i = 0; i < k1; ++i) {
        std::cin >> buf;
        raw_bits_in_numbers[buf / one_block_size] |= 1UL << (buf % one_block_size);
    }
    std::vector<std::uint32_t> n_rates(one_block_variants_count, 0);
    for (const auto &r: raw_bits_in_numbers) ++n_rates[r];
    auto alg_elems_cmp = [](Queue_El *a, Queue_El *b) { return a->rate > b->rate; };
    std::priority_queue<Queue_El *, std::vector<Queue_El *>, decltype(alg_elems_cmp)> alg_elems(alg_elems_cmp);
    for (std::uint32_t i = 0; i < one_block_variants_count; ++i) {
        if (n_rates[i] == 0) continue;
        alg_elems.emplace(new Queue_El(static_cast<one_block_t>(i), n_rates[i]));
    }
    while (alg_elems.size() > 1) {
        Queue_El *a = alg_elems.top();
        alg_elems.pop();
        Queue_El *b = alg_elems.top();
        alg_elems.pop();
        auto *root_a_b = new Queue_El(0, a->rate + b->rate, a, b);
        alg_elems.push(root_a_b);
    }
    std::unordered_map<one_block_t, std::string> unordered_huffman_codes_for_blocks;
    Queue_El *huffman_tree_root = alg_elems.top();
    alg_elems.pop();
    std::string buf_str;
    buf_str.reserve(257);
    std::uint64_t res_bits_size = 0;
    TreeAnalise(huffman_tree_root, unordered_huffman_codes_for_blocks, buf_str, res_bits_size);
    std::vector<std::string> huffman_codes_for_blocks(one_block_variants_count, "");
    for (const auto &p: unordered_huffman_codes_for_blocks) huffman_codes_for_blocks[p.first] = p.second;
    std::string result_bits_in_string;
    result_bits_in_string.reserve(res_bits_size);
    for (const auto &raw_block: raw_bits_in_numbers)
        result_bits_in_string.append(huffman_codes_for_blocks[raw_block]);
    //TODO: написать преобразование этой строки в массив unsigned char, добавить в ее начало таблицу символов. Потом вывести все это в отдельную функцию и использовать несколько раз.
}

void Second() {

}

int main() {
    std::string alg_type;
    std::cin >> alg_type;
    if (alg_type == "first") First();
    else Second();
    return 0;
}
