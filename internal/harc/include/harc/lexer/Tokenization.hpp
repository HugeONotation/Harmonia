#ifndef HARC_TOKENIZATION_HPP
#define HARC_TOKENIZATION_HPP

#include "Tokens.hpp"

#include "Lexing_errors.hpp"

#include <string>
#include <vector>
#include <array>

namespace harc::lex {

    ///
    /// struct representing the tokenize of a Harmonia source file.
    ///
    struct Tokenization {

        ///
        /// List of types of tokens found
        ///
        std::vector<Token_type> types;

        ///
        /// List of types of tokens
        ///
        std::vector<std::uint32_t> source_indices;

        ///
        /// List of token lengths
        ///
        std::vector<std::uint32_t> lengths;

        ///
        /// List of line-column pairs of where tokens are located in memory
        ///
        std::vector<std::array<std::uint32_t, 2>> source_locations;

        ///
        /// Indices of first code point in each line
        ///
        std::vector<std::uint32_t> line_indices;

        ///
        /// Indices of matching token locations
        ///
        std::vector<std::uint32_t> pair_indices;

    };

}

#endif //HARC_TOKENIZATION_HPP
