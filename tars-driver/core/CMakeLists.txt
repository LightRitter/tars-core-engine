add_library(tarsCore Driver.cpp StateMachine.cpp)

target_include_directories(tarsCore 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(tarsCore PUBLIC cxx_std_17)