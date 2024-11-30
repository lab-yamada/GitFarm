cmake_minimum_required(VERSION 3.31.0)
project(gitfarm_algorithm VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(APPLE)
    # macOS
    set(JAVA_AWT_LIBRARY "/opt/homebrew/opt/openjdk@17/libexec/openjdk.jdk/Contents/Home/lib/libjawt.dylib")
    set(JAVA_JVM_LIBRARY "/opt/homebrew/opt/openjdk@17/libexec/openjdk.jdk/Contents/Home/lib/server/libjvm.dylib")
    set(JAVA_INCLUDE_PATH "/opt/homebrew/Cellar/openjdk@17/17.0.13/include/")
    set(JAVA_INCLUDE_PATH2 "/opt/homebrew/Cellar/openjdk@17/17.0.13/libexec/openjdk.jdk/Contents/Home/include/")
    set(JAVA_AWT_INCLUDE_PATH "/opt/homebrew/Cellar/openjdk@17/17.0.13/libexec/openjdk.jdk/Contents/Home/include/")
elseif(UNIX)
    # Linux
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        message(STATUS "Detected x86_64 architecture")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
        set(JAVA_AWT_LIBRARY "/usr/lib/jvm/java-17-openjdk-amd64/lib/libjawt.dylib")
        set(JAVA_JVM_LIBRARY "/usr/lib/jvm/java-17-openjdk-amd64/lib/server/libjvm.so")
        set(JAVA_INCLUDE_PATH "/usr/lib/jvm/java-17-openjdk-amd64/include")
        set(JAVA_INCLUDE_PATH2 "/usr/lib/jvm/java-17-openjdk-amd64/include/linux/")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        message(STATUS "Detected ARM 64-bit architecture")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a")
        set(JAVA_AWT_LIBRARY "/usr/lib/jvm/java-17-openjdk-arm64/lib/libjawt.dylib")
        set(JAVA_JVM_LIBRARY "/usr/lib/jvm/java-17-openjdk-arm64/lib/server/libjvm.so")
        set(JAVA_INCLUDE_PATH "/usr/lib/jvm/java-17-openjdk-arm64/include")
        set(JAVA_INCLUDE_PATH2 "/usr/lib/jvm/java-17-openjdk-arm64/include/linux/")
    else()
        message(STATUS "Detected unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
    set(JAVA_AWT_INCLUDE_PATH JAVA_INCLUDE_PATH2)
endif()

find_package(JNI REQUIRED)
if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_AWT_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(
    include/
    ${JAVA_INCLUDE_PATH}/
    ${JNI_INCLUDE_DIRS}/
)

set(SOURCES
    src/algorithm/algorithm.cpp
    src/jni/random.cpp
    src/domain/item.cpp
    src/jni/jni.c
)

set(LIB_NAME
    gitcha_algorithms
)

add_library(${LIB_NAME} SHARED
    ${SOURCES}
)

target_link_libraries(${LIB_NAME}
    ${JNI_LIBRARIES}
)

set_target_properties(${LIB_NAME} PROPERTIES
    OUTPUT_NAME ${LIB_NAME}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

if(APPLE)
    # macOS
    set_target_properties(${LIB_NAME} PROPERTIES
        SUFFIX ".dylib"
    )
elseif(UNIX)
    # Linux
    set_target_properties(${LIB_NAME} PROPERTIES
        SUFFIX ".so"
    )
endif()

add_executable(test_runner
    test/test.cpp
)

target_link_libraries(test_runner PRIVATE gitcha_algorithms)

set_target_properties(test_runner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
