cmake_minimum_required(VERSION 3.20)

project(scheme_cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(scheme
    src/builtin.cpp
    src/environment.cpp
    src/eval.cpp
    src/lambda.cpp
    src/parser.cpp
    src/scheme.cpp
    src/serializer.cpp
    src/tokenizer.cpp
)
target_include_directories(scheme PUBLIC src)

add_executable(scheme-repl app/main.cpp)
target_link_libraries(scheme-repl PRIVATE scheme)

include(CTest)
if(BUILD_TESTING)
    find_package(Catch2 3 QUIET)
    if(Catch2_FOUND)
        add_executable(scheme-tests
            tests/test_boolean.cpp
            tests/test_control_flow.cpp
            tests/test_eval.cpp
            tests/test_integer.cpp
            tests/test_lambda.cpp
            tests/test_list.cpp
            tests/test_symbol.cpp
        )
        target_include_directories(scheme-tests PRIVATE ${PROJECT_SOURCE_DIR})
        target_link_libraries(scheme-tests PRIVATE scheme Catch2::Catch2WithMain)

        include(Catch)
        catch_discover_tests(scheme-tests)
    else()
        message(STATUS "Catch2 3 not found: tests will not be built")
    endif()
endif()
