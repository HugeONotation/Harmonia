#ifndef HARMONIA_CLI_ARGUMENTS_HPP
#define HARMONIA_CLI_ARGUMENTS_HPP

#include <map>
#include <string_view>

namespace harc::cli {

    //=====================================================
    // Singular arguments
    //=====================================================

    using response_func = void (*)(int argc, char* const argv[]);

    struct Singular_argument {
        response_func response = nullptr;
    };

    extern const std::map<std::string_view, Singular_argument> singular_argument_map;

    //=====================================================
    // Named arguments
    //=====================================================

    using parse_func = void (*)(std::string_view key, std::string_view value, void* out);

    using validation_func = void (*)(std::string_view key, std::string_view value);

    void parse_nothing_as_true(std::string_view key, std::string_view value, void* out_ptr);

    struct Named_argument {
        void* address = nullptr;
        parse_func parser = nullptr;
        validation_func validator = nullptr;
    };

    extern const std::map<std::string_view, Named_argument> argument_map;

}

#endif //HARMONIA_CLI_ARGUMENTS_HPP
