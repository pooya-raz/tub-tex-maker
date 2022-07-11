# Tub-Tex-Maker
Consumes the Twelver Usul Bibliography (TUB) MediaWiki API and outputs LaTeX files for publication.

## Prerequisites
What you need to install to build this project and how to install them.

* CMake
  * Install using system package manager.
* VCPKG manager
    * Follow installation instructions [on the website](https://vcpkg.io/en/getting-started.html).
    * Add package location to the cmake tool chain: -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

## Building
1. Clone this repo
2. Install all necessary packages found in CMakeLists.txt with VCPKG
3. To build from the command line, run the following:
   * `cmake --build ./cmake-build-debug --target tub_tex_maker`

## Built with:
* C++20
* libcpr: https://docs.libcpr.org/ for http calls
* Boost-log for logging
* fmt for string formatting. Should remove once std::format is implemented in clang. For updates see here: https://en.cppreference.com/w/cpp/compiler_support
* Google Test for testing.

## Authors
* Christopher Pooya Razavian - *Initial work* - [pooya-raz](https://github.com/pooya-raz)

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
* European Research Council
* University of Exeter
* Robert Gleave - Principle Investigator
