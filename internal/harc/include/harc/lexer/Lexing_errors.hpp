#ifndef HARMONIA_LEXING_ERRORS_HPP
#define HARMONIA_LEXING_ERRORS_HPP

#include <cstdint>

namespace harc::lex {

    enum class Error_code : std::uint16_t {
        NO_ERROR,

        LEXING_ERROR,

        // utf8 validation errors
        INVALID_UTF8,
        INVALID_UTF8_NON_SHORTEST_FORM,
        INVALID_UTF8_HIGH_TWO_BITS_NOT_SET_IN_CONTINUATION_BYTES,
        INVALID_UTF8_EXCESSIVE_CONTINUATION_BYTES,
        INVALID_UTF8_CODEPOINT_IS_SURROGATE_VALUE,
        INVALID_UTF8_CODEPOINT_GREATER_THAN_U10FFFF,

        // Token balancing errors
        UNMATCHED_PARENTHESIS,
        UNMATCHED_CURLY_BRACKET,
        UNMATCHED_ANGLE_BRACKET,
    };

    struct Error {
        lex::Error_code error_code{};

        std::uint32_t error_begin = 0;
        std::uint32_t error_end = 0;
    };

}

#endif //HARMONIA_LEXING_ERRORS_HPP
