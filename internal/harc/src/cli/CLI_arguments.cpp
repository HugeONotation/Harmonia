#include <harc/cli/CLI_arguments.hpp>
#include <harc/cli/CLI.hpp>
#include <harc/cli/Errors.hpp>

#include <harc/Harc.hpp>

#include <aul/Span.hpp>

#include <string>
#include <thread>

#include <fmt/core.h>

namespace harc::cli {

    auto& args = impl::cli_args;

    //=====================================================
    // Named argument parse functions
    //=====================================================

    void parse_nothing_as_true(std::string_view key, std::string_view value, void* out_ptr) {
        bool& out = *reinterpret_cast<bool*>(out_ptr);
        out = true;
    }

    void parse_boolean(std::string_view key, std::string_view value, void* out_ptr) {
        const std::string_view recognized_values[2] = {
            "false",
            "true"
        };

        cli::Message_buffer::append(
            Error_code::UNRECOGNIZED_VALUE,
            key,
            value,
            aul::Span{recognized_values}
        );
    }

    void parse_u16(std::string_view key, std::string_view value, void* out_ptr) {
        std::uint16_t& out = *reinterpret_cast<std::uint16_t*>(out_ptr);
        static_assert(sizeof(unsigned long long) >= sizeof(std::uint16_t));

        unsigned long long v = 0;
        try {
            v = std::stoull(value.data());
        } catch (std::invalid_argument& e) {
            Message_buffer::append(
                Error_code::VALUE_NOT_UNSIGNED_INTEGER,
                key,
                value
            );
            return;
        } catch (std::out_of_range& e) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_U16,
                key,
                value
            );
            return;
        }

        if (UINT16_MAX < v) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_U16,
                key,
                value
            );
            return;
        }

        out = v;
    }

    void parse_i16(std::string_view key, std::string_view value, void* out_ptr) {
        std::int16_t& out = *reinterpret_cast<std::int16_t*>(out_ptr);
        static_assert(sizeof(long long) >= sizeof(std::int16_t));

        long long v = 0;
        try {
            v = std::stoull(value.data());
        } catch (std::invalid_argument& e) {
            Message_buffer::append(
                Error_code::VALUE_NOT_UNSIGNED_INTEGER,
                key,
                value
            );
            return;
        } catch (std::out_of_range& e) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_I16,
                key,
                value
            );
            return;
        }

        if (INT16_MIN < v || INT16_MAX < v) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_I16,
                key,
                value
            );
            return;
        }

        out = v;
    }

    void parse_u32(std::string_view key, std::string_view value, void* out_ptr) {
        std::uint32_t& out = *reinterpret_cast<std::uint32_t*>(out_ptr);
        static_assert(sizeof(unsigned long long) >= sizeof(std::uint32_t));

        unsigned long long v = 0;
        try {
            v = std::stoull(value.data());
        } catch (std::invalid_argument& e) {
            Message_buffer::append(
                Error_code::VALUE_NOT_UNSIGNED_INTEGER,
                key,
                value
            );
            return;
        } catch (std::out_of_range& e) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_U32,
                key,
                value
            );
            return;
        }

        if (UINT32_MAX < v) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_U32,
                key,
                value
            );
            return;
        }

        out = v;
    }

    void parse_i32(std::string_view key, std::string_view value, void* out_ptr) {
        std::int32_t& out = *reinterpret_cast<std::int32_t*>(out_ptr);
        static_assert(sizeof(long long) >= sizeof(std::int32_t));

        long long v = 0;
        try {
            v = std::stoull(value.data());
        } catch (std::invalid_argument& e) {
            Message_buffer::append(
                Error_code::VALUE_NOT_UNSIGNED_INTEGER,
                key,
                value
            );
            return;
        } catch (std::out_of_range& e) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_I32,
                key,
                value
            );
            return;
        }

        if (INT32_MIN < v || INT32_MAX < v) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_I32,
                key,
                value
            );
            return;
        }

        out = v;
    }

    void parse_u64(std::string_view key, std::string_view value, void* out_ptr) {
        std::uint64_t& out = *reinterpret_cast<std::uint64_t*>(out_ptr);
        static_assert(sizeof(unsigned long long) >= sizeof(std::uint64_t));

        unsigned long long v = 0;
        try {
            v = std::stoull(value.data());
        } catch (std::invalid_argument& e) {
            Message_buffer::append(
                Error_code::VALUE_NOT_UNSIGNED_INTEGER,
                key,
                value
            );
            return;
        } catch (std::out_of_range& e) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_U64,
                key,
                value
            );
            return;
        }

        if (UINT64_MAX < v) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_U64,
                key,
                value
            );
            return;
        }

        out = v;
    }

    void parse_i64(std::string_view key, std::string_view value, void* out_ptr) {
        std::int64_t& out = *reinterpret_cast<std::int64_t*>(out_ptr);
        static_assert(sizeof(long long) >= sizeof(std::int64_t));

        long long v = 0;
        try {
            v = std::stoull(value.data());
        } catch (std::invalid_argument& e) {
            Message_buffer::append(
                Error_code::VALUE_NOT_UNSIGNED_INTEGER,
                key,
                value
            );
            return;
        } catch (std::out_of_range& e) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_I64,
                key,
                value
            );
            return;
        }

        if (INT64_MIN < v || INT64_MAX < v) {
            Message_buffer::append(
                Error_code::VALUE_INT_MAGNITUDE_OUT_OF_RANGE_I64,
                key,
                value
            );
            return;
        }

        out = v;
    }

    //=====================================================
    // Validation functions
    //=====================================================

    void null_validator(std::string_view key, std::string_view value) {

    }

    void validate_port_number(std::string_view key, std::string_view value) {
        if (arguments.network_port < 1024) {
            Message_buffer::append(Warning_code::PRIVILEGED_PORT_NUMBER, key, value);
        }
    }

    void validate_thread_count(std::string_view key, std::string_view value) {
        if (arguments.cpu_worker_thread_count == 0 && arguments.network_mode != Network_mode::PURE_SERVER) {
            Message_buffer::append(
                Error_code::ZERO_THREADS_REQUESTED,
                key,
                value
            );
        }

        if (arguments.cpu_worker_thread_count >= std::thread::hardware_concurrency()) {
            Message_buffer::append(
                Warning_code::MORE_THREADS_REQUESTED_THAN_AVAILABLE,
                key,
                value,
                std::to_string(std::thread::hardware_concurrency())
            );
        }
    }

    //=====================================================
    // Response functions
    //=====================================================

    void respond_version(int argc, char* const argv[]) {
        fmt::print(
            "Harc {}\n{}\n{}\n",
            harc::to_string(harc::version),
            "Harmonia compiler",
            "Authored by Huge-O Notation"
        );
    }

    void respond_help(int argc, char* const argv[]) {
        //TODO: Defer to help printing subroutines once they're written
        fmt::print(
            "{}\n",
            "Help pages have not yet been implemented."
        );
    }

    //=====================================================
    // Argument maps
    //=====================================================

    const std::map<std::string_view, Singular_argument> singular_argument_map {
        {"version", {respond_version}},
        {"help",    {respond_help}}
    };

    const std::map<std::string_view, Named_argument> argument_map {
        //{"logging_level",        {&args.logging_level,        parse_level}},
        //{"network_mode",         {&args.network_mode,         parse_network_mode}},
        {"performance_warnings", {&args.performance_warnings, parse_boolean, null_validator}},
        {"style_warnings",       {&args.style_warnings,       parse_boolean, null_validator}},
        //{"server_address_ipv6",  {&args.server_address_ipv6,  parse_ipv6_address}},
        //{"server_address_ipv4",  {&args.server_address_ipv4,  parse_ipv4_address}},
        {"network_port",         {&args.network_port,         parse_u16, validate_port_number}},
        //{"assembler",            {&args.assembler_path,       parse_path}},
        {"cpu_worker_thread_count",         {&args.cpu_worker_thread_count, parse_u32, null_validator}}
    };

}
