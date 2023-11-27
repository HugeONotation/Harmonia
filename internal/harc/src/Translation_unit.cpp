#include <harc/Translation_unit.hpp>

#include <harc/lexer/Tokens.hpp>

namespace harc {

    std::string tokenization_to_string(const Translation_unit& unit) {
        auto& tokenization = unit.tokenization;
        std::stringstream ret;

        std::uint32_t max_index_width = std::to_string(unit.tokenization.lengths.size() - 1).size();
        std::uint32_t max_line_width = std::to_string(unit.tokenization.source_locations.back()[0]).size();

        std::string index_padding = std::string(max_index_width, ' ');

        for (std::uint32_t i = 0; i < tokenization.types.size(); ++i) {
            //Report token index
            ret << std::setw(max_index_width);
            ret << std::to_string(i);
            ret << std::setw(0);

            //Report line and column
            ret << ". (";
            ret << std::setw(max_line_width);
            ret << std::to_string(tokenization.source_locations[i][0]);
            ret << std::setw(0);
            ret << ", ";
            ret << std::setw(2);
            // 2 is chosen under the assumption that lines should not be more
            // than 80 columns wide, and hence, only two digits would need to be
            // printed in the common case
            ret << std::to_string(tokenization.source_locations[i][1]);
            ret << std::setw(0);
            ret << ") ";

            // Report token type
            auto type = tokenization.types[i];
            ret << std::left;
            // The longest value returned by harc::to_string(Token_type) is 19
            // characters long: SINGLE_LINE_COMMENT. One added for a space char
            ret << std::setw(19 + 1);
            ret << harc::to_string(type);
            ret << std::right;
            ret << std::setw(0);

            ret << " ";

            // Report index of token's pair
            if (tokenization.pair_indices[i] != UINT32_MAX) {
                ret << std::setw(max_index_width);
                ret << std::to_string(tokenization.pair_indices[i]);
            } else {
                ret << index_padding;
            }
            ret << std::setw(0);

            // Report token text
            if (is_textual(type)) {
                ret << "  ";
                ret << std::string_view{unit.source.data() + tokenization.source_indices[i], tokenization.lengths[i]};
            }

            ret << '\n';
        }

        return ret.str();
    }

    std::string_view excerpt_with_context(
        const Translation_unit& unit,
        std::array<std::uint32_t, 2> except_location
    ) {
        //TODO: Complete implementation
        if (unit.source.size() <= except_location[0]) {

        }

        if (unit.source.size() <= except_location[1]) {

        }

        if (except_location[1] < except_location[0]) {

        }

        if (except_location[0] == except_location[1]) {

        }

        unit.tokenization.line_indices;

        return {};
    }

}
