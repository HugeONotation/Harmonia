#include <harc/Harc.hpp>
#include <harc/Logging.hpp>
#include <harc/Error_reporting.hpp>
#include "harc/cli/CLI.hpp"
#include <fmt/printf.h>

int main(int argc, char* argv[]) {
    using namespace harc;

    // Set up Quill logging library
    initialize_loggers();

    // Parse command line arguments
    cli::parse_arguments(argc, argv);
    if (!Message_buffer::is_empty()) {
        Message_buffer::flush();
        return EXIT_FAILURE;
    }

    // Return early when further work was not requested at command line
    if (cli::arguments.should_terminate_after_parsing_args) {
        return EXIT_SUCCESS;
    }

    // Launch core compiler subroutines
    switch (cli::arguments.network_mode) {
        case cli::Network_mode::LOCAL:       run_locally();     break;
        case cli::Network_mode::SERVER:      run_server();      break;
        case cli::Network_mode::PURE_SERVER: run_pure_server(); break;
        case cli::Network_mode::CLIENT:      run_client();      break;
        default: {
            HARC_LOG_CRITICAL("Encountered unrecognized Network_mode enum value in switch statement.");
            return EXIT_FAILURE;
        }
    }

    // Ensure that error messages are printed out
    auto ret = Message_buffer::is_empty() ? EXIT_SUCCESS : EXIT_FAILURE;
    Message_buffer::flush();
    return ret;
}
