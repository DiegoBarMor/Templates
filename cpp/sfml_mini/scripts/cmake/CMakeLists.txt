cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE APP_SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(APPEND APP_SRC_FILES ${CMAKE_SOURCE_DIR}/main.cpp)

# get_filename_component(TARGET_NAME ${CMAKE_SOURCE_DIR} NAME)
set(TARGET_NAME app)

add_executable(${TARGET_NAME} ${APP_SRC_FILES})
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${TARGET_NAME}
    PRIVATE
        SFML::Graphics
)
