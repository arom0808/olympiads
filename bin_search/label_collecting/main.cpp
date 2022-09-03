#include <iostream>
#include <vector>
#include <algorithm>

using Album = std::pair<std::uint16_t, std::uint16_t>;
using Albums = std::vector<Album>;
using AlbumPair = std::pair<std::uint16_t, std::uint16_t>;

int main() {
    std::uint16_t N;
    std::cin >> N;
    Albums albums(N);
    std::uint32_t summary_labels_count = 0;
    for (std::uint32_t i = 0; i < N; ++i) {
        albums[i].first = i + 1;
        std::cin >> albums[i].second;
        summary_labels_count += albums[i].second;
    }
    std::sort(albums.begin(), albums.end(), [](const Album &a, const Album &b) { return a.second < b.second; });
    std::vector<AlbumPair> results;
    results.reserve(summary_labels_count / 2);
    while (albums.size() > 1) {
        auto album_it = albums.begin();
        auto next_album_it = std::next(album_it);
        for (std::uint16_t i = 0; i < album_it->second; ++i)
            results.emplace_back(album_it->first, next_album_it->first);
        next_album_it->second -= album_it->second;
        albums.erase(album_it);
    }
    std::cout << results.size() << std::endl;
    for (const auto &res: results)
        std::cout << res.first << " " << res.second << std::endl;
    return 0;
}
