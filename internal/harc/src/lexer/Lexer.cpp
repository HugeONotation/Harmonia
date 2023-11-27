#include <harc/lexer/Lexer.hpp>

#include <harc/lexer/Tokens.hpp>

#include <harc/Logging.hpp>
#include <harc/Error_reporting.hpp>

#include <vector>
#include <array>

#include <unicode/unistr.h>
#include <unicode/schriter.h>
#include <unicode/uchar.h>

namespace harc::lex {

    bool requires_utf8(Translation_unit& unit) {
        for (auto c : unit.source) {
            if ((signed char)(c) < 0) {
                return true;
            }
        }

        return false;
    }

    ///
    /// \param x First code point
    /// \param y Second code point
    /// \param z Third code point
    /// \return Type of token. If the token cannot be categorized, then
    /// Token_type::NULL_TOKEN is returned.
    [[nodiscard]]
    Token_type identify_token(UChar32 x, UChar32 y, UChar32 z) {
        switch (x) {
            case '!': {
                if (y == '=') {
                    return Token_type::CMP_NE;
                }

                return Token_type::EXCLAMATION;
            }
            case '^': {
                if (y == '^' && z == '=') {
                    return Token_type::LOGICAL_XOR_EQUALS;
                }

                if (y == '^') {
                    return Token_type::LOGICAL_XOR;
                }

                if (y == '=') {
                    return Token_type::BITWISE_XOR_EQUALS;
                }

                return Token_type::CARET;
            }
            case '&': {
                if (y == '&' && z == '=') {
                    return Token_type::LOGICAL_AND_EQUALS;
                }

                if (y == '&') {
                    return Token_type::LOGICAL_AND;
                }

                if (y == '=') {
                    return Token_type::BITWISE_AND_EQUALS;
                }

                return Token_type::AMPERSAND;
            }
            case '|': {
                if (y == '|' && z == '=') {
                    return Token_type::LOGICAL_OR_EQUALS;
                }

                if (y == '|') {
                    return Token_type::LOGICAL_OR;
                }

                if (y == '=') {
                    return Token_type::BITWISE_OR_EQUALS;
                }

                return Token_type::PIPE;
            }
            case '~': {
                if (y == '&') {
                    return Token_type::BITWISE_NAND;
                }

                if (y == '|') {
                    return Token_type::BITWISE_NOR;
                }

                if (y == '^') {
                    return Token_type::BITWISE_XNOR;
                }

                return Token_type::SQUIGGLE;
            }
            case ':': {
                if (y == '>') {
                    return Token_type::R_ANGLE_BRACKET;
                }

                return Token_type::COLON;
            }
            case ';': {
                return Token_type::SEMICOLON;
            }
            case ',': {
                return Token_type::COMMA;
            }
            case '+': {
                if (y == '=') {
                    return Token_type::PLUS_EQUALS;
                }

                if (y == '+') {
                    return Token_type::INCREMENT;
                }

                return Token_type::PLUS;
            }
            case '-': {
                if (y == '-') {
                    return Token_type::DECREMENT;
                }

                if (y == '>') {
                    return Token_type::ARROW;
                }

                if (y == '=') {
                    return Token_type::MINUS_EQUALS;
                }

                return Token_type::MINUS;
            }
            case '*': {
                if (y == '=') {
                    return Token_type::TIMES_EQUALS;
                }

                return Token_type::ASTERISK;
            }
            case '/': {
                if (y == '/' && z == '/') {
                    return Token_type::DOC_TEXT;
                }

                if (y == '/') {
                    return Token_type::SINGLE_LINE_COMMENT;
                }

                if (y == '=') {
                    return Token_type::DIVIDE_EQUALS;
                }

                if (y == '*') {
                    return Token_type::MULTILINE_COMMENT;
                }

                return Token_type::SLASH;
            }
            case '%': {
                if (y == '=') {
                    return Token_type::MODULO_EQUALS;
                }

                return Token_type::MODULO;
            }
            case '=': {
                if (y == '=') {
                    return Token_type::CMP_EQ;
                }

                return Token_type::EQUAL_SIGN;
            }
            case '(': {
                return Token_type::L_PAREN;
            }
            case ')': {
                return Token_type::R_PAREN;
            }
            case '{': {
                return Token_type::L_CURLY_BRACKET;
            }
            case '}': {
                return Token_type::R_CURLY_BRACKET;
            }
            case '[': {
                return Token_type::L_SQUARE_BRACKET;
            }
            case ']': {
                return Token_type::R_SQUARE_BRACKET;
            }
            case '<': {
                if (y == '<' && z == '=') {
                    return Token_type::L_SHIFT_EQUALS;
                }

                if (y == '=' && z == '>') {
                    return Token_type::CMP_TW;
                }

                if (y == ':') {
                    return Token_type::L_TEMPLATE_BRACKET;
                }

                if (y == '<') {
                    return Token_type::L_SHIFT;
                }

                if (y == '=') {
                    return Token_type::CMP_LE;
                }

                return Token_type::L_ANGLE_BRACKET;
            }
            case '>': {
                if (y == '>' && z == '=') {
                    return Token_type::R_SHIFT;
                }

                if (y == '>') {
                    return Token_type::R_SHIFT;
                }

                if (y == '=') {
                    return Token_type::CMP_GE;
                }

                return Token_type::R_ANGLE_BRACKET;
            }
            case '.': {
                if (y == '.' && z == '.') {
                    return Token_type::TRIPLE_DOT;
                }

                if (y == '.') {
                    return Token_type::DOUBLE_DOT;
                }

                return Token_type::DOT;
            }
            case '"': {
                return Token_type::STRING_LITERAL;
            }
            case '\'': {
                return Token_type::CHAR_LITERAL;
            }
            default: {
                if (std::isdigit(x)) {
                    return Token_type::NUMERIC_LITERAL;
                }

                if (u_hasBinaryProperty(x, UCHAR_ID_START)) {
                    return Token_type::TEXT;
                }

                return Token_type::NULL_TOKEN;
            }
        }
    }

    void find_single_line_comment_end(UChar32& x, UChar32& y, UChar32& z, icu::StringCharacterIterator& it) {
        // x is /
        // y is /
        // z is unknown

        // Iterate until z is a newline
        for (; z != icu::StringCharacterIterator::DONE; z = it.next32PostInc()) {
            if (z == '\n') {
                break;
            }
        }

        // Perform one shift left of chars.
        y = z;
        z = it.next32PostInc();
    }

    void find_numeric_literal_end(UChar32& x, UChar32& y, UChar32& z, icu::StringCharacterIterator& it) {
        // x is a digit
        // y is unknown
        // z is unknown

        if (y == icu::StringCharacterIterator::DONE || !(u_isdigit(y) || u_isalpha(y) || y == '_' || y == '.')) {
            return;
        }

        while (z != icu::StringCharacterIterator::DONE) {
            if (!(u_isdigit(z) || u_isalpha(z) || z == '_' || z == '.')) {
                break;
            }

            z = it.next32PostInc();
        }

        y = z;
        z = it.next32PostInc();
    }

    void find_string_literal_end(UChar32& x, UChar32& y, UChar32& z, icu::StringCharacterIterator& it) {
        // x is "
        // y is unknown
        // z is unknown

        if (y == icu::StringCharacterIterator::DONE || y == '"' || y == '\n') {
            y = z;
            z = it.next32PostInc();

            return;
        }

        bool is_codepoint_escaped = y == '\\';

        while (z != icu::StringCharacterIterator::DONE) {
            if ((z == '"' && !is_codepoint_escaped) || y == '\n') {
                break;
            }

            is_codepoint_escaped = (z == '\\') && !is_codepoint_escaped;

            z = it.next32PostInc();
        }

        y = z;
        z = it.next32PostInc();

        y = z;
        z = it.next32PostInc();
    }

    void find_char_literal_end(UChar32& x, UChar32& y, UChar32& z, icu::StringCharacterIterator& it) {
        // x is '
        // y is unknown
        // z is unknown

        if (y == icu::StringCharacterIterator::DONE || y == '\'') {
            y = z;
            z = it.next32PostInc();

            return;
        }

        bool is_codepoint_escaped = y == '\\';

        while (z != icu::StringCharacterIterator::DONE) {
            if (z == '\'' && !is_codepoint_escaped) {
                break;
            }

            is_codepoint_escaped = (z == '\\') && !is_codepoint_escaped;

            z = it.next32PostInc();
        }

        y = z;
        z = it.next32PostInc();

        y = z;
        z = it.next32PostInc();
    }

    void find_text_token_end(UChar32& x, UChar32& y, UChar32& z, icu::StringCharacterIterator& it) {
        // x is codepoint which may begin identifier
        // y is unknown
        // z is unknown

        if (y == icu::StringCharacterIterator::DONE || !u_hasBinaryProperty(y, UProperty::UCHAR_ID_CONTINUE)) {
            return;
        }

        while (z != icu::StringCharacterIterator::DONE) {
            if (!u_hasBinaryProperty(z, UProperty::UCHAR_ID_CONTINUE)) {
                break;
            }

            z = it.next32PostInc();
        }

        y = z;
        z = it.next32PostInc();
    }

    void find_doc_text_end(UChar32& x, UChar32& y, UChar32& z, icu::StringCharacterIterator& it) {
        // x is /
        // y is /
        // z is /

        while (z != icu::StringCharacterIterator::DONE) {
            if (z == '\n') {
                break;
            }

            z = it.next32PostInc();
        }

        y = z;
        z = it.next32PostInc();
    }


    struct Stack_entry {
        Token_type type;
        std::uint32_t index;
    };



    Error_code lex_ascii(Translation_unit& unit) {
        return {};
    }

    Error_code lex_utf8(Translation_unit& unit) {
        return {};
    }

    Error_code lex(Translation_unit& unit) {
        auto& tokenization = unit.tokenization;

        // Guess number of tokens and reserve enough space
        const std::uint32_t bytes_per_token_estimate = 5;
        auto token_count_estimate = unit.source.size() / bytes_per_token_estimate;

        tokenization.types.reserve(token_count_estimate);
        tokenization.lengths.reserve(token_count_estimate);
        tokenization.source_indices.reserve(token_count_estimate);
        tokenization.source_locations.reserve(token_count_estimate);


        // Guess number of lines and reserve enough space
        const std::uint32_t bytes_per_line_estimate = 8;
        auto line_count_estimate = unit.source.size() / bytes_per_line_estimate;

        tokenization.line_indices.reserve(line_count_estimate);
        tokenization.line_indices.push_back(0);


        // Helper lambda to make emplacing tokens more terse
        auto emplace_token =
            [&tokenization] (
                Token_type type,
                std::uint32_t index,
                std::uint32_t length,
                std::array<std::uint32_t, 2> location,
                std::uint32_t pair_index = UINT32_MAX
            ) {
                tokenization.types.push_back(type);
                tokenization.source_indices.push_back(index);
                tokenization.lengths.push_back(length);
                tokenization.source_locations.push_back(location);
                tokenization.pair_indices.push_back(pair_index);
            };

        //TODO: Utilize translation unit's error buffer

        //TODO: Address the issue that the use of a signed 32-bit integer does
        //not meet Harmonia's requirement that source files may be up to at
        //least 2^32-1 bytes in size
        icu::UnicodeString ustring{unit.source.data(), static_cast<std::int32_t>(unit.source.size()), "utf-8"};

        // Append two more empty characters so that getting the indices from the
        // iterator continue to be incremented even after reaching the end of
        // the string.
        ustring += icu::StringCharacterIterator::DONE;
        ustring += icu::StringCharacterIterator::DONE;

        // Index of codepoint which begins current line
        std::uint32_t line_begin_index = 0;

        // Track current line number
        std::uint32_t line = 1;

        // Codepoint iterator
        icu::StringCharacterIterator it{ustring};

        // Stack which is used to identify unpaired tokens
        std::vector<Stack_entry> balancing_stack;

        // Guess maximum nesting depth
        balancing_stack.reserve(32);

        // Track current codepoints and next two codepoints
        UChar32 x = it.next32PostInc();
        UChar32 y = it.next32PostInc();
        UChar32 z = it.next32PostInc();

        for (;x != icu::StringCharacterIterator::DONE; x = y, y = z, z = it.next32PostInc()) {
            // Location of codepoint x
            std::array<std::uint32_t, 2> location = {line, it.getIndex() - 2 - line_begin_index};

            // Handle new lines
            if (x == '\n') {
                line += 1;
                line_begin_index = it.getIndex() - 2;
                tokenization.line_indices.push_back(line_begin_index);
                continue;
            }

            // Skip whitespace
            if (u_isUWhiteSpace(x)) {
                continue;
            }

            // Identify type of current token
            Token_type type = identify_token(x, y, z);

            // Handle case where token was not recognized
            if (type == Token_type::NULL_TOKEN) {
                //TODO: Do error handling
                return Error_code::LEXING_ERROR;
            }

            // Handle single line comment
            if (type == Token_type::SINGLE_LINE_COMMENT) {
                find_single_line_comment_end(x, y, z, it);
                continue;
            }

            // Handle multiline comment
            if (type == Token_type::MULTILINE_COMMENT) {
                // x is /
                // y is *
                // z is unknown

                // Perform one manual iteration because otherwise /*/ is
                // interpreted as a complete multi-line comment
                y = z;
                z = it.next32PostInc();

                // Wait until y is * and z is /
                for (;z != icu::StringCharacterIterator::DONE;) {
                    if (y == '*' && z == '/') {
                        break;
                    }

                    if (y == '\n') {
                        line += 1;
                        line_begin_index = it.getIndex() - 2;
                        tokenization.line_indices.push_back(line_begin_index);
                    }

                    y = z;
                    z = it.next32PostInc();
                }

                y = z;
                z = it.next32PostInc();

                y = z;
                z = it.next32PostInc();

                continue;
            }

            // Handle textural tokens, whose lengths are variable
            if (is_textual(type)) {
                auto starting_index = it.getIndex() - 3;
                switch (type) {
                    case Token_type::NUMERIC_LITERAL: {
                        find_numeric_literal_end(x, y, z, it);
                        break;
                    }
                    case Token_type::STRING_LITERAL: {
                        find_string_literal_end(x, y, z, it);
                        if (y == icu::StringCharacterIterator::DONE) {
                            print_error(
                                unit.source_path,
                                unit.source.data() + line_begin_index,
                                {line, it.getIndex() - 2 - line_begin_index},
                                "Unterminated string literal"
                            );
                            return Error_code::LEXING_ERROR;
                        }

                        break;
                    }
                    case Token_type::CHAR_LITERAL: {
                        find_char_literal_end(x, y, z, it);
                        if (y == icu::StringCharacterIterator::DONE) {
                            print_error(
                                unit.source_path,
                                unit.source.data() + line_begin_index,
                                {line, it.getIndex() - 2 - line_begin_index},
                                "Unterminated char literal"
                            );
                            return Error_code::LEXING_ERROR;
                        }

                        break;
                    }
                    case Token_type::TEXT: {
                        find_text_token_end(x, y, z, it);

                        // Reset the balancing stack if the text token
                        // introduces a new function or struct
                        auto token_text = std::string_view{
                            unit.source.data() + starting_index,
                            std::size_t(it.getIndex() - starting_index - 2)
                        };

                        if (token_text == "struct" || token_text == "func") {
                            if (!balancing_stack.empty()) {
                                //TODO: Handle lack of properly balanced tokens
                                balancing_stack.clear();
                            }
                        }

                        break;
                    }
                    case Token_type::DOC_TEXT: {
                        find_doc_text_end(x, y, z, it);
                        break;
                    }
                    default: {
                        //This should never be reached
                        HARC_LOG_ERROR("Reached unexpected branch of switch statement");
                        std::exit(EXIT_FAILURE);
                    }
                }

                auto curr_index = it.getIndex();
                emplace_token(
                    type,
                    starting_index,
                    curr_index - starting_index - 2,
                    {line, starting_index - line_begin_index + 1}
                );

                continue;
            }

            // Handle non-textual tokens, whose lengths are at most 3 code points
            auto width = token_width(type);


            // Handle balancing tokens
            auto expected_match = matching_token_type(type);

            //TODO: Handle mismatched tokens and attempt to identify which
            // those are

            std::uint32_t matching_index = UINT32_MAX;
            if (expected_match != Token_type::NULL_TOKEN) {
                if (is_left_token(type)) {
                    Stack_entry b{};
                    b.type = type;
                    b.index = tokenization.lengths.size();
                    balancing_stack.push_back(b);
                } else {
                    auto stack_top = balancing_stack.back();
                    if (expected_match == stack_top.type) {
                        balancing_stack.pop_back();
                        matching_index = stack_top.index;

                        tokenization.pair_indices[stack_top.index] =
                            tokenization.lengths.size();
                    } else {
                        print_error(
                            unit.source_path,
                            std::string_view{
                                unit.source.data() + line_begin_index,
                                it.getIndex() - line_begin_index + 1
                            },
                            location,
                            "Unmatched token"
                        );
                    }
                }
            }

            emplace_token(
                type,
                it.getIndex() - 3,
                width,
                location,
                matching_index
            );

            // Advance the iterator (width - 1) times.
            for (int i = 1; i < width; ++i) {
                x = y;
                y = z;
                z = it.next32PostInc();
            }
        }

        return Error_code::NO_ERROR;
    }

}
