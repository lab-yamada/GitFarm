cmake_minimum_required(VERSION 3.31.0)
project(gitcha_algorithms VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include/
)

add_library(gitcha_algorithms SHARED
    src/algorithm/pity.cpp
    src/algorithm/wrs.cpp
)

set_target_properties(gitcha_algorithms PROPERTIES
    OUTPUT_NAME "gitcha_algorithms"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

if(APPLE)
    # macOS
    set_target_properties(gitcha_algorithms PROPERTIES
        SUFFIX ".dylib"
    )
elseif(UNIX)
    # Linux
    set_target_properties(gitcha_algorithms PROPERTIES
        SUFFIX ".so"
    )
elseif(WINDOW)
    # Window
    set_target_properties(gitcha_algorithms PROPERTIES
        SUFFIX ".dll"
    )
endif()

add_executable(test_runner
    test/test.cpp
)

target_link_libraries(test_runner PRIVATE gitcha_algorithms)

set_target_properties(test_runner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
