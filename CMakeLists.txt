cmake_minimum_required(VERSION 3.6)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(mygbemu)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.3
)
FetchContent_MakeAvailable(SDL2)

file (GLOB_RECURSE mygbemu_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/emulator/*.c)
file (GLOB_RECURSE mygbemu_HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/emulator/*.h)

add_executable(mygbemu ${mygbemu_SOURCES} ${mygbemu_HEADERS})
target_include_directories(mygbemu PUBLIC ${CMAKE_SOURCE_DIR}/emulator/)
target_link_libraries(mygbemu PRIVATE SDL2 SDL2main)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT mygbemu)
