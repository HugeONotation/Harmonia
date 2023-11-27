#ifndef HARMONIA_ALGORITHMS_HPP
#define HARMONIA_ALGORITHMS_HPP

#include <vector>
#include <string>
#include <string_view>
#include <span>

namespace harc {

    ///
    /// \param str String to split into multiple substrings
    /// \param delimiter String that will mark the boundary between consecutive
    /// substrings
    /// \return List of views over the results substrings
    [[nodiscard]]
    std::vector<std::string_view> split(
        std::string_view str,
        std::string_view delimiter
    );


    ///
    /// \param str String to split into multiple substrings
    /// \param delimiter Character that will mark the boundary between
    /// consecutive substrings
    /// \return List of views over the results substrings
    [[nodiscard]]
    std::vector<std::string_view> split(
        std::string_view str,
        char delimiter
    );

    ///
    /// \param strings Span of strings to join together
    /// \param delimiter Delimiter tobe paced between consecutive joined strings
    /// \return
    [[nodiscard]]
    std::string join(
        std::span<const std::string_view> strings,
        std::string_view delimiter = ""
    );

    ///
    /// \param str View over string to perform replacements on
    /// \param target Substring to search for
    /// \param replacement Substring to replace target with
    /// \return
    [[nodiscard]]
    std::string replace(
        std::string_view str,
        std::string_view target,
        std::string_view replacement
    );

    ///
    /// \param str0 ASCII-encoded string
    /// \param str1 ASCII-encoded string
    /// \param max Maximum edit distance to compute.
    /// \return The Damerau-Levenshtein edit distance between str0 and str1
    [[nodiscard]]
    std::size_t damerau_levenstein_edit_distance_ascii(
        std::string_view str0,
        std::string_view str1,
        std::size_t max = SIZE_MAX
    );

    ///
    /// \param str0 UTF8-encoded string
    /// \param str1 UTF8-encoded string
    /// \param max Maximum edit distance to compute.
    /// \return The Damerau-Levenshtein edit distance between str0 and str1
    [[nodiscard]]
    std::size_t damerau_levenstein_edit_distance_utf8(
        std::string_view str0,
        std::string_view str1,
        std::size_t max = SIZE_MAX
    );

    using similiarty_metric = std::size_t (*)(std::string_view, std::string_view);

    ///
    /// \param word
    /// \param dictionary
    /// \param sim_func
    /// \param n Number fo similar results to compute
    /// \return
    [[nodiscard]]
    std::vector<std::string_view> most_similar(
        std::string_view word,
        std::span<std::string_view> dictionary,
        similiarty_metric sim_func,
        std::size_t max_distance = SIZE_MAX,
        std::size_t n = 1
    );

}

#endif //HARMONIA_ALGORITHMS_HPP
