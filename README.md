#Install


To build from command line:

/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build /Users/pooya/Developer/sandbox/cpp/tub-tex-maker/cmake-build-debug --target tub_tex_maker


VCPKG manager

Uses: 
* libcpr. For installation instructions see: https://docs.libcpr.org/
* Boost-log for logging
* fmt for string formatting. Should remove once std::format is implemented in clang. For updates see here: https://en.cppreference.com/w/cpp/compiler_support