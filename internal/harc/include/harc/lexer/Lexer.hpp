#ifndef HARC_TOKENIZER_HPP
#define HARC_TOKENIZER_HPP

#include <harc/Errors.hpp>
#include <harc/Translation_unit.hpp>

namespace harc::lex {

    [[nodiscard]]
    bool requires_utf8(Translation_unit& unit);

    ///
    ///
    ///
    ///
    /// \param unit Translation unit to parse source for
    Error_code lex(Translation_unit& unit);

}

#endif //HARC_TOKENIZER_HPP
