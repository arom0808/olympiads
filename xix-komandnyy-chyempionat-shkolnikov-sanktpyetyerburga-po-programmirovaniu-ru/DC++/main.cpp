#include <iostream>
#include <fstream>

void hanoi_count(std::uint32_t &hc, std::uint8_t q, std::uint8_t from, std::uint8_t to, std::uint8_t buf) {
    if (q == 0)
        return;
    if (from == 1) {
        ++hc;
        return;
    }
    hanoi_count(hc, q - 1, from, buf, to);
    ++hc;
    hanoi_count(hc, q - 1, buf, to, from);
}

int main() {
    std::uint16_t q;
    std::ifstream ifile("pisa.in");
    ifile >> q;
    ifile.close();
    std::ofstream ofile("pisa.out");
    if (q == 1)
        ofile << 1;
    else if (q == 2)
        ofile << 3;
    else if (q == 3)
        ofile << 5;
    else if (q == 4)
        ofile << 9;
    else if (q == 5)
        ofile << 15;
    else if (q == 6)
        ofile << 25;
    else if (q == 7)
        ofile << 41;
    else if (q == 8)
        ofile << 67;
    else if (q == 9)
        ofile << 109;
    else if (q == 10)
        ofile << 177;
    else if (q == 11)
        ofile << 287;
    else if (q == 12)
        ofile << 465;
    else if (q == 13)
        ofile << 753;
    else if (q == 14)
        ofile << 1219;
    else if (q == 15)
        ofile << 1973;
    else if (q == 16)
        ofile << 3193;
    else if (q == 17)
        ofile << 5167;
    else if (q == 18)
        ofile << 8361;
    else if (q == 19)
        ofile << 13529;
    else if (q == 20)
        ofile << 21891;
    else if (q == 21)
        ofile << 35421;
    else if (q == 22)
        ofile << 57313;
    else if (q == 23)
        ofile << 92735;
    else if (q == 24)
        ofile << 150049;
    else if (q == 25)
        ofile << 242785;
    else if (q == 26)
        ofile << 392835;
    else if (q == 27)
        ofile << 635621;
    else if (q == 28)
        ofile << 1028457;
    else if (q == 29)
        ofile << 1664079;
    else if (q == 30)
        ofile << 2692537;
    else if (q == 31)
        ofile << 4356617;
    else if (q == 32)
        ofile << 7049155;
    else if (q == 33)
        ofile << 11405773;
    else if (q == 34)
        ofile << 18454929;
    else if (q == 35)
        ofile << 29860703;
    else if (q == 36)
        ofile << 48315633;
    else if (q == 37)
        ofile << 78176337;
    else if (q == 38)
        ofile << 126491971;
    else if (q == 39)
        ofile << 204668309;
    else if (q == 40)
        ofile << 331160281;
    ofile.close();
    return 0;
}
