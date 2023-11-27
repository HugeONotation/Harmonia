#ifndef HARC_TOKENS_HPP
#define HARC_TOKENS_HPP

#include <harc/Logging.hpp>

#include <cstdint>

namespace harc {

    enum class Token_type : std::uint8_t {
        NULL_TOKEN = 0,

        // The following enum values are chosen to correspond to their ASCII
        // values to open optimizations up.
        EXCLAMATION = '!',
        CARET = '^',
        AMPERSAND = '&',
        PIPE = '|',
        SQUIGGLE = '~',
        COLON = ':',
        SEMICOLON = ';',
        COMMA = ',',

        PLUS = '+',
        MINUS = '-',
        ASTERISK = '*',
        SLASH = '/',
        MODULO = '%',

        EQUAL_SIGN = '=',

        L_PAREN = '(',
        R_PAREN = ')',
        L_CURLY_BRACKET  = '{',
        R_CURLY_BRACKET  = '}',
        L_SQUARE_BRACKET = '[',
        R_SQUARE_BRACKET = ']',
        L_ANGLE_BRACKET  = '<',
        R_ANGLE_BRACKET  = '>',


        DOT = '.',
        // The following enums values are chosen to be greater than 127 so that
        // they do not conflict with any ASCII values
        DOUBLE_DOT = 128,
        TRIPLE_DOT,

        ARROW,

        PLUS_EQUALS,
        MINUS_EQUALS,
        TIMES_EQUALS,
        DIVIDE_EQUALS,
        MODULO_EQUALS,

        CMP_EQ,
        CMP_NE,
        CMP_LE,
        CMP_GE,
        CMP_TW,

        BITWISE_NAND,
        BITWISE_NOR,
        BITWISE_XNOR,

        LOGICAL_AND,
        LOGICAL_OR,
        LOGICAL_XOR,

        L_SHIFT,
        R_SHIFT,

        BITWISE_AND_EQUALS,
        BITWISE_OR_EQUALS,
        BITWISE_XOR_EQUALS,

        LOGICAL_AND_EQUALS,
        LOGICAL_OR_EQUALS,
        LOGICAL_XOR_EQUALS,

        L_SHIFT_EQUALS,
        R_SHIFT_EQUALS,

        INCREMENT,
        DECREMENT,

        L_TEMPLATE_BRACKET,
        R_TEMPLATE_BRACKET,

        LAMBDA,

        // These two are used purely for internal handling during tokenization
        SINGLE_LINE_COMMENT = 249,
        MULTILINE_COMMENT = 250,

        NUMERIC_LITERAL = 251,
        STRING_LITERAL  = 252,
        CHAR_LITERAL    = 253,
        TEXT            = 254,
        DOC_TEXT        = 255
    };

    ///
    /// \param type Token_type enum value
    /// \return True if the token type is one of NUMERIC_LITERAL,
    /// STRING_LITERAL, CHAR_LITERAL, TEXT, or DOC_TEXT
    [[nodiscard]]
    bool is_textual(Token_type type);

    ///
    /// \param type True if the token corresponds to a leading unary operator
    /// \return True if the token corresponds to a unary operator
    [[nodiscard]]
    bool is_unary_operator(Token_type type);

    ///
    /// \param type Token type
    /// \return True if the token corresponds to a binary operator
    [[nodiscard]]
    bool is_binary_operator(Token_type type);

    ///
    /// \param type Arbitrary token type
    /// \return True if the token type has a corresponding right token.
    [[nodiscard]]
    bool is_left_token(Token_type type);

    ///
    /// \param type Token type
    /// \return Type of token which is expected to match with type. Returns
    /// NULL_TOKEN if no such pairing exists
    [[nodiscard]]
    Token_type matching_token_type(Token_type type);

    ///
    /// The number of unique code points which a token is.
    /// For textual tokens, returns SIZE_MAX
    ///
    [[nodiscard]]
    std::size_t token_width(Token_type type);

    ///
    /// \param token_type Token_type enum value
    /// \return View over string representation of token type. View remains
    /// valid throughout life of program.
    [[nodiscard]]
    std::string_view to_string(Token_type token_type);

}

#endif //HARC_TOKENS_HPP
