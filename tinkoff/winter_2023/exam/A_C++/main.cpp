#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Device {
    long double expiration_time;
    std::uint64_t consumption;

    bool operator<(const Device &other) const {
        return this->expiration_time < other.expiration_time;
    }

    explicit Device(const long double &expiration_time = 0, const std::uint64_t &consumption = 0)
            : expiration_time(expiration_time), consumption(consumption) {}
};

int main() {
    std::uint64_t n, x;
    std::uint64_t summary_consumption = 0;
    std::cin >> n >> x;
    std::vector<Device> devices(n);
    for (auto &&device: devices) {
        std::uint64_t d, e;
        std::cin >> d >> e;
        device.expiration_time = static_cast<long double>(e) / static_cast<long double>(d);
        device.consumption = d;
        summary_consumption += d;
    }
    if (x >= summary_consumption) {
        std::cout << "-1";
        return 0;
    }
    if (n == 1) {
        std::cout << devices.begin()->expiration_time;
        return 0;
    }
    std::sort(devices.begin(), devices.end());
    long double d_x = static_cast<long double>(x),
            cur_time = 0,
            cur_sum_consumption = 0;
    for (std::uint32_t i = 0; i < n - 1; ++i) {
        auto &this_device = devices[i], next_device = devices[i + 1];
        cur_sum_consumption += this_device.consumption;
        long double time_dif = next_device.expiration_time - this_device.expiration_time;
        long double need_time = time_dif * cur_sum_consumption / d_x;
        if (cur_time + need_time > next_device.expiration_time) {
            std::cout << std::fixed << std::setprecision(10)
                      << cur_time + (this_device.expiration_time - cur_time) * cur_sum_consumption /
                                    (cur_sum_consumption - d_x);
            return 0;
        }
        cur_time += need_time;
    }
    auto last_el = std::prev(devices.end());
    std::cout << std::fixed << std::setprecision(10)
              << cur_time + (last_el->expiration_time - cur_time) * static_cast<long double>(summary_consumption) /
                            (static_cast<long double>(summary_consumption) - d_x);
    return 0;
}
