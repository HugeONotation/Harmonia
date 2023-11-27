cmake_minimum_required(VERSION 3.20)

#==========================================================
# Compilation options
#==========================================================

option(HARC_USE_POSIX ON)

option(HARC_USE_CUDA OFF)

#==========================================================
# Project
#==========================================================

if(HARC_USE_CUDA)
    project(HARC LANGUAGES CXX CUDA)
else()
    project(HARC LANGUAGES CXX)
endif()

add_executable(Harc
    include/harc/Harc.hpp
    src/Harc.cpp

    include/harc/common/OS_utils.hpp
    src/common/OS_utils.cpp

    include/harc/Settings.hpp

    include/harc/parser/Operators.hpp

    include/harc/Error_reporting.hpp
    src/Error_reporting.cpp

    include/harc/cli/CLI.hpp
    src/cli/CLI.cpp

    include/harc/Logging.hpp
    src/Logging.cpp

    include/harc/lexer/Lexer.hpp
    src/lexer/Lexer.cpp

    include/harc/lexer/Tokens.hpp
    src/lexer/Tokens.cpp

    include/harc/Translation_unit.hpp
    src/Translation_unit.cpp

    include/harc/parser/Parser.hpp
    src/parser/Parser.cpp

    include/harc/parser/Printer.hpp
    src/parser/Printer.cpp

    include/harc/parser/Parse_tree_visitor.hpp

    include/harc/Errors.hpp
    src/Errors.cpp

    include/harc/emitter/Emitter.hpp
    src/emitter/Emitter.cpp

    include/harc/prepass/Prepass_errors.hpp

    include/harc/prepass/Prepass.hpp

    include/harc/common/Algorithms.hpp
    src/common/Algorithms.cpp

    src/prepass/Prepass.cpp
    include/harc/Networking.hpp
    src/Main.cpp
    include/harc/cli/CLI_arguments.hpp
    src/cli/CLI_arguments.cpp
    include/harc/cli/Errors.hpp
    src/cli/Errors.cpp
)

# Code for detecting target operating system capabilities
if(HARC_USE_POSIX)
    target_compile_definitions(Harc PRIVATE HARC_POSIX=1)
endif()

#==========================================================
# Interprocedural optimization
#==========================================================

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT error)

if(ipo_supported)
    set_property(TARGET Harc PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

#==========================================================
# Harc executable targets
#==========================================================

set(HARC_CUDA_DEBUG_FLAGS "-G" "-g")

set(HARC_CXX_FLAGS "-march=native")
set(HARC_CUDA_FLAGS "$<$<CONFIG:Debug>:${HARC_CUDA_DEBUG_FLAGS}>")

target_compile_options(Harc PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${HARC_CXX_FLAGS}>")
target_compile_options(Harc PRIVATE "$<$<COMPILE_LANGUAGE:CUDA>:${HARC_CUDA_FLAGS}>")

target_compile_features(Harc PUBLIC cxx_std_20)
find_package(ICU 70.1 COMPONENTS uc i18n REQUIRED)

target_link_libraries(Harc PRIVATE quill AUL fmt ICU::uc ICU::i18n)
target_include_directories(Harc PRIVATE ./include/)

# This target is used to create a symbolic link from the location of the
# generated executable to the assets folder
add_custom_target(Link_assets
    COMMAND cmake -E create_symlink "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
)

add_dependencies(Harc Link_assets)

#==========================================================
# CUDA details
#==========================================================

if(HARC_USE_CUDA)
    add_library(Harc_cuda STATIC
        include/harc/lexer_cuda/Lexer_cuda.hpp
        src/lexer_cuda/Lexer_cuda.cu

        src/cuda_common/Codepoint_manipulation.cu
        include/harc/cuda_common/Codepoint_manipulation.cuh
        include/harc/cuda_common/Algorithms.cuh

        include/harc/lexer/Lexing_errors.hpp

        include/harc/Translation_unit_cuda.hpp
        src/Translation_unit_cuda.cpp

        src/cuda_common/Synchronization.cu

        include/harc/Harc_cuda.hpp
        src/Harc_cuda.cpp

        include/harc/cuda_common/Codepoint_manipulation_tables.cuh
        src/cuda_common/Algorithm.cu
    )

    set_target_properties(Harc_cuda PROPERTIES CUDA_ARCHITECTURES 61)

    find_package(CUDAToolkit REQUIRED)

    target_link_libraries(Harc_cuda PRIVATE CUDA::cudart)

    set_target_properties(Harc_cuda PROPERTIES CUDA_SEPARABLE_COMPILATION OFF)

    target_link_libraries(Harc_cuda PRIVATE cuda)

    target_compile_features(Harc_cuda PRIVATE cuda_std_20)

    target_link_libraries(Harc_cuda PRIVATE AUL quill cuda cudart)

    target_include_directories(Harc_cuda PRIVATE ./include/ ${CUDA_INCLUDE_DIRS} ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

    target_compile_definitions(Harc PRIVATE HARC_CUDA=1)
    target_compile_definitions(Harc_cuda PRIVATE HARC_CUDA=1)

    target_link_libraries(Harc PRIVATE Harc_cuda)

else()
    target_compile_definitions(Harc PRIVATE HARC_CUDA=0)

endif()

#==========================================================
# Misc.
#==========================================================

add_subdirectory(support/)
