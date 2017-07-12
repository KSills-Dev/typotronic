set(HEADERS
    util.hpp
    costs.hpp
    layout.hpp
    typo.hpp)

set(SOURCES
    main.cpp
    util.cpp
    costs.cpp
    layout.cpp)

add_executable(typo ${HEADERS} ${SOURCES})

target_compile_options(typo PUBLIC -std=c++11)
target_compile_options(typo PRIVATE -Wall)