cmake_minimum_required(VERSION 3.22)
project(tub_pdf_maker)

set(CMAKE_CXX_STANDARD 23)
find_package(cpr CONFIG REQUIRED)
find_package(Boost 1.79.0 REQUIRED COMPONENTS log)

add_executable(tub_pdf_maker src/main.cpp src/services/TubMediaWikiService.cpp src/services/TubMediaWikiService.h src/services/MediaWikiService.h)
target_link_libraries(tub_pdf_maker PRIVATE cpr::cpr)
target_link_libraries(tub_pdf_maker PRIVATE Boost::log)