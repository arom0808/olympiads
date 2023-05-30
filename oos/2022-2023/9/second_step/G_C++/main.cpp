#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Song {
public:
    std::string name, author;
    std::uint32_t time_length = 0;
    std::uint32_t used_times = 0;

    Song() = default;

    Song(const std::string &author, const std::string &name) : author(author), name(name) {}

    Song(const std::pair<std::string, std::string> &pair) : author(pair.first), name(pair.second) {}

    bool operator<(const Song &other) const {
        if (author < other.author) return true;
        else if (author > other.author) return false;
        if (name < other.name) return true;
        return false;
    }

    bool operator==(const Song &other) const {
        return name == other.name && author == other.author;
    }

    bool operator!=(const Song &other) const {
        return !((*this) == other);
    }
};

class PlayList {
public:
    std::string name;
    std::vector<std::pair<std::string, std::string>> songs_inits;

    std::uint32_t next_song_id = 0;

    PlayList() = default;

    explicit PlayList(const std::string &name) : name(name) {}

    bool operator<(const PlayList &other) const {
        return name < other.name;
    }

    bool operator==(const PlayList &other) const {
        return name == other.name;
    }
};

int main() {
    std::string temp_line;
    std::getline(std::cin, temp_line);
    std::uint32_t t = std::stoi(temp_line);
    std::set<std::set<Song>> global_songs;
    for (std::uint32_t test_id = 0; test_id < t; ++test_id) {
        std::getline(std::cin, temp_line);
        std::getline(std::cin, temp_line);
        std::uint32_t k = std::stoi(temp_line);
        std::vector<PlayList> playlists(k);
        global_songs.insert({});
        std::set<Song> &songs = const_cast<std::set<Song> &>(*global_songs.find({}));
        for (auto &&playlist: playlists) {
            std::getline(std::cin, temp_line);
            std::uint32_t first_quote = temp_line.find('\"'), second_quote = temp_line.find('\"', first_quote + 1);
            playlist.name = std::string(temp_line, first_quote + 1, second_quote - first_quote - 1);
            std::uint32_t songs_count = std::stoi(std::string(temp_line, second_quote + 2));
            playlist.songs_inits.resize(songs_count);
            for (auto &&songs_init: playlist.songs_inits) {
                std::getline(std::cin, temp_line);
                Song this_song;
                std::uint32_t song_first_quote = 2, song_second_quote = temp_line.find('\"', song_first_quote + 1),
                        song_third_quote = song_second_quote + 5,
                        song_fourth_quote = temp_line.find('\"', song_third_quote + 1);
                this_song.name = std::string(temp_line, song_first_quote, song_second_quote - song_first_quote);
                this_song.author = std::string(temp_line, song_third_quote + 1,
                                               song_fourth_quote - song_third_quote - 1);
                std::uint32_t minutes = std::stoi(std::string(temp_line, song_fourth_quote + 6, 2));
                std::uint32_t seconds = std::stoi(std::string(temp_line, song_fourth_quote + 9, 2));
                this_song.time_length = minutes * 60 + seconds;
                songs.insert(this_song);
                songs_init.first = this_song.author;
                songs_init.second = this_song.name;
            }
        }
        std::sort(playlists.begin(), playlists.end());
        std::getline(std::cin, temp_line);
        std::uint32_t q = std::stoi(temp_line);
        for (std::uint32_t request_id = 0; request_id < q; ++request_id) {
            std::getline(std::cin, temp_line);
            bool do_type = temp_line.substr(0, 5) == "Start";
            std::uint32_t first_quote = temp_line.find('\"'), second_quote = temp_line.find('\"', first_quote + 1);
            std::string playlist_name = temp_line.substr(first_quote + 1, second_quote - first_quote - 1);
            std::uint32_t minutes = std::stoi(temp_line.substr(second_quote + 2, 2));
            std::uint32_t seconds = std::stoi(temp_line.substr(second_quote + 5, 2));
            auto this_playlist_it = std::lower_bound(playlists.begin(), playlists.end(), PlayList(playlist_name));
            if (do_type) this_playlist_it->next_song_id = 0;
            std::int32_t exp_time = minutes * 60 + seconds;
            while (exp_time > 0) {
                auto this_song_it = std::lower_bound(songs.begin(), songs.end(),
                                                     Song(this_playlist_it->songs_inits[this_playlist_it->next_song_id]));
                exp_time -= this_song_it->time_length;
                ++const_cast<std::uint32_t &>(this_song_it->used_times);
                ++this_playlist_it->next_song_id;
            }
        }
    }
    for (const auto swe: global_songs) {
        std::vector<Song> used_songs;
        used_songs.reserve(swe.size());
        for (const auto &ss: swe) if (ss.used_times > 0) used_songs.push_back(ss);
        std::cout << used_songs.size() << "\n";
        for (const auto &ss: used_songs)
            std::cout << "\"" << ss.name << "\" by \"" << ss.author << "\" times " << ss.used_times << "\n";
    }

    return 0;
}
