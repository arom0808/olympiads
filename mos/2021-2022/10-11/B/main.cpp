#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::uint64_t t = 0, cost, deliverycost, freedelivery;
    std::vector<std::uint64_t> results;
    std::ifstream inp("b_inp.txt");
    inp >> t;
    results.resize(t, 0);
    for (auto &res: results) {
        inp >> cost >> deliverycost >> freedelivery;
        if (cost < freedelivery)
            res = cost + deliverycost;
        else if (cost > freedelivery - 1 + deliverycost)
            res = cost;
        else
            res = freedelivery - 1 + deliverycost;
    }
    inp.close();
    std::ofstream out("b_out.txt");
    for (const auto &res: results)
        out << res << std::endl;
    out.close();
    return 0;
}
