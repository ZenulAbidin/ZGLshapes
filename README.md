# ZGLshapes
### Zenul_Abidin's OpenGL shape classes

There are no libraries which can create and manipulate 2D and 3D shapes in a framework-independent manner. ZGLshapes aims to bridge the gap by providing a set of classes that represent the most common shapes, and ways to export them into screen-drawable objects.

Currently these classes depend on Qt5, and there are only 2D shapes for now.

This code is **experimental**. It may not compile. There is **no** stable API, the APIs are subject to change without warning. This decision might change in the future.

## Building

You need Boost >= 1.59, because `BOOST_TEST` macro is used in this project which was introduced in that version. For now, you also need Qt5.

Create a new build directory with `mkdir build; cd build` Then run `cmake ..; make; cmake --install .`. This will install to /usr/local by default. To change the installation prefix use `cmake --install . --prefix /desired/prefix`.

By default, all of the tests are built along with the library. If you don't want to build tests, pass `-DNO_TESTS=true` to CMake. To build only specific test suites, pass `-DALL_TESTS=false -DTEST_testdirname=true -DTEST_testdirname2=true (etc.)` to CMake, where `testdirname` is the name of the directory under `tests/` in uppercase containing tests that you want to build.

**Attention**: `make install` does not install the files correctly at this time.

## Testing

Run `tests/run-tests` in the generated build directory to run the tests. The source file for this test wrapper `tests/run-tests.cpp` contains a variable with the arguments that will be passed to all Boost.Test modules.
