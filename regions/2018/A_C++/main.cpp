#include <iostream>

int main() {
    std::uint64_t twos_count, threes_count, fours_count;
    std::cin >> twos_count >> threes_count >> fours_count;
    long double marks_sum = 2 * twos_count + 3 * threes_count + 4 * fours_count;
    std::uint64_t marks_count = twos_count + threes_count + fours_count;
    const std::uint64_t start_marks_count = marks_count;
    if (marks_sum / marks_count < 3.5) {
        for (std::uint64_t step_size = 1e14; step_size > 1; step_size /= 10) {
            while (marks_sum / marks_count < 3.5) {
                marks_count += step_size;
                marks_sum += step_size * 5;
            }
            marks_count -= step_size;
            marks_sum -= step_size * 5;
        }
        while (marks_sum / marks_count < 3.5) {
            ++marks_count;
            marks_sum += 5;
        }
    }
    std::cout << marks_count - start_marks_count;
    return 0;
}
