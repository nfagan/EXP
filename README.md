# EXP

EXP exposes a set of libraries designed to simplify state machine style task coding. Included are utilities / interfaces that enable stimulus display, simplified task construction, and data storage. Check out the examples to see more.

## Building

### Dependencies

* [cmake](https://cmake.org/download/)
* XCode command line tools with support for c++14 (if on mac)
* Visual Studio with support for c++14 (if on windows)
* [glfw](https://github.com/glfw/glfw) - built libs are included, but may need to be rebuilt depending on your environment
* sqlite3 - again, libs are included, but may require rebuilding
* python, if attempting to use the build script `build.py`

### Simplified clone, build, and install

```bash
git clone https://github.com/nfagan/EXP.git --recursive
cd ./EXP
python build.py
```

Libs are installed to the lib-subdirectory in each module.




