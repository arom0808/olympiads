#include <iostream>

using namespace std;

enum class Dir {
    north, east, south, west
};

enum class Curs {
    forward, left, right, back
};

int main() {
    uint32_t rd, rc;
    cin >> rd >> rc;
    auto k1 = static_cast<Dir>(rd), k2 = Dir::north;
    auto p = static_cast<Curs>(rc);
    switch (p) {
        case Curs::forward:
            k2 = k1;
            break;
        case Curs::left:
            switch (k1) {
                case Dir::north:
                    k2 = Dir::west;
                    break;
                case Dir::east:
                    k2 = Dir::north;
                    break;
                case Dir::south:
                    k2 = Dir::east;
                    break;
                case Dir::west:
                    k2 = Dir::south;
            }
            break;
        case Curs::right:
            switch (k1) {
                case Dir::north:
                    k2 = Dir::east;
                    break;
                case Dir::east:
                    k2 = Dir::south;
                    break;
                case Dir::south:
                    k2 = Dir::west;
                    break;
                case Dir::west:
                    k2 = Dir::north;
            }
            break;
        case Curs::back:
            switch (k1) {
                case Dir::north:
                    k2 = Dir::south;
                    break;
                case Dir::east:
                    k2 = Dir::west;
                    break;
                case Dir::south:
                    k2 = Dir::north;
                    break;
                case Dir::west:
                    k2 = Dir::east;
            }
    }
    cout << static_cast<uint32_t>(k2);
    /* Мне искренне очень интересно, зачем такие извращения и почему нельзя использовать что-то более короткое по типу
        case Curs::left:
            k2 = static_cast<Dir>((static_cast<uint32_t>(k1) + 3) % 4);
            break;
        case Curs::right:
            k2 = static_cast<Dir>((static_cast<uint32_t>(k1) + 1) % 4);
            break;
        case Curs::back:
            k2 = static_cast<Dir>((static_cast<uint32_t>(k1) + 2) % 4);
            break;
     */
    return 0;
}
