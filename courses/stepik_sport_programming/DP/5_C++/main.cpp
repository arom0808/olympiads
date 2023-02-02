#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

enum class WhereDpValueFrom {
    first,
    second,
    middle
};

struct DpValue {
    std::uint32_t max_weight;
    std::uint32_t objs_count;
    WhereDpValueFrom where_from;

    explicit DpValue(std::uint32_t max_weight = 0, std::uint32_t objs_count = 0,
                     WhereDpValueFrom where_from = WhereDpValueFrom::middle)
            : max_weight(max_weight), objs_count(objs_count), where_from(where_from) {}
};

using DpRow = std::vector<DpValue>;
using Dp = std::vector<DpRow>;

using Coords = std::pair<std::uint32_t, std::uint32_t>;
using MaxValuesCoords = std::vector<Coords>;

using ObjectsSequence = std::set<std::uint32_t>;
using ObjectsSequences = std::set<ObjectsSequence>;

struct Object {
    std::uint32_t weight, value;

    explicit Object(std::uint32_t weight = 0, std::uint32_t value = 0) : weight(weight), value(value) {}
};

inline std::uint32_t
GetValueMaxWeightMinus(const Dp &dp, std::uint32_t i, std::uint32_t j, std::uint32_t i_minus, std::uint32_t j_minus) {
    if (i_minus > i) return 0;
    if (j_minus > j) return 0;
    return dp[i - i_minus][j - j_minus].max_weight;
}

inline std::uint32_t
GetValueObjectsCountMinus(const Dp &dp, std::uint32_t i, std::uint32_t j, std::uint32_t i_minus,
                          std::uint32_t j_minus) {
    if (i_minus > i) return 0;
    if (j_minus > j) return 0;
    return dp[i - i_minus][j - j_minus].objs_count;
}

Dp &GenerateDp(const std::vector<Object> &objects, Dp &dp, std::uint32_t n, std::uint32_t W) {
    dp.clear();
    dp.resize(n + 1, DpRow(W + 1));
    for (std::uint32_t i = 1; i < dp.size(); ++i) {
        for (std::uint32_t j = 1; j < dp[0].size(); ++j) {
            std::uint32_t first_variant_max_sum =
                    GetValueMaxWeightMinus(dp, i, j, 1, objects[i].weight) + objects[i].value;
            std::uint32_t second_variant_max_sum = GetValueMaxWeightMinus(dp, i, j, 1, 0);
            std::uint32_t first_variant_objects_count = GetValueObjectsCountMinus(dp, i, j, 1, objects[i].weight) + 1;
            std::uint32_t second_variant_objects_count = GetValueObjectsCountMinus(dp, i, j, 1, 0);
            WhereDpValueFrom where_from;
            if (first_variant_max_sum > second_variant_max_sum) {
                where_from = WhereDpValueFrom::first;
            } else if (second_variant_max_sum > first_variant_max_sum) {
                where_from = WhereDpValueFrom::second;
            } else {
                if (first_variant_objects_count < second_variant_objects_count)
                    where_from = WhereDpValueFrom::first;
                else if (first_variant_objects_count > second_variant_objects_count)
                    where_from = WhereDpValueFrom::second;
                else where_from = WhereDpValueFrom::middle;
            }
            if (where_from == WhereDpValueFrom::first)
                dp[i][j] = DpValue(first_variant_max_sum, first_variant_objects_count, where_from);
            else
                dp[i][j] = DpValue(second_variant_max_sum, second_variant_objects_count, where_from);
        }
    }
    return dp;
}

void GenerateMaxValuesCoords(const Dp &dp, MaxValuesCoords &max_values_coords) {
    std::uint32_t now_max = 0;
    max_values_coords.clear();
    max_values_coords.reserve(100);
    for (std::uint32_t i = 0; i < dp.size(); ++i) {
        for (std::uint32_t j = 0; j < dp[i].size(); ++j) {
            if (dp[i][j].max_weight > now_max) {
                max_values_coords.clear();
                max_values_coords.reserve(100);
                now_max = dp[i][j].max_weight;
            }
            if (dp[i][j].max_weight == now_max) max_values_coords.emplace_back(i, j);
        }
    }
}

void DeleteNotMinimalObjectsCountValuesFromMaxCoords(const Dp &dp, MaxValuesCoords &max_values_coords) {
    auto objects_count_sort_f = [&dp](const Coords &a, const Coords &b) {
        return dp[a.first][a.second].objs_count < dp[b.first][b.second].objs_count;
    };
    Coords coords_min_objs_cnt =
            *std::min_element(max_values_coords.begin(), max_values_coords.end(), objects_count_sort_f);
    std::uint32_t min_objects_count = dp[coords_min_objs_cnt.first][coords_min_objs_cnt.second].objs_count;
    auto objects_delete_if_f = [&dp, &min_objects_count](const Coords &coords) {
        return dp[coords.first][coords.second].objs_count > min_objects_count;
    };
    max_values_coords.erase(std::remove_if(max_values_coords.begin(), max_values_coords.end(), objects_delete_if_f),
                            max_values_coords.end());
}

void GenerateObjectSequenceRecursion(const Dp &dp, const Coords &coords, ObjectsSequences &objects_sequences) {

}

void
GenerateObjectsSequences(const Dp &dp, const MaxValuesCoords &max_values_coords, ObjectsSequences &objects_sequences) {
    ObjectsSequences temp_sequences;
    for (const auto &coords: max_values_coords) {
        GenerateObjectSequenceRecursion(dp, coords, temp_sequences);
        objects_sequences.merge(temp_sequences);
    }
}

int main() {
    std::uint32_t n, W;
    std::cin >> n >> W;
    std::vector<Object> objects(n);
    for (auto &&obj: objects) std::cin >> obj.weight >> obj.value;
    Dp dp;
    GenerateDp(objects, dp, n, W);
    MaxValuesCoords max_values_coords;
    GenerateMaxValuesCoords(dp, max_values_coords);
    DeleteNotMinimalObjectsCountValuesFromMaxCoords(dp, max_values_coords);
    ObjectsSequences objects_sequences;
    GenerateObjectsSequences(dp, max_values_coords, objects_sequences);
    return 0;
}
