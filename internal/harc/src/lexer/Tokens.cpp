#include <harc/lexer/Tokens.hpp>

namespace harc {

    bool is_textual(Token_type type) {
        static_assert(static_cast<std::uint8_t>(Token_type::SINGLE_LINE_COMMENT) >= 249);
        static_assert(static_cast<std::uint8_t>(Token_type::MULTILINE_COMMENT) >= 249);
        static_assert(static_cast<std::uint8_t>(Token_type::NUMERIC_LITERAL) >= 249);
        static_assert(static_cast<std::uint8_t>(Token_type::STRING_LITERAL) >= 249);
        static_assert(static_cast<std::uint8_t>(Token_type::CHAR_LITERAL) >= 249);
        static_assert(static_cast<std::uint8_t>(Token_type::TEXT) >= 249);
        static_assert(static_cast<std::uint8_t>(Token_type::DOC_TEXT) >= 249);

        return static_cast<std::uint8_t>(type) >= 249;
    }

    bool is_unary_operator(Token_type type) {
        switch (type) {
            case Token_type::EXCLAMATION:
            case Token_type::AMPERSAND:
            case Token_type::SQUIGGLE:
            case Token_type::PLUS:
            case Token_type::MINUS:
            case Token_type::ASTERISK:
            case Token_type::INCREMENT:
            case Token_type::DECREMENT:
                return true;
            default:
                return false;
        }
    }

    bool is_binary_operator(Token_type type) {
        switch (type) {
            case Token_type::AMPERSAND:
            case Token_type::CARET:
            case Token_type::PIPE:
            case Token_type::PLUS:
            case Token_type::MINUS:
            case Token_type::ASTERISK:
            case Token_type::SLASH:
            case Token_type::MODULO:
            case Token_type::EQUAL_SIGN:
            case Token_type::ARROW:
            case Token_type::PLUS_EQUALS:
            case Token_type::MINUS_EQUALS:
            case Token_type::TIMES_EQUALS:
            case Token_type::DIVIDE_EQUALS:
            case Token_type::MODULO_EQUALS:
            case Token_type::CMP_EQ:
            case Token_type::CMP_NE:
            case Token_type::CMP_LE:
            case Token_type::CMP_GE:
            case Token_type::CMP_TW:
            case Token_type::BITWISE_NAND:
            case Token_type::BITWISE_NOR:
            case Token_type::BITWISE_XNOR:
            case Token_type::LOGICAL_AND:
            case Token_type::LOGICAL_OR:
            case Token_type::LOGICAL_XOR:
            case Token_type::L_SHIFT:
            case Token_type::R_SHIFT:
            case Token_type::BITWISE_AND_EQUALS:
            case Token_type::BITWISE_OR_EQUALS:
            case Token_type::BITWISE_XOR_EQUALS:
            case Token_type::LOGICAL_AND_EQUALS:
            case Token_type::LOGICAL_OR_EQUALS:
            case Token_type::LOGICAL_XOR_EQUALS:
            case Token_type::L_SHIFT_EQUALS:
            case Token_type::R_SHIFT_EQUALS:
                return true;
            default:
                return false;
        }
    }

    bool is_left_token(Token_type type) {
        switch (type) {
            case Token_type::L_PAREN:
            case Token_type::L_CURLY_BRACKET:
            case Token_type::L_SQUARE_BRACKET:
            case Token_type::L_TEMPLATE_BRACKET:
                return true;

            default:
                return false;
        }
    }

    Token_type matching_token_type(Token_type type) {
        switch (type) {
            case Token_type::L_PAREN: return Token_type::R_PAREN;
            case Token_type::R_PAREN: return Token_type::L_PAREN;

            case Token_type::L_CURLY_BRACKET: return Token_type::R_CURLY_BRACKET;
            case Token_type::R_CURLY_BRACKET: return Token_type::L_CURLY_BRACKET;

            case Token_type::L_SQUARE_BRACKET: return Token_type::R_SQUARE_BRACKET;
            case Token_type::R_SQUARE_BRACKET: return Token_type::L_SQUARE_BRACKET;

            case Token_type::L_TEMPLATE_BRACKET: return Token_type::R_TEMPLATE_BRACKET;
            case Token_type::R_TEMPLATE_BRACKET: return Token_type::L_TEMPLATE_BRACKET;

            default: return Token_type::NULL_TOKEN;
        }
    }

    std::size_t token_width(Token_type token_type) {
        switch (token_type) {
            case Token_type::NULL_TOKEN: return 0;

            case Token_type::EXCLAMATION: return 1;
            case Token_type::CARET: return 1;
            case Token_type::AMPERSAND: return 1;
            case Token_type::PIPE: return 1;
            case Token_type::SQUIGGLE: return 1;
            case Token_type::COLON: return 1;
            case Token_type::SEMICOLON: return 1;
            case Token_type::COMMA: return 1;

            case Token_type::PLUS: return 1;
            case Token_type::MINUS: return 1;
            case Token_type::ASTERISK: return 1;
            case Token_type::SLASH: return 1;
            case Token_type::MODULO: return 1;

            case Token_type::EQUAL_SIGN: return 1;

            case Token_type::L_PAREN: return 1;
            case Token_type::R_PAREN: return 1;
            case Token_type::L_CURLY_BRACKET: return 1;
            case Token_type::R_CURLY_BRACKET: return 1;
            case Token_type::L_SQUARE_BRACKET: return 1;
            case Token_type::R_SQUARE_BRACKET: return 1;
            case Token_type::L_ANGLE_BRACKET: return 1;
            case Token_type::R_ANGLE_BRACKET: return 1;

            case Token_type::DOT: return 1;
            case Token_type::DOUBLE_DOT: return 2;
            case Token_type::TRIPLE_DOT: return 3;
            case Token_type::ARROW: return 2;

            case Token_type::PLUS_EQUALS: return 2;
            case Token_type::MINUS_EQUALS: return 2;
            case Token_type::TIMES_EQUALS: return 2;
            case Token_type::DIVIDE_EQUALS: return 2;
            case Token_type::MODULO_EQUALS: return 2;

            case Token_type::CMP_EQ: return 2;
            case Token_type::CMP_NE: return 2;
            case Token_type::CMP_LE: return 2;
            case Token_type::CMP_GE: return 2;
            case Token_type::CMP_TW: return 3;

            case Token_type::BITWISE_NAND: return 2;
            case Token_type::BITWISE_NOR: return 2;
            case Token_type::BITWISE_XNOR: return 2;

            case Token_type::LOGICAL_AND: return 2;
            case Token_type::LOGICAL_OR: return 2;
            case Token_type::LOGICAL_XOR: return 3;

            case Token_type::L_SHIFT: return 2;
            case Token_type::R_SHIFT: return 2;

            case Token_type::BITWISE_AND_EQUALS: return 2;
            case Token_type::BITWISE_OR_EQUALS: return 2;
            case Token_type::BITWISE_XOR_EQUALS: return 2;

            case Token_type::LOGICAL_AND_EQUALS: return 2;
            case Token_type::LOGICAL_OR_EQUALS: return 2;
            case Token_type::LOGICAL_XOR_EQUALS: return 2;

            case Token_type::L_SHIFT_EQUALS: return 3;
            case Token_type::R_SHIFT_EQUALS: return 3;

            case Token_type::INCREMENT: return 2;
            case Token_type::DECREMENT: return 2;

            case Token_type::L_TEMPLATE_BRACKET: return 2;
            case Token_type::R_TEMPLATE_BRACKET: return 2;

            case Token_type::SINGLE_LINE_COMMENT: return SIZE_MAX;
            case Token_type::MULTILINE_COMMENT: return SIZE_MAX;

            case Token_type::NUMERIC_LITERAL: return SIZE_MAX;
            case Token_type::STRING_LITERAL: return SIZE_MAX;
            case Token_type::CHAR_LITERAL: return SIZE_MAX;
            case Token_type::TEXT: return SIZE_MAX;
            case Token_type::DOC_TEXT: return SIZE_MAX;

            default: {
                HARC_LOG_ERROR("Unhandled token in implementation of to_string(Token-type");
                return 0;
            }
        }
    }

    std::string_view to_string(Token_type token_type) {
        switch (token_type) {
            case Token_type::NULL_TOKEN: return {"NULL_TOKEN"};

            case Token_type::EXCLAMATION: return {"EXCLAMATION_MARK"};
            case Token_type::CARET: return {"CARET"};
            case Token_type::AMPERSAND: return {"AMPERSAND"};
            case Token_type::ASTERISK: return {"ASTERISK"};
            case Token_type::PIPE: return {"PIPE"};
            case Token_type::SQUIGGLE: return {"SQUIGGLE"};
            case Token_type::COLON: return {"COLON"};
            case Token_type::SEMICOLON: return {"SEMICOLON"};
            case Token_type::COMMA: return {"COMMA"};

            case Token_type::PLUS: return {"PLUS"};
            case Token_type::MINUS: return {"MINUS"};
            case Token_type::SLASH: return {"SLASH"};
            case Token_type::MODULO: return {"MODULO"};

            case Token_type::EQUAL_SIGN: return {"EQUAL_SIGN"};

            case Token_type::L_PAREN: return {"L_PAREN"};
            case Token_type::R_PAREN: return {"R_PAREN"};
            case Token_type::L_SQUARE_BRACKET: return {"L_SQUARE_BRACKET"};
            case Token_type::R_SQUARE_BRACKET: return {"R_SQUARE_BRACKET"};
            case Token_type::L_CURLY_BRACKET: return {"L_CURLY_BRACKET"};
            case Token_type::R_CURLY_BRACKET: return {"R_CURLY_BRACKET"};
            case Token_type::L_ANGLE_BRACKET: return {"L_ANGLE_BRACKET"};
            case Token_type::R_ANGLE_BRACKET: return {"R_ANGLE_BRACKET"};

            case Token_type::DOT: return {"DOT"};
            case Token_type::DOUBLE_DOT: return {"DOUBLE_DOT"};
            case Token_type::TRIPLE_DOT: return {"TRIPLE_DOT"};

            case Token_type::ARROW: return {"ARROW"};

            case Token_type::PLUS_EQUALS: return {"PLUS_EQUALS"};
            case Token_type::MINUS_EQUALS: return {"MINUS_EQUALS"};
            case Token_type::TIMES_EQUALS: return {"TIMES_EQUALS"};
            case Token_type::DIVIDE_EQUALS: return {"DIVIDE_EQUALS"};
            case Token_type::MODULO_EQUALS: return {"MODULO_EQUALS"};

            case Token_type::CMP_EQ: return {"CMP_EQUAL"};
            case Token_type::CMP_NE: return {"CMP_NOT_EQUAL"};
            case Token_type::CMP_LE: return {"CMP_LESS_EQUAL"};
            case Token_type::CMP_GE: return {"CMP_GREATER_EQUAL"};
            case Token_type::CMP_TW: return {"CMP_THREE_WAY"};

            case Token_type::BITWISE_NAND: return {"BITWISE_NAND"};
            case Token_type::BITWISE_NOR: return {"BITWISE_NOR"};
            case Token_type::BITWISE_XNOR: return {"BITWISE_XNOR"};

            case Token_type::LOGICAL_AND: return {"LOGICAL_AND"};
            case Token_type::LOGICAL_OR: return {"LOGICAL_OR"};
            case Token_type::LOGICAL_XOR: return {"LOGICAL_XOR"};

            case Token_type::L_SHIFT: return {"L_SHIFT"};
            case Token_type::R_SHIFT: return {"R_SHIFT"};

            case Token_type::BITWISE_AND_EQUALS: return {"BITWISE_AND_EQUALS"};
            case Token_type::BITWISE_OR_EQUALS: return {"BITWISE_OR_EQUALS"};
            case Token_type::BITWISE_XOR_EQUALS: return {"BITWISE_XOR_EQUALS"};

            case Token_type::LOGICAL_AND_EQUALS: return {"LOGICAL_AND_EQUALS"};
            case Token_type::LOGICAL_OR_EQUALS: return {"LOGICAL_OR_EQUALS"};
            case Token_type::LOGICAL_XOR_EQUALS: return {"LOGICAL_XOR_EQUALS"};

            case Token_type::L_SHIFT_EQUALS: return {"L_SHIFT_EQUALS"};
            case Token_type::R_SHIFT_EQUALS: return {"R_SHIFT_EQUALS"};

            case Token_type::INCREMENT: return {"INCREMENT"};
            case Token_type::DECREMENT: return {"DECREMENT"};

            case Token_type::L_TEMPLATE_BRACKET: return {"L_TEMPLATE_BRACKET"};
            case Token_type::R_TEMPLATE_BRACKET: return {"R_TEMPLATE_BRACKET"};

            case Token_type::SINGLE_LINE_COMMENT: return {"SINGLE_LINE_COMMENT"};
            case Token_type::MULTILINE_COMMENT: return {"MULTILINE_COMMENT"};

            case Token_type::NUMERIC_LITERAL: return {"NUMERIC_LITERAL"};
            case Token_type::STRING_LITERAL: return {"STRING_LITERAL"};
            case Token_type::CHAR_LITERAL: return {"CHAR_LITERAL"};
            case Token_type::TEXT: return {"TEXT"};
            case Token_type::DOC_TEXT: return {"DOC_TEXT"};

            default: {
                HARC_LOG_ERROR("Unhandled token in implementation of to_string(Token-type");
                return {"Unknown"};
            }
        }
    }

}
