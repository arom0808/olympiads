#include <iostream>
#include <random>
#include <cstdint>

using namespace std;

uint32_t seed = 11245351;
mt19937 rng(seed);

uniform_int_distribution d0_9(0, 9);

int32_t rand_dir() {
    int32_t d = d0_9(rng);
    if (d == 0) return 3;
    if (d == 1) return 2;
    if (d < 6) return 1;
    return 0;
}

const string dirs = "URDL";
char t_c;

bool ask(int32_t dir) {
    cout << dirs[dir] << endl;
    cin >> t_c;
    return t_c != 'N';
}

int main() {
    while (!ask(rand_dir())) {}
    return 0;
}
