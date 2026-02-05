# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Project name and current version
project(ShipEditor VERSION 0.1 LANGUAGES CXX)

# Enable general warnings
# See http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Use 2014 C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Creates the compile_commands.json used by editors for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Must use GNUInstallDirs to install libraries into correct locations on all platforms:
include(GNUInstallDirs)

# Pkg_config is used to locate header and files for dependency libraries:
find_package(PkgConfig)

pkg_check_modules(JSONCPP jsoncpp)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

#Include
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

#Linker
link_directories(${JSONCPP_LIBRARY_DIRS})

# Compile files:

file(GLOB SRC_FILES
    "*.cpp"
    "section/*.cpp"
)
add_executable(ShipEditor ${SRC_FILES})

# Add folder with all headers:
target_include_directories(ShipEditor PRIVATE hpp)

# Link files:
target_link_libraries(ShipEditor
    ${GTKMM_LIBRARIES}
    ${JSONCPP_LIBRARIES}
)
