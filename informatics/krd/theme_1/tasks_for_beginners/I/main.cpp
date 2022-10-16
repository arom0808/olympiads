#include <iostream>

struct TripCountAndPrice {
    std::uint32_t sixty_count = 0, ten_count = 0, one_count = 0;

    void operator+=(const TripCountAndPrice &other) {
        this->sixty_count += other.sixty_count;
        this->ten_count += other.ten_count;
        this->one_count += other.one_count;
    }

    std::uint32_t trip_count() const {
        return this->sixty_count * 60 + this->ten_count * 10 + this->one_count;
    }

    std::uint32_t price() const {
        return this->sixty_count * 440 + this->ten_count * 125 + this->one_count * 15;
    }
};

TripCountAndPrice MaxOfOne(std::uint32_t need_trip_count) {
    return TripCountAndPrice{0, 0, need_trip_count};
}

TripCountAndPrice MaxOfTen(std::uint32_t need_trip_count) {
    TripCountAndPrice first_variant{0, need_trip_count / 10};
    if (need_trip_count % 10 == 0) return first_variant;
    TripCountAndPrice second_variant{0, first_variant.ten_count + 1};
    first_variant += MaxOfOne(need_trip_count - first_variant.trip_count());
    if (first_variant.price() < second_variant.price()) return first_variant;
    else return second_variant;
}

TripCountAndPrice MaxOfSixty(std::uint32_t need_trip_count) {
    TripCountAndPrice first_variant{need_trip_count / 60};
    if (need_trip_count % 60 == 0) return first_variant;
    TripCountAndPrice second_variant{first_variant.sixty_count + 1};
    first_variant += MaxOfTen(need_trip_count - first_variant.trip_count());
    if (first_variant.price() < second_variant.price()) return first_variant;
    else return second_variant;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    TripCountAndPrice trip_counts = MaxOfSixty(n);
    std::cout << trip_counts.one_count << " " << trip_counts.ten_count << " " << trip_counts.sixty_count;
    return 0;
}