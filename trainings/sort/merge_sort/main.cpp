#include <iostream>
#include <vector>

void MergeSort(std::vector<std::int32_t> &numb, std::vector<std::int32_t> &buff, std::uint32_t left,
               std::uint32_t right, bool st = false) {
    if (left + 1 == right) {
        buff[left] = numb[left];
        return;
    }
    std::vector<std::int32_t> &numbers = (st ? buff : numb);
    std::vector<std::int32_t> &buffer = (st ? numb : buff);
    std::uint32_t middle = (left + right) / 2;
    MergeSort(numb, buff, left, middle, !st);
    MergeSort(numb, buff, middle, right, !st);
    for (std::uint32_t i = left, left_i = left, right_i = middle; i < right; ++i) {
        if (left_i < middle && right_i < right) {
            if (buffer[left_i] < buffer[right_i]) {
                numbers[i] = buffer[left_i];
                ++left_i;
            } else {
                numbers[i] = buffer[right_i];
                ++right_i;
            }
        } else if (left_i < middle) {
            numbers[i] = buffer[left_i];
            ++left_i;
        } else {
            numbers[i] = buffer[right_i];
            ++right_i;
        }
    }
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::int32_t> numbers(N), buffer(N);
    for (auto &&number: numbers) std::cin >> number;
    MergeSort(numbers, buffer, 0, N);
    for (const auto &number: numbers) std::cout << number << " ";
    return 0;
}
