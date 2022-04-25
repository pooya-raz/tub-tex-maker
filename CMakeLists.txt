cmake_minimum_required(VERSION 3.22)
project(tub_pdf_maker)

set(CMAKE_CXX_STANDARD 23)
find_package(cpr CONFIG REQUIRED)
find_package(Boost 1.79.0 REQUIRED COMPONENTS log)
find_package(GTest CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(tub_pdf_maker
        src/main.cpp
        src/services/mediawiki_service.h
        src/services/tub_mediawiki_service.cpp src/services/tub_mediawiki_service.h
        src/services/file_writer_service.cpp src/services/file_writer_service.h
        src/tub_json.cpp src/tub_json.h
        src/models/entry.cpp src/models/entry.h
        src/entry_builder.cpp src/entry_builder.h)
target_link_libraries(tub_pdf_maker PRIVATE cpr::cpr)
target_link_libraries(tub_pdf_maker PRIVATE Boost::log)
target_link_libraries(tub_pdf_maker PRIVATE nlohmann_json::nlohmann_json)
add_compile_options(-g -Wall -Wextra -Wno-unused-parameter -Wno-reorder -Werror=return-type)

enable_testing()

add_executable(
        TubMediaWiki_test
        tests/tub_mediawiki_test.cpp
        src/services/tub_mediawiki_service.h src/services/tub_mediawiki_service.cpp
        src/services/mediawiki_service.h
        src/tub_json.cpp src/tub_json.h
        tests/tub_json_test.cpp
        src/models/entry.cpp src/models/entry.h
        src/entry_builder.cpp src/entry_builder.h
        )
target_link_libraries(
        TubMediaWiki_test
        GTest::gtest_main
        cpr::cpr
        Boost::log
)

include(GoogleTest)

gtest_discover_tests(TubMediaWiki_test)

