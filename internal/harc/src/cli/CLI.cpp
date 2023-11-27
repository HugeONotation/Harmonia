#include <harc/cli/CLI.hpp>
#include <harc/cli/CLI_arguments.hpp>

#include <harc/Logging.hpp>

#include <sstream>
#include <map>
#include <span>

namespace harc::cli {

    void parse_configuration(
        std::map<std::string_view, std::string_view>& config_map
    ) {
        for (auto& p : config_map) {
            auto& [key, value] = p;

            auto it = argument_map.find(key);
            if (it == argument_map.end()) {
                //TODO: Log error
                continue;
            }

            auto [address, parser, validator] = std::get<1>(*it);

            parser(key, value, address);
            validator(key, value);
        }
    }

    harc::Error_code post_validation_argument_processing() {
        namespace fs = std::filesystem;

        /*
        // Validate assembler path
        if (arguments.assembler_path.empty()) {
            // Use default choice of assembler
            #if HARC_POSIX
            impl::cli_args.assembler_path = "/usr/bin/as";
            #else
            static_assert(false, "Default assembler path not specified for target operating system.")
            #endif
        }

        if (!fs::exists(arguments.assembler_path)) {

        } else if (fs::is_directory(arguments.assembler_path)) {

        } else {

        }
        */

        return harc::Error_code::NO_ERROR;
    }

    void parse_arguments(int argc, char* const argv[]) {
        // Return early when no arguments specified at command line
        if (argc < 2) {
            return;
        }

        //Parse singular arguments
        {
            std::string_view first_argument = argv[1];

            if (first_argument.starts_with("--")) {
                first_argument = first_argument.substr(2);
            }

            if (first_argument.starts_with("-")) {
                first_argument = first_argument.substr(1);
            }

            auto it = singular_argument_map.find(first_argument);

            if (it != singular_argument_map.end()) {
                auto response_function = it->second.response;
                response_function(argc, argv);

                // Currently all singular arguments involve the program terminating early
                impl::cli_args.should_terminate_after_parsing_args = true;
                return;
            }
        }


        //Parse named arguments
        std::map<std::string_view, std::string_view> cli_config_map{};

        for (int i = 1; i < argc; ++i) {
            std::string_view curr{argv[i]};
            std::string_view next{};

            if ((i + 1) < argc) {
                next = std::string_view{argv[i + 1]};
            }

            if (curr.starts_with("--")) {
                // Read as full-length parameter

                bool takes_argument = argument_map.at(curr.substr(2)).parser != parse_nothing_as_true;

                if (!takes_argument || next.empty() || next.starts_with("-")) {
                    cli_config_map.emplace(std::pair{
                        std::string_view{argv[i + 0] + 2},
                        std::string_view{}
                    });
                } else {
                    cli_config_map.emplace(std::pair{
                        std::string_view{argv[i + 0] + 2},
                        std::string_view{argv[i + 1]}
                    });
                    ++i;
                }
            } else if (curr.starts_with("-")) {
                // Read as abbreviated parameter
                cli_config_map.emplace(std::pair{
                    std::string_view{argv[i] + 1},
                    std::string_view{}
                });
            } else {
                // Read as source file path
                impl::cli_args.source_paths.emplace_back(argv[i]);
            }
        }

        parse_configuration(cli_config_map);
        Message_buffer::flush();
    }

}
