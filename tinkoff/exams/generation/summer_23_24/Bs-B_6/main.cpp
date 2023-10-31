#include <iostream>
#include <vector>

struct ListEl {
    bool type = false;
    std::uint32_t pos = 0;
    ListEl *prev = nullptr, *next = nullptr;
};

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    std::vector<ListEl> mylist(n + 1);
    ListEl *reg_begin = &mylist.front(), *reg_end = &mylist.back();
    char c;
    for (std::uint32_t i = 0; i < n; ++i) {
        std::cin >> c;
        mylist[i].type = c == 'w';
        mylist[i].pos = i;
        mylist[i].next = &mylist[i + 1];
        mylist[i + 1].prev = &mylist[i];
    }
    std::vector<std::uint32_t> result;
    result.reserve(n);
    auto start = reg_begin;
    while (reg_begin != reg_end) {
        std::uint32_t off_cnt = 0, typ_cnt = 0;
        auto end = start;
        for (std::uint32_t i = 0; i < k + 1; ++i, end = end->next) {
            if (end->type) ++off_cnt;
            else ++typ_cnt;
        }
        for (; off_cnt != 1 || typ_cnt != k; start = start->next, end = end->next) {
            if (start->type) --off_cnt;
            else --typ_cnt;
            if (end->type) ++off_cnt;
            else ++typ_cnt;
        }
        for (auto it = start; it != end; it = it->next) result.push_back(it->pos);
        if (start->prev != nullptr) start->prev->next = end;
        if (start == reg_begin) reg_begin = end;
        end->prev = start->prev;
        start = end;
        for (std::uint32_t i = 0; start != reg_begin && i < k + 1; start = start->prev, ++i) {}
    }
    for (std::uint32_t i = 0; i < n; ++i) {
        std::cout << result[n - 1 - i] + 1 << " ";
        if ((i + 1) % (k + 1) == 0 && i != 0) std::cout << "\n";
    }
    return 0;
}