#ifndef HARMONIA_HARC_HPP
#define HARMONIA_HARC_HPP

#include <harc/Version.hpp>
#include <harc/Errors.hpp>

namespace harc {

    // Harc's version
    constexpr Version version{0, 0, 0, Release_type::ALPHA};

    ///
    /// Run Harc as a client
    ///
    /// \return
    void run_client();

    ///
    /// Run Harc as a server
    /// This instance of Harc will not perform compilation tasks
    ///
    /// \return
    void run_pure_server();

    ///
    /// Run Harc as a server.
    /// This instance of Harc will also perform compilation tasks.
    ///
    /// \return
    void run_server();

    ///
    /// Run Harc purely locally.
    ///
    /// \return
    void run_locally();

}

#endif //HARMONIA_HARC_HPP
