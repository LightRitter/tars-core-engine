add_executable(tars_sim main.cpp)

target_link_libraries(tars_sim
    PRIVATE
        tarsCore
        tarsBackend)