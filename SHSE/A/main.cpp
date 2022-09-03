#include <iostream>
#include<fstream>
#include<vector>

class Room {
    std::uint32_t capacity;
    bool occupied;

public:
    explicit Room(std::uint32_t capacity = 1, bool occupied = false) : capacity(capacity), occupied(occupied) {}

    bool is_occupied() { return occupied; }

    std::uint32_t get_capacity() { return capacity; }

    void reserve() { occupied = true; }

    void free() { occupied = false; }
};

class Hotel {
private:
    std::size_t rooms_count;
    Room *rooms;

public:
    explicit Hotel(std::size_t rooms_count_local, Room *_rooms) {
        rooms_count = rooms_count_local;
        rooms = (Room *) malloc(sizeof(Room) * rooms_count);
        for (std::size_t i = 0; i < rooms_count; ++i) {
            rooms[i] = *(new Room(_rooms[i]));
        }
    }

    Hotel(const Hotel &hotel) {
        rooms_count = hotel.rooms_count;
        rooms = (Room *) malloc(sizeof(Room) * rooms_count);
        for (std::size_t i = 0; i < rooms_count; ++i) {
            rooms[i] = *(new Room(hotel.rooms[i]));
        }
    }

    ~Hotel() {
        if (rooms != nullptr)
            free(rooms);
    }

    double get_filled_percentage() const {
        return static_cast<double>(rooms_count - count_free()) / static_cast<double>(rooms_count) * 100.0;
    }

    Room &get_room(std::size_t p) { return rooms[p]; }

    void free_room(std::size_t p) { rooms[p].free(); }

    std::size_t count_free() const {
        std::size_t res = 0;
        for (std::size_t i = 0; i < rooms_count; ++i) if (!rooms[i].is_occupied())++res;
        return res;
    }

    std::int64_t find_room(std::uint32_t k) {
        for (std::size_t i = 0; i < rooms_count; ++i) {
            if ((!rooms[i].is_occupied()) && rooms[i].get_capacity() == k) {
                rooms[i].reserve();
                return static_cast<std::int64_t>(i);
            }
        }
        return -1;
    }

    std::size_t get_room_count() { return rooms_count; }
};

Hotel load_hotel(std::ifstream &file) {
    std::size_t rooms_count;
    file >> rooms_count;
    Room *rooms = (Room *) malloc(sizeof(Room) * rooms_count);
    std::uint32_t uitmp;
    bool btmp;
    for (std::size_t i = 0; i < rooms_count; ++i) {
        file >> uitmp >> btmp;
        (&rooms[i])->~Room(uitmp, btmp);
    }
    Hotel hotel(rooms_count, rooms);
    delete[]rooms;
    return hotel;
}

void save_hotel(std::ofstream &file, Hotel h) {
    file << h.get_room_count() << std::endl;
    for (std::size_t i = 0; i < h.get_room_count(); ++i) {
        file << h.get_room(i).get_capacity() << " " << h.get_room(i).is_occupied() << std::endl;
    }
}

int main() {
    std::ifstream inp("source.txt");
    std::uint32_t K;
    inp >> K;
    std::vector<Hotel> hotels(K, Hotel(0, nullptr));
    for (auto &&hotel: hotels)
        hotel = load_hotel(inp);
    std::vector<double> effs(K);
    double sum = 0;
    for (std::size_t i = 0; i < K; ++i) {
        effs[i] = hotels[i].get_filled_percentage();
        sum += effs[i];
    }
    double sr = sum / static_cast<double>(K);
    std::vector<Hotel> res;
    for (const Hotel &hotel: hotels)
        if (hotel.get_filled_percentage() > sr)
            res.push_back(hotel);
    std::ofstream out("destination.txt");
    out << res.size()<<std::endl;
    for (const auto &h: res) save_hotel(out, h);
    out.close();
    return 0;
}