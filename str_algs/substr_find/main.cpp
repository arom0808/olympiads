#include<iostream>
#include<string>

int main() {
    std::string line, pattern;
    int n, m, i, j, k, d[256];
    std::cin >> line >> pattern;
    n = line.size();
    m = pattern.size();
    for (i = 0; i < 256; ++i)
        d[i] = m;
    for (i = 0; i < m - 1; ++i)
        d[pattern[i]] = m - i - 1;
    i = m - 1;
    do {
        j = m - 1;
        k = i;
        while (j >= 0 && pattern[j] == line[k]) {
            j--;
            k--;
        }
        if (j < 0)
            std::cout << k + 1 << ' ';
        i += d[line[i]];
    } while (i < n);
    return 0;
}