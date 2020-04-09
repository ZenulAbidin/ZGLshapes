# ZGLshapes
### Zenul_Abidin's OpenGL shape classes

There are no libraries which can create and manipulate 2D and 3D shapes in a framework-independent manner. ZGLshapes aims to bridge the gap by providing a set of classes that represent the most common shapes, and ways to export them into screen-drawable objects.

Currently these classes depend on Qt5, and there are only 2D shapes for now.

This code is **experimental**. It may not compile. There is **no** stable API, the APIs are subject to change without warning.

## Building

You need Boost >= 1.59, because `BOOST_TEST` macro is used in this project which was introduced in that version.

Create a new build directory with `mkdir build; cd build` Then run `cmake ..; make; cmake --install .`. This will install to /usr/local by default. To change the installation prefix use `cmake --install . --prefix /desired/prefix`.

**Attention**: `make install` does not install the files correctly at this time.

## Testing

Run the `./run-tests.sh` script in the generated build directory to run the tests. This file is not automatically regenerated at this time, and needs to be updated manually. Arguments passed to this script will be passed to all of the Boost.Test modules.
