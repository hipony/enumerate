if(BUILD_TESTING)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

    find_package(Catch2 CONFIG REQUIRED)

    add_executable(enumerate-cpp11-tests enumerate.test.cpp)
    target_link_libraries(enumerate-cpp11-tests
        PRIVATE
            hipony::enumerate
            Catch2::Catch2 Catch2::Catch2WithMain
    )
    add_test(NAME enumerate-cpp11-tests COMMAND enumerate-cpp11-tests)

    add_executable(enumerate-cpp14-tests enumerate.test.cpp)
    target_link_libraries(enumerate-cpp14-tests
        PRIVATE
            hipony::enumerate
            Catch2::Catch2 Catch2::Catch2WithMain
    )
    target_compile_features(enumerate-cpp14-tests INTERFACE cxx_std_14)
    add_test(NAME enumerate-cpp14-tests COMMAND enumerate-cpp14-tests)

    add_executable(enumerate-cpp17-tests enumerate.test.cpp)
    target_link_libraries(enumerate-cpp17-tests
        PRIVATE
            hipony::enumerate
            Catch2::Catch2 Catch2::Catch2WithMain
    )
    target_compile_features(enumerate-cpp17-tests INTERFACE cxx_std_17)
    add_test(NAME enumerate-cpp17-tests COMMAND enumerate-cpp17-tests)

    add_executable(enumerate-cpp20-tests
        enumerate.test.cpp
        enumerate.cpp20.test.cpp
    )
    target_link_libraries(enumerate-cpp20-tests
        PRIVATE
            hipony::enumerate
            Catch2::Catch2 Catch2::Catch2WithMain
    )
    target_compile_features(enumerate-cpp20-tests  INTERFACE cxx_std_20)
    add_test(NAME enumerate-cpp20-tests COMMAND enumerate-cpp20-tests)
endif()
