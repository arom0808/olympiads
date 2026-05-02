#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class SegmentTree {
public:
    struct Elem {
        uint32_t lr = 0, lnr = 0, nlr = 0, nlnr = 0;
    };

private:
    vector<Elem> elems;
    uint32_t size;

    void elem_upd(uint32_t id) {
        elems[id].lr = max(elems[id * 2].lnr + elems[id * 2 + 1].nlr,
                           max(elems[id * 2].lnr + elems[id * 2 + 1].lr,
                               elems[id * 2].lr + elems[id * 2 + 1].nlr));
        elems[id].nlr = max(elems[id * 2].nlnr + elems[id * 2 + 1].nlr,
                            max(elems[id * 2].nlnr + elems[id * 2 + 1].lr,
                                elems[id * 2].nlr + elems[id * 2 + 1].nlr));
        elems[id].lnr = max(elems[id * 2].lnr + elems[id * 2 + 1].nlnr,
                            max(elems[id * 2].lnr + elems[id * 2 + 1].lnr,
                                elems[id * 2].lr + elems[id * 2 + 1].nlnr));
        elems[id].nlnr = max(elems[id * 2].nlnr + elems[id * 2 + 1].nlnr,
                             max(elems[id * 2].nlnr + elems[id * 2 + 1].lnr,
                                 elems[id * 2].nlr + elems[id * 2 + 1].nlnr));
    }

    void init(uint32_t id, uint32_t l, uint32_t r, const vector<uint32_t> &nums) {
        if (l >= r) return;
        if (r - l == 1) elems[id].lr = nums[l];
        else {
            init(id * 2, l, (l + r) / 2, nums);
            init(id * 2 + 1, (l + r) / 2, r, nums);
            elem_upd(id);
        }
    }

    void in_update(uint32_t id, uint32_t l, uint32_t r, uint32_t req_i, uint32_t num) {
        if (l > req_i || r <= req_i) return;
        if (r - l == 1) elems[id].lr = num;
        else {
            in_update(id * 2, l, (l + r) / 2, req_i, num);
            in_update(id * 2 + 1, (l + r) / 2, r, req_i, num);
            elem_upd(id);
        }
    }

public:

    void update(uint32_t req_i, uint32_t num) {
        in_update(1, 0, size, req_i, num);
    }

    uint32_t get_max() {
        return max(elems[1].nlnr, max(elems[1].nlr, max(elems[1].lnr, elems[1].lr)));
    }

    explicit SegmentTree(const vector<uint32_t> &nums) : size(nums.size()), elems(nums.size() * 4) {
        init(1, 0, nums.size(), nums);
    }
};

int main() {
    uint32_t n, m;
    cin >> n >> m;
    vector<uint32_t> nums(n);
    for (auto &el: nums) cin >> el;
    SegmentTree st(nums);
    cout << st.get_max() << "\n";
    for (uint32_t i = 0, b, t; i < m; ++i) {
        cin >> b >> t;
        st.update(b - 1, t);
        cout << st.get_max() << "\n";
    }
    return 0;
}
