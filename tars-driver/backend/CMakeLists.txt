add_library(tarsBackend SimBackend.cpp)

target_include_directories(tarsBackend 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(tarsCore PUBLIC cxx_std_17)