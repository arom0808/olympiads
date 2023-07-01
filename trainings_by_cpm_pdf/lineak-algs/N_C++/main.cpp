#include <iostream>
#include <unordered_map>

struct PairHasher {
    std::size_t operator()(const std::pair<std::uint32_t, std::uint32_t> &k) const {
        using std::size_t;
        using std::hash;
        using std::string;

        return (static_cast<std::uint64_t>(k.first) << 32) | static_cast<std::uint64_t>(k.second);
    }
};


class IO {
    std::string _temp_;
    std::uint32_t requests_cnt = 0, max_req_cnt = 1e9;
    std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, bool, PairHasher> cache;
public:
    void set_max_req_cnt(std::uint32_t new_max_req_cnt) {
        max_req_cnt = new_max_req_cnt;
        cache.reserve(max_req_cnt);
    }

    bool is_right(std::uint32_t l, std::uint32_t r) {
        if (requests_cnt >= max_req_cnt) return true;
        auto it = cache.find({l, r});
        if (it != cache.end()) return it->second;
        std::cout << "? " << l + 1 << " " << r + 1 << "\n";
        std::cout.flush();
        std::cin >> _temp_;
        cache.emplace(std::pair<std::uint32_t, std::uint32_t>{l, r}, _temp_ == "Yes");
        ++requests_cnt;
        return _temp_ == "Yes";
    }
};

IO io;

void ProcessRight(std::uint32_t l, std::uint32_t r, std::string &str) {
    str[l] = '(';
    str[r] = ')';
    if (r - l == 1) return;
    else if (io.is_right(l + 1, r - 1)) ProcessRight(l + 1, r - 1, str);
    else {
        for (std::uint32_t i = l + 1; i < r; i += 2) {
            if (io.is_right(l, i)) {
                ProcessRight(l, i, str);
                ProcessRight(i + 1, r, str);
            }
        }
    }
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    if (n <= 16) io.set_max_req_cnt(150);
    else if (n <= 1000) io.set_max_req_cnt(10000);
    else io.set_max_req_cnt(100000);
    std::string str(n, '?');
    ProcessRight(0, n - 1, str);
    std::cout << "! " << str;
    return 0;
}
