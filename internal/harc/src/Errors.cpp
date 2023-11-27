#include <harc/Errors.hpp>

#include <harc/Error_reporting.hpp>

namespace harc {

    std::string_view to_string(Error_code error) {
        switch (error) {
            case Error_code::NO_ERROR:
                return "No error";
            case Error_code::GENERAL_INTERNAL_ERROR:
                return "General internal failure";
            case Error_code::NO_SOURCE_FILES_SPECIFIED:
                return "No source files were specified at the command line";
            case Error_code::INVALID_COMMAND_LINE_ARGUMENTS:
                return "Invalid command line arguments";
            case Error_code::INVALID_SOURCE_FILE:
                return "Invalid source file";
            case Error_code::TOKENIZATION_ERROR:
                return "Tokenization error";
            case Error_code::PARSING_ERROR:
                return "Parsing error";
            default:
                return "Unrecognized error";
        }
    }

    std::vector<Error> Message_buffer::list{};

    void Message_buffer::append(Error_code error_code, const std::string& str) {
        list.emplace_back(error_code, str);
    }

    void Message_buffer::append(Error_code error_code, std::string&& str) {
        list.emplace_back(error_code, std::move(str));
    }

    void Message_buffer::append(Error_code error_code, std::string_view str) {
        list.emplace_back(error_code, str.data());
    }

    void Message_buffer::append(Error_code error_code, const char* str) {
        list.emplace_back(error_code, str);
    }

    void Message_buffer::flush() {
        for (auto& error : list) {
            print_error(harc::to_string(error.error_code));
            //TODO: Substitute in auxiliary info
        }

        list = std::vector<Error>{};
    }

}
