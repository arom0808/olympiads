#include <iostream>

struct TripCountAndPrice {
    std::uint32_t sixty_count = 0, twenty_count = 0, ten_count = 0, five_count = 0, one_count = 0;

    void operator+=(const TripCountAndPrice &other) {
        this->sixty_count += other.sixty_count;
        this->twenty_count += other.twenty_count;
        this->ten_count += other.ten_count;
        this->five_count += other.five_count;
        this->one_count += other.one_count;
    }

    std::uint32_t trip_count() const {
        return this->sixty_count * 60 + this->twenty_count * 20 + this->ten_count * 10 + this->five_count * 5 +
               this->one_count;
    }

    std::uint32_t price() const {
        return this->sixty_count * 440 + this->twenty_count * 230 + this->ten_count * 125 + this->five_count * 70 +
               this->one_count * 15;
    }
};

TripCountAndPrice MaxOfOne(std::uint32_t need_trip_count) {
    return TripCountAndPrice{0, 0, 0, 0, need_trip_count};
}

TripCountAndPrice MaxOfFive(std::uint32_t need_trip_count) {
    TripCountAndPrice first_variant{0, 0, 0, need_trip_count / 5};
    if (need_trip_count % 5 == 0) return first_variant;
    TripCountAndPrice second_variant{0, 0, 0, first_variant.five_count + 1};
    first_variant += MaxOfOne(need_trip_count - first_variant.trip_count());
    if (first_variant.price() < second_variant.price()) return first_variant;
    else if (first_variant.price() == second_variant.price()) {
        if (first_variant.trip_count() > second_variant.trip_count()) return first_variant;
        else return second_variant;
    } else return second_variant;
}

TripCountAndPrice MaxOfTen(std::uint32_t need_trip_count) {
    TripCountAndPrice first_variant{0, 0, need_trip_count / 10};
    if (need_trip_count % 10 == 0) return first_variant;
    TripCountAndPrice second_variant{0, 0, first_variant.ten_count + 1};
    first_variant += MaxOfFive(need_trip_count - first_variant.trip_count());
    if (first_variant.price() < second_variant.price()) return first_variant;
    else if (first_variant.price() == second_variant.price()) {
        if (first_variant.trip_count() > second_variant.trip_count()) return first_variant;
        else return second_variant;
    } else return second_variant;
}

TripCountAndPrice MaxOfTwenty(std::uint32_t need_trip_count) {
    TripCountAndPrice first_variant{0, need_trip_count / 20};
    if (need_trip_count % 20 == 0) return first_variant;
    TripCountAndPrice second_variant{0, first_variant.twenty_count + 1};
    first_variant += MaxOfTen(need_trip_count - first_variant.trip_count());
    if (first_variant.price() < second_variant.price()) return first_variant;
    else if (first_variant.price() == second_variant.price()) {
        if (first_variant.trip_count() > second_variant.trip_count()) return first_variant;
        else return second_variant;
    } else return second_variant;
}

TripCountAndPrice MaxOfSixty(std::uint32_t need_trip_count) {
    TripCountAndPrice first_variant{need_trip_count / 60};
    if (need_trip_count % 60 == 0) return first_variant;
    TripCountAndPrice second_variant{first_variant.sixty_count + 1};
    first_variant += MaxOfTwenty(need_trip_count - first_variant.trip_count());
    if (first_variant.price() < second_variant.price()) return first_variant;
    else if (first_variant.price() == second_variant.price()) {
        if (first_variant.trip_count() > second_variant.trip_count()) return first_variant;
        else return second_variant;
    } else return second_variant;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    TripCountAndPrice trip_counts = MaxOfSixty(n);
    std::cout << trip_counts.one_count << " " << trip_counts.five_count << " " << trip_counts.ten_count << " "
              << trip_counts.twenty_count << " " << trip_counts.sixty_count;
    return 0;
}