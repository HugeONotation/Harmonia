cmake_minimum_required(VERSION 3.0)

add_executable(Unicode_properties
    Unicode_properties.cpp
)

target_compile_features(Unicode_properties PRIVATE cuda_std_17)
#target_include_directories(Unicode_properties.cpp PRIVATE ../include)
