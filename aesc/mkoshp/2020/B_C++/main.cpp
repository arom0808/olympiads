#include <iostream>
#include <list>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

struct MS {
    std::uint32_t id = 0;
    std::list<std::uint32_t>::iterator cnt_iterator;
};

int main() {
    std::uint32_t n;
    std::cin >> n;
    char cmd;
    std::uint32_t last_ans = 1;
    auto cmp = [](const MS &a, const MS &b) {
        return a.id < b.id;
    };
    tree<MS, null_type, decltype(cmp), rb_tree_tag, tree_order_statistics_node_update> publishers;
//    std::map<std::uint32_t, std::uint32_t> publishers;
    std::list<std::uint32_t> global_cnts;
    for (std::uint32_t i = 0, a; i < n; ++i) {
        std::cin >> cmd >> a;
        if (cmd == '+') {
            auto it = publishers.find(MS(a));
            if (it != publishers.end()) {
                ++(*it->cnt_iterator);
            } else publishers.insert(MS(a, global_cnts.insert(global_cnts.end(), 1)));
            if (a <= last_ans) {
                ++last_ans;
            }
        } else {
            auto it = publishers.find(MS(a));
            if ((*it->cnt_iterator) == 1) {
                global_cnts.erase(it->cnt_iterator);
                publishers.erase(it);
            } else --(*it->cnt_iterator);
            if (a <= last_ans) {
                last_ans = publishers.order_of_key(MS(a)) + 1;
            }
        }
        if (a <= last_ans) {
            std::uint32_t min_add = last_ans, max_add = last_ans;
            while (true) {
                auto i1 = publishers.lower_bound(MS(min_add));
                auto i2 = publishers.upper_bound(MS(max_add));
                if (i1 == i2) break;
                min_add = max_add + 1;
                for (auto tit = i1; tit != i2; ++tit) {
                    max_add += (*tit->cnt_iterator);
                    last_ans += (*tit->cnt_iterator);
                }
            }
        }
        std::cout << last_ans << "\n";
    }
    return 0;
}
