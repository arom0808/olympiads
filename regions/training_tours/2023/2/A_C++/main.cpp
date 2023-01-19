#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>


struct Rang {
    std::string humans_arr;
    bool is_size_even;
    std::uint32_t not_even_pos_boys_count, even_pos_boys_count;

    std::uint32_t CountIfStartIsNotEven() const { return not_even_pos_boys_count; }

    std::uint32_t CountIfStartIsEven() const { return even_pos_boys_count; }

    void CountBoysOnNotEvenPositions(const std::string &HumansArr) {
        not_even_pos_boys_count = 0;
        if (!HumansArr.empty())
            for (std::uint32_t i = 0; i < HumansArr.size(); i += 2)
                if (HumansArr[i] == 'B') ++not_even_pos_boys_count;
    }

    void CountBoysOnEvenPositions(const std::string &HumansArr) {
        even_pos_boys_count = 0;
        if (HumansArr.size() >= 2)
            for (std::uint32_t i = 1; i < HumansArr.size(); i += 2)
                if (HumansArr[i] == 'B') ++even_pos_boys_count;
    }

    void CountBoys(const std::string &HumansArr) {
        CountBoysOnNotEvenPositions(HumansArr);
        CountBoysOnEvenPositions(HumansArr);
        is_size_even = (HumansArr.size() % 2 == 0);
        humans_arr = HumansArr;
    }


    explicit Rang() : not_even_pos_boys_count(0), even_pos_boys_count(0) {}

    explicit Rang(const std::string &HumansArr) {
        CountBoys(HumansArr);
    }
};

void ClearAndReserve(std::vector<Rang> &even_count_even_benefit,
                     std::vector<Rang> &even_count_not_even_benefit,
                     std::vector<Rang> &not_even_count_even_benefit,
                     std::vector<Rang> &not_even_count_not_even_benefit,
                     std::uint32_t N) {
    even_count_even_benefit.clear();
    even_count_not_even_benefit.clear();
    not_even_count_even_benefit.clear();
    not_even_count_not_even_benefit.clear();
    even_count_even_benefit.reserve(N);
    even_count_not_even_benefit.reserve(N);
    not_even_count_even_benefit.reserve(N);
    not_even_count_not_even_benefit.reserve(N);
}

void SortToFourVectors(const std::function<const std::string &(std::uint32_t i)> &F, std::uint32_t N,
                       std::vector<Rang> &even_count_even_benefit,
                       std::vector<Rang> &even_count_not_even_benefit,
                       std::vector<Rang> &not_even_count_even_benefit,
                       std::vector<Rang> &not_even_count_not_even_benefit) {
    ClearAndReserve(even_count_even_benefit, even_count_not_even_benefit, not_even_count_even_benefit,
                    not_even_count_not_even_benefit, N);
    Rang temp_rng;
    for (std::uint32_t i = 0; i < N; ++i) {
        const std::string &temp_str = F(i);
        temp_rng.CountBoys(temp_str);
        if (temp_str.size() % 2 == 0) {
            if (temp_rng.CountIfStartIsEven() > temp_rng.CountIfStartIsNotEven()) {
                even_count_even_benefit.push_back(temp_rng);
            } else {
                even_count_not_even_benefit.push_back(temp_rng);
            }
        } else {
            if (temp_rng.CountIfStartIsEven() > temp_rng.CountIfStartIsNotEven()) {
                not_even_count_even_benefit.push_back(temp_rng);
            } else {
                not_even_count_not_even_benefit.push_back(temp_rng);
            }
        }
    }
}

void InputRangesFromKeyboard(std::vector<Rang> &even_count_even_benefit,
                             std::vector<Rang> &even_count_not_even_benefit,
                             std::vector<Rang> &not_even_count_even_benefit,
                             std::vector<Rang> &not_even_count_not_even_benefit) {
    std::uint32_t N;
    std::cin >> N;
    std::string temp_str;
    auto F = [&temp_str](std::uint32_t _i) -> std::string & {
        std::cin >> temp_str;
        return temp_str;
    };
    SortToFourVectors(F, N, even_count_even_benefit, even_count_not_even_benefit, not_even_count_even_benefit,
                      not_even_count_not_even_benefit);
}

void StringRangesEnumerationNotEvenBoys(const std::function<void()> &F_if_boy_on_now_even,
                                        const std::function<void(char ch)> &F_any_anything,
                                        const std::vector<std::string> &ranges) {
    bool is_start_even = false;
    for (auto &range: ranges) {
        for (std::uint32_t i = 0; i < range.size(); ++i) {
            if (range[i] == 'B') {
                if (!is_start_even) { if (i % 2 == 0) F_if_boy_on_now_even(); else F_any_anything(range[i]); }
                else { if (i % 2 == 1) F_if_boy_on_now_even(); else F_any_anything(range[i]); }
            } else F_any_anything(range[i]);
        }
        if (range.size() % 2 == 1) is_start_even = !is_start_even;
    }
}

std::random_device dev;
//std::uint32_t seed = dev();
std::uint32_t seed = 489532438;
std::mt19937 rng(seed);

std::uint32_t GenerateRangesAndAnswer(std::vector<std::string> &ranges,
                                      std::vector<Rang> &even_count_even_benefit,
                                      std::vector<Rang> &even_count_not_even_benefit,
                                      std::vector<Rang> &not_even_count_even_benefit,
                                      std::vector<Rang> &not_even_count_not_even_benefit) {
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(5, 10), dist_rang_size(1, 20);
    std::uniform_real_distribution<float> dist_bit_probability(0.0, 1.0);
    std::bernoulli_distribution dist_bit(dist_bit_probability(rng));
    ranges.clear();
    ranges.resize(dist_n(rng));
    for (auto &&rang_str: ranges) {
        rang_str.resize(dist_rang_size(rng), 'G');
        for (auto &&ch: rang_str) if (dist_bit(rng)) ch = 'B';
    }
    std::sort(ranges.begin(), ranges.end());
    std::uint32_t max_boys_on_not_even_pos = 0, current_permutation = 0, need_permutations_count = 0;
    do {
        std::uint32_t now_boys_on_not_even_pos_count = 0;
        auto increase_now_boys_f = [&now_boys_on_not_even_pos_count]() { ++now_boys_on_not_even_pos_count; };
        StringRangesEnumerationNotEvenBoys(increase_now_boys_f, [](char ch) {}, ranges);
        if (now_boys_on_not_even_pos_count > max_boys_on_not_even_pos) {
            max_boys_on_not_even_pos = now_boys_on_not_even_pos_count;
            need_permutations_count = current_permutation;
        }
        ++current_permutation;
    } while (std::next_permutation(ranges.begin(), ranges.end()));

    if (need_permutations_count > 0)
        for (std::uint32_t i = 0; i < need_permutations_count; ++i)
            std::next_permutation(ranges.begin(), ranges.end());

    auto F = [&ranges](std::uint32_t i) -> std::string & {
        return ranges[i];
    };

    SortToFourVectors(F, ranges.size(), even_count_even_benefit, even_count_not_even_benefit,
                      not_even_count_even_benefit, not_even_count_not_even_benefit);
    return max_boys_on_not_even_pos;
}

std::uint32_t CountBoysOnNotEvenPositions(const std::vector<Rang> &ranges) {
    bool now_start_even = false;
    std::uint32_t result = 0;
    for (const auto &rang: ranges) {
        if (now_start_even) result += rang.CountIfStartIsEven();
        else result += rang.CountIfStartIsNotEven();
        if (!rang.is_size_even) now_start_even = !now_start_even;
    }
    return result;
}

std::uint32_t MySolution(std::vector<std::string> &my_ranges, std::vector<Rang> &even_count_even_benefit,
                         std::vector<Rang> &even_count_not_even_benefit,
                         std::vector<Rang> &not_even_count_even_benefit,
                         std::vector<Rang> &not_even_count_not_even_benefit) {
    std::vector<Rang> total_rang(
            even_count_even_benefit.size() + even_count_not_even_benefit.size() + not_even_count_even_benefit.size() +
            not_even_count_not_even_benefit.size());
    auto now_it = total_rang.begin();
    std::uint32_t now_pos = 0;
    now_it = std::copy(even_count_not_even_benefit.begin(), even_count_not_even_benefit.end(), total_rang.begin());
    now_pos += even_count_not_even_benefit.size();

    auto sort_even_benefit = [](const Rang &rang1, const Rang &rang2) {
        return rang1.CountIfStartIsEven() >= rang2.CountIfStartIsEven();
    };
    auto sort_not_even_benefit = [](const Rang &rang1, const Rang &rang2) {
        return rang1.CountIfStartIsNotEven() >= rang2.CountIfStartIsNotEven();
    };
    std::sort(not_even_count_even_benefit.begin(), not_even_count_even_benefit.end(), sort_even_benefit);
    std::sort(not_even_count_not_even_benefit.begin(), not_even_count_not_even_benefit.end(), sort_not_even_benefit);

    std::vector<Rang> not_evens_rang(not_even_count_even_benefit.size() + not_even_count_not_even_benefit.size());
    std::vector<Rang> bad_ranges;
    std::vector<std::reference_wrapper<Rang>> for_good_ranges_reference;
    bool bad_ranges_sort_type = false;
    bad_ranges.reserve(not_evens_rang.size());
    for_good_ranges_reference.reserve(not_evens_rang.size());
    for (std::uint32_t i = 0, e_b_i = 0, ne_b_i = 0; i < not_evens_rang.size(); ++i) {
        if (i % 2 == 1) {
            if (e_b_i < not_even_count_even_benefit.size()) {
                not_evens_rang[i] = not_even_count_even_benefit[e_b_i++];
            } else {
                for_good_ranges_reference.emplace_back(not_evens_rang[i]);
                bad_ranges.push_back(*std::prev(not_even_count_not_even_benefit.end()));
                not_even_count_not_even_benefit.erase(std::prev(not_even_count_not_even_benefit.end()));
                bad_ranges_sort_type = false;
            }
        } else {
            if (ne_b_i < not_even_count_not_even_benefit.size()) {
                not_evens_rang[i] = not_even_count_not_even_benefit[ne_b_i++];
            } else {
                for_good_ranges_reference.emplace_back(not_evens_rang[i]);
                bad_ranges.push_back(*std::prev(not_even_count_even_benefit.end()));
                not_even_count_even_benefit.erase(std::prev(not_even_count_even_benefit.end()));
                bad_ranges_sort_type = true;
            }
        }
    }
    auto bad_ranges_sort = [bad_ranges_sort_type](const Rang &rang1, const Rang &rang2) {
        if (!bad_ranges_sort_type) return rang1.CountIfStartIsEven() >= rang2.CountIfStartIsEven();
        else return rang1.CountIfStartIsNotEven() >= rang2.CountIfStartIsNotEven();
    };
    std::sort(bad_ranges.begin(), bad_ranges.end(), bad_ranges_sort);
    for (std::uint32_t i = 0; i < bad_ranges.size(); ++i) {
        for_good_ranges_reference[i].get() = bad_ranges[i];
    }
    if (!not_evens_rang.empty()) {
        total_rang[now_pos++] = not_evens_rang[0];
        std::advance(now_it, 1);
    }
    now_it = std::copy(even_count_even_benefit.begin(), even_count_even_benefit.end(), now_it);
    now_pos += even_count_even_benefit.size();
    if (not_evens_rang.size() >= 2) {
        now_it = std::copy(std::next(not_evens_rang.begin()), not_evens_rang.end(), now_it);
//        now_pos += not_evens_rang.size() - 1;
    }

    my_ranges.clear();
    for (const auto &rang: total_rang) my_ranges.push_back(rang.humans_arr);

    std::uint32_t result = CountBoysOnNotEvenPositions(total_rang);
    return result;
}

int main() {
    std::vector<Rang> even_count_even_benefit, even_count_not_even_benefit, not_even_count_even_benefit, not_even_count_not_even_benefit;
//    InputRangesFromKeyboard(even_count_even_benefit, even_count_not_even_benefit, not_even_count_even_benefit,
//                            not_even_count_not_even_benefit);
    std::cout << "seed: " << seed << std::endl << std::endl;
    std::vector<std::string> ranges, my_ranges;
    std::uint32_t right_res = GenerateRangesAndAnswer(ranges, even_count_even_benefit, even_count_not_even_benefit,
                                                      not_even_count_even_benefit, not_even_count_not_even_benefit);
    std::cout << "ranges:" << std::endl;
    for (const auto &range: ranges) std::cout << range << std::endl;
    std::cout << std::endl;
    std::cout << "full ranges: ";
    StringRangesEnumerationNotEvenBoys([]() { std::cout << "-"; }, [](char ch) { std::cout << ch; }, ranges);

//    for (const auto &range: ranges) std::cout << range;
    std::cout << std::endl << std::endl;
    std::cout << "right: " << right_res << std::endl;
    std::uint32_t my_res = MySolution(my_ranges, even_count_even_benefit, even_count_not_even_benefit,
                                      not_even_count_even_benefit, not_even_count_not_even_benefit);
    std::cout << "my: " << my_res << std::endl;
    std::cout << "full my ranges: ";
    StringRangesEnumerationNotEvenBoys([]() { std::cout << "-"; }, [](char ch) { std::cout << ch; }, my_ranges);
    return 0;
}
