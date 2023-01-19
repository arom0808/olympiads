#include <iostream>
#include <set>

std::set<std::uint32_t> fit_six_numbers{
        543210, 643210, 653210, 654210, 654310, 654320, 654321, 743210, 753210, 754210, 754310, 754320, 754321, 763210,
        764210, 764310, 764320,
        764321, 765210, 765310, 765320, 765321, 765410, 765420, 765421, 765430, 765431, 765432, 843210, 853210, 854210,
        854310, 854320, 854321, 863210, 864210, 864310, 864320, 864321, 865210, 865310, 865320, 865321, 865410, 865420,
        865421, 865430, 865431, 865432, 873210, 874210, 874310, 874320, 874321, 875210, 875310, 875320, 875321, 875410,
        875420, 875421, 875430, 875431, 875432, 876210, 876310, 876320, 876321, 876410, 876420, 876421, 876430, 876431,
        876432, 876510, 876520, 876521, 876530, 876531, 876532, 876540, 876541, 876542, 876543, 943210, 953210, 954210,
        954310, 954320, 954321, 963210, 964210, 964310, 964320, 964321, 965210, 965310, 965320, 965321, 965410, 965420,
        965421, 965430, 965431, 965432, 973210, 974210, 974310, 974320, 974321, 975210, 975310, 975320, 975321, 975410,
        975420, 975421, 975430, 975431, 975432, 976210, 976310, 976320, 976321, 976410, 976420, 976421, 976430, 976431,
        976432, 976510, 976520, 976521, 976530, 976531, 976532, 976540,
        976541, 976542, 976543, 983210, 984210, 984310, 984320, 984321, 985210, 985310, 985320, 985321, 985410, 985420,
        985421, 985430, 985431, 985432, 986210, 986310, 986320, 986321, 986410, 986420, 986421, 986430, 986431, 986432,
        986510, 986520, 986521, 986530, 986531, 986532, 986540, 986541, 986542, 986543, 987210, 987310, 987320, 987321,
        987410, 987420, 987421, 987430, 987431, 987432, 987510, 987520, 987521, 987530, 987531, 987532, 987540, 987541,
        987542, 987543, 987610, 987620, 987621, 987630, 987631, 987632, 987640, 987641, 987642, 987643, 987650, 987651,
        987652, 987653, 987654};

int main() {
    std::uint32_t divider, result = 0;
    std::cin >> divider;
    for (const auto &f_n: fit_six_numbers) if (f_n % divider == 0) ++result;
    std::cout << result;
    return 0;
}
