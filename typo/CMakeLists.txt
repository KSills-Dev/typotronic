set(HEADERS)

set(SOURCES
    main.cpp)

add_executable(typo ${HEADERS} ${SOURCES})

target_compile_options(typo PUBLIC -std=c++11)
target_compile_options(typo PRIVATE -Wall)
