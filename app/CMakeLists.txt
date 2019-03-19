cmake_minimum_required(VERSION 3.4.1)

set(ARCH arch-arm64)
#add_compile_options(-std=c++17)

include_directories(${CMAKE_SOURCE_DIR}/src/main/jniLibs/include)

add_library( # Sets the name of the library.
        jni_btc_oracle_core_wrapper

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/jni/btc_oracle_core_wrapper_Transaction.cpp
        src/main/jni/btc_oracle_core_wrapper_Script.cpp
        src/main/jni/jni_utils.cpp)

target_include_directories(jni_btc_oracle_core_wrapper PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/main/jniLibs>
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)


add_library(btc_oracle_core SHARED IMPORTED)
        set_target_properties(btc_oracle_core
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libbtc_oracle_core.so)

target_link_libraries( # Specifies the target library.
        jni_btc_oracle_core_wrapper
        btc_oracle_core
        #wallycore

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        )