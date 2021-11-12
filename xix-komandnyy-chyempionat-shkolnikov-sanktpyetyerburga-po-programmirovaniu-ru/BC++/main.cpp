#include <iostream>
#include <vector>
#include <fstream>

int main() {
    std::uint64_t n, m, h;
    bool isAllIdent = true;
    std::vector<std::pair<std::uint64_t, std::uint64_t>> sprouts;
    std::ifstream ifile("garden.in");
    std::ofstream ofile("garden.out");
    ifile >> n >> m >> h;
    sprouts.resize(n);
    for (auto sprout: sprouts) {
        ifile >> sprout.first >> sprout.second;
        sprout.first += (m - 1) * sprout.second;
        if (sprout.first < h) {
            ofile << "-1";
            ifile.close();
            ofile.close();
            return 0;
        } else if (sprout.first > h) {
            isAllIdent = false;
        }
    }
    if (isAllIdent)
        ofile << "0";
    else
        ofile << "1";
    ifile.close();
    ofile.close();
    return 0;
}
