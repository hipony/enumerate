if(BUILD_TESTING)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

    add_executable(enumerate-tests enumerate.test.cpp)
    target_link_libraries(enumerate-tests PRIVATE hipony::enumerate)

    find_package(Catch2 CONFIG REQUIRED)
    target_link_libraries(enumerate-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

    add_test(enumerate-tests enumerate-tests)
endif()
