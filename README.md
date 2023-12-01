Time Series Filter Library
==================

Introduction
------------
TSFlib is a set of c++ classes that can be used to filter time series in either batch or streaming applications. It was originally part of the EPANET-RTX library, a library used for realtime simulation of water distribution systems.
 

 
Find Out More
------------------ 
Get more info from the RTX [official documentation](http://OpenWaterAnalytics.github.com/epanet-rtx/) and the [wiki](https://github.com/OpenWaterAnalytics/epanet-rtx/wiki).




Building
--------

```

conan export deps/local_export/sqlite_modern_cpp
conan install . --profile=x86 --build=missing -s build_type=Release
conan build . --profile=x86 --build=missing -s build_type=Release
conan export-pkg . --profile=x86 -s build_type=Release

# run tests
./build/Release/bin/tsflib_test
```

if you are developing this as a dependent package locally, do this first:

```
conan editable add .

```

### Docker Build

```
docker buildx build -t tsflib-test -f tsflib.docker --platform linux/amd64 .
```
