cmake_minimum_required(VERSION 3.5)

project(enumerate LANGUAGES CXX VERSION 1.0.0)

include(CTest)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(enumerate INTERFACE)
add_library(hipony::enumerate ALIAS enumerate)

target_compile_features(enumerate INTERFACE cxx_std_11)

target_include_directories(
  enumerate
  INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_subdirectory(src)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/hipony-enumerate-config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/hipony-enumerate-config.cmake"
  INSTALL_DESTINATION
  "${CMAKE_INSTALL_LIBDIR}/cmake/hipony-enumerate")

set(ENUMERATE_CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
set(CMAKE_SIZEOF_VOID_P "")
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/hipony-enumerate-config-version.cmake"
  COMPATIBILITY SameMajorVersion)
set(CMAKE_SIZEOF_VOID_P ${ENUMERATE_CMAKE_SIZEOF_VOID_P})

install(TARGETS enumerate
        EXPORT hipony-enumerate
        DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(EXPORT hipony-enumerate
        NAMESPACE hipony::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/hipony-enumerate")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/hipony-enumerate-config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/hipony-enumerate-config-version.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/hipony-enumerate")

install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

export(EXPORT hipony-enumerate
       NAMESPACE hipony::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/hipony-enumerate-targets.cmake")
