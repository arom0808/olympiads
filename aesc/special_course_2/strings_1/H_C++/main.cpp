#include <iostream>

using namespace std;

class Bor {
    struct Vertex {
        Vertex *to[2] = {nullptr, nullptr};
        uint32_t terminal_cnt = 0, to_terminal_cnt = 0;
    };

    Vertex *root = new Vertex();
public:

    void add(uint32_t x) {
        auto v = root;
        for (uint32_t i = 0; i < 32; ++i) {
            ++v->to_terminal_cnt;
            if (!v->to[(x >> (31 - i)) & 1u]) v->to[(x >> (31 - i)) & 1u] = new Vertex();
            v = v->to[(x >> (31 - i)) & 1u];
        }
        ++v->to_terminal_cnt, ++v->terminal_cnt;
    }

    void erase(uint32_t x) {
        auto v = root;
        for (uint32_t i = 0; i < 32; ++i) {
            --v->to_terminal_cnt;
            v = v->to[(x >> (31 - i)) & 1u];
        }
        --v->to_terminal_cnt, --v->terminal_cnt;
    }

    uint32_t max_xor(uint32_t x) {
        auto v = root;
        for (uint32_t i = 0; i < 32; ++i) {
            if ((x >> (31 - i)) & 1u) {
                if (v->to[0] && v->to[0]->to_terminal_cnt) v = v->to[0];
                else {
                    x &= ~(1u << (31 - i));
                    v = v->to[1];
                }
            } else {
                if (v->to[1] && v->to[1]->to_terminal_cnt) {
                    x |= 1u << (31 - i);
                    v = v->to[1];
                } else v = v->to[0];
            }
        }
        return x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Bor bor;
    bor.add(0);
    uint32_t q;
    cin >> q;
    char c;
    for (uint32_t i = 0, x; i < q; ++i) {
        cin >> c >> x;
        if (c == '+') bor.add(x);
        else if (c == '-') bor.erase(x);
        else cout << bor.max_xor(x) << "\n";
    }
    return 0;
}
