#include <fstream>
#include <string.h>
#include <iostream>

int main() {
    char *s = new char[10000002];
    std::ifstream ifile("number.in");
    ifile.get(s + 1, 10000001);
    std::size_t strsize = strlen(s + 1);
    s[0] = s[1];
    s[1] = '\0';
    ifile.close();
    unsigned long long count = 0;
    std::size_t strlens, strlensi;
    int strcmpssi;
    for (int i = 1; i < strsize; ++i) {
        if (s[i + 1] == '0') {
            s[i] = s[i + 1];
            s[i + 1] = '\0';
            continue;
        }
        strlens = i;
        strlensi = strsize - i;
        if (strlens < strlensi) {
            ++count;
        } else if (strlens == strlensi) {
            strcmpssi = strcmp(s, s + i + 1);
            if (strcmpssi < 0)
                ++count;
            else if (strcmpssi == 0)
                ++count;
        }
        s[i] = s[i + 1];
        s[i + 1] = '\0';
    }
    std::ofstream ofile("number.out");
    ofile << count;
    ofile.close();
    return 0;
}
