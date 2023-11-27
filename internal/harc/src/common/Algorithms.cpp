#include <harc/common/Algorithms.hpp>

#include <vector>

namespace harc {

    std::vector<std::string_view> split(
        std::string_view str,
        std::string_view delimiter
    ) {
        std::vector<std::string_view> ret;

        std::size_t pos_start = 0;
        std::size_t pos_end;
        std::size_t delim_len = delimiter.length();
        while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
            std::string_view token = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            if (!token.empty()) {
                ret.push_back(token);
            }
        }

        ret.push_back(str.substr(pos_start));
        return ret;
    }

    std::vector<std::string_view> split(
        std::string_view str,
        char delimiter
    ) {
        std::vector<std::string_view> ret;

        std::size_t pos_start = 0;
        std::size_t pos_end;
        while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
            std::string_view token = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + 1;
            if (!token.empty()) {
                ret.push_back(token);
            }
        }

        ret.push_back(str.substr(pos_start));
        return ret;
    }

    [[nodiscard]]
    std::string join(std::span<const std::string_view> strings, std::string_view delimiter) {
        if (strings.empty()) {
            return {};
        }

        std::size_t cumulative_delimiter_size = (strings.size() - 1) * delimiter.size();
        std::size_t cumulative_string_size = 0;
        for (auto& str : strings) {
            cumulative_string_size += str.size();
        }

        std::string ret;
        ret.reserve(cumulative_delimiter_size + cumulative_string_size);

        ret.append(strings[0]);
        for (std::size_t i = 1; i < strings.size(); ++i) {
            ret.append(strings[i]);
            ret.append(delimiter);
        }

        return ret;
    }

    std::string replace(
        std::string_view str,
        std::string_view target,
        std::string_view replacement
    ) {
        std::string ret;
        ret.reserve(str.size() + replacement.size());

        std::size_t pos_start = 0;
        std::size_t pos_end;
        while ((pos_end = str.find(target, pos_start)) != std::string::npos) {
            std::string_view token = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + 1;
            ret.append(token);
        }

        ret.append(str.substr(pos_start));

        return ret;
    }

    std::size_t demerau_levenstein_edit_distance_ascii(
        std::string_view str0,
        std::string_view str1
    ) {
        std::size_t width = str0.size() + 1;
        std::size_t height = str1.size() + 1;

        std::vector<std::uint32_t> table;
        table.resize(width * height);

        auto lookup = [&table, width] (std::size_t x, std::size_t y) -> std::uint32_t& {
            return table[y * width + x];
        };

        // Fill top row
        for (std::size_t i = 0; i < width; ++i) {
            //TODO: Complete
        }

        // Fill left column
        for (std::size_t i = 0; i < height; ++i) {
            //TODO: Complete
        }

        // Populate second row
        //TODO: Complete

        // Populate second columns
        //TODO: Complete

        // Fill rest of table
        //TODO: Complete

        return table.back();
    }

    std::size_t demerau_levenstein_edit_distance_utf8(
        std::string_view str0,
        std::string_view str1
    ) {
        return 0;
    }

    struct Rank_string_view_pair {
        std::size_t distance;
        std::string_view view;

        friend bool operator<(
            const Rank_string_view_pair& lhs,
            const Rank_string_view_pair& rhs
        ) {
            return lhs.distance < rhs.distance;
        }
    };

    std::vector<std::string_view> most_similar(
        std::string_view word,
        std::span<std::string_view> dictionary,
        similiarty_metric sim_func,
        std::size_t max_distance,
        std::size_t n
    ) {
        // Compute distances for each string.
        std::vector<Rank_string_view_pair> results;
        results.resize(dictionary.size());

        std::size_t occupancy = 0;
        for (auto& target_word : dictionary) {
            auto cost = sim_func(word, target_word);

            if (cost <= max_distance) {
                results[occupancy].distance = cost;
                results[occupancy].view = target_word;
                ++occupancy;
            }
        }
        results.resize(occupancy);

        // Construct vector containing results
        std::vector<std::string_view> ret;
        ret.resize(results.size());

        for (std::size_t i = 0; i < results.size(); ++i) {
            ret[i] = results[i].view;
        }

        return ret;
    }

}

