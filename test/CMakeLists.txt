list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

find_package(Catch2 CONFIG REQUIRED)

add_executable(enumerate-tests
    enumerate.test.cpp
    traits.test.cpp
)
target_link_libraries(enumerate-tests
    PRIVATE
        hipony::enumerate
        Catch2::Catch2 Catch2::Catch2WithMain
)
add_test(NAME enumerate-tests COMMAND enumerate-tests)
