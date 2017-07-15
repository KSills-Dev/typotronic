set(HEADERS
    costs.hpp
    layout.hpp
    typo.hpp
    io.hpp)

if (${tests_enabled} MATCHES "ON")
    message("Tests building")
else(${tests_enabled} MATCHES "ON")
endif(${tests_enabled} MATCHES "ON")

set(SOURCES
    costs.cpp
    layout.cpp
    typo.cpp
    io.cpp)

add_executable(typo ${HEADERS} main.cpp ${SOURCES})

target_compile_options(typo PUBLIC -std=c++11)
target_compile_options(typo PRIVATE -Wall)


OPTION(TESTS_ENABLED "Enable project test build." OFF)
if (TESTS_ENABLED)
    message("Building tests.")

    add_executable(typo-test ${HEADERS} test.cpp ${SOURCES})

    target_compile_definitions(typo-test PRIVATE "-DTESTS_ENABLED")
    target_compile_options(typo-test PUBLIC -std=c++11)
    target_compile_options(typo-test PRIVATE -Wall)
endif(TESTS_ENABLED)
