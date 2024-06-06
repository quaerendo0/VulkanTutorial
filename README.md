1) Install vcpkg and cmake
2) Set
```
   -DCMAKE_TOOLCHAIN_FILE=<your-vcpkg-path>\scripts\buildsystems\vcpkg.cmake
   -DVCPKG_MANIFEST_MODE:BOOL=ON
```
3) Cmake generation and program build should work ok now