cmake_minimum_required(VERSION 3.22)
project(tub_pdf_maker VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
find_package(cpr CONFIG REQUIRED)
find_package(Boost 1.79.0 REQUIRED COMPONENTS log)
find_package(GTest CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(tub_pdf_maker
        src/main.cpp
        src/io/mediawiki.h
        src/io/tub_mediawiki.cpp src/io/tub_mediawiki.h
        src/io/file_writer.cpp src/io/file_writer.h
        src/TubJson.cpp src/TubJson.h
        src/models/entry.cpp src/models/entry.h
        src/builders/entry_builder.cpp src/builders/entry_builder.h
        src/models/author.cpp src/models/author.h
        src/models/title_type.h)
target_link_libraries(tub_pdf_maker PRIVATE cpr::cpr)
target_link_libraries(tub_pdf_maker PRIVATE Boost::log)
target_link_libraries(tub_pdf_maker PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(tub_pdf_maker PRIVATE fmt::fmt)

enable_testing()

add_executable(
        TubMediaWiki_test
        src/io/tub_mediawiki.h src/io/tub_mediawiki.cpp
        src/io/mediawiki.h
        src/TubJson.cpp src/TubJson.h
        src/models/entry.cpp src/models/entry.h
        src/builders/entry_builder.cpp src/builders/entry_builder.h src/builders/entry_builder.test.cpp
        src/models/author.cpp src/models/author.h
        src/models/title_type.h src/TubJson.test.cpp)
target_link_libraries(
        TubMediaWiki_test
        GTest::gtest_main
        cpr::cpr
        Boost::log
        fmt::fmt
)

include(GoogleTest)

gtest_discover_tests(TubMediaWiki_test)

