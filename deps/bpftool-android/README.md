# BPFTool for Android

The existing files have been built AOSP tree for Pixel-9(Codename: Tokay) device.

## Build commands

In case you wish to build a different version of BPFTool for Android from a particular AOSP source-tree, assuming the project has been configured earlier, after ensuring the `AOSP_ROOT` variable in `cmake/aosp.cmake` is setup to root directory of AOSP source code, run the following command:

```shell
$ cd <repository-root>
$ cd build-dir
$ cmake --build . --target build_aosp_libs
```

