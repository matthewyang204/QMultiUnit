# Building QMultiUnit

QMultiUnit uses CMake to generate builds for its Qt application. These
instructions cover local builds on Windows, macOS, and Linux.

## Prerequisites

Install the following tools before configuring the project:

- [CMake](https://cmake.org/download/) 3.19 or later
- [Qt](https://www.qt.io/download-qt-installer) 6.5 or later (recommended), or
  Qt 5.15
- A C++ compiler supported by the installed Qt version
- [Ninja](https://ninja-build.org/) when using the commands below

The default build uses Qt 6. To use Qt 5, install Qt 5.15 and pass
`-DUSE_QT5=ON` when configuring.

### Additional Windows requirements

- `windeployqt`, supplied with the Qt installation, must be available to CMake.
- [Inno Setup](https://jrsoftware.org/isinfo.php) is required only to create
  the Windows installer.

### Additional Linux requirements

The runtime packages required by the Qt platform plugin may need to be
installed by your distribution. On Ubuntu, the CI build installs these
packages:

```text
libxkbcommon-x11-0 libxcb-cursor0 libxcb-icccm4 libxcb-image0
libxcb-keysyms1 libxcb-render-util0 libxcb-shape0 libxcb-xinerama0 libxcb1
```

## Configure and build

Run these commands from the repository root:

```sh
<Qt prefix>/<version>/<platform>/bin/qt-cmake -S src -B build -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$PWD/package"
cmake --build build --parallel
```

The Qt 6 build is configured by default. For Qt 5, add
`-DUSE_QT5=ON` to the configure command:

```sh
<Qt prefix>/<version>/<platform>/bin/qt-cmake -S src -B build-qt5 -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$PWD/package-qt5" \
  -DUSE_QT5=ON
cmake --build build-qt5 --parallel
```

If CMake cannot find Qt, set `CMAKE_PREFIX_PATH` to the Qt installation
directory, or select the Qt installation through your IDE's CMake
configuration.

Additionally, on macOS, the `SDKROOT` and `MACOSX_DEPLOYMENT_TARGET` environment variables
can be used to control which macOS SDK and target version are used for the build.

## Install or package the build

Install the built application and its Qt runtime dependencies into the
configured prefix:

```sh
cmake --install build
```

On macOS, deploy Qt frameworks into the application bundle after installing:

```sh
macdeployqt package/QMultiUnit.app
```

On Windows, the build automatically runs `windeployqt` as a post-build step.
To create the installer, open `installer/qmultiunit-setup.iss` with Inno Setup
and compile it. The script looks for the executable in `package`, `build`, or
the corresponding `src/build` directories.

## IDE builds

The `src` directory is the CMake source directory. It can be opened directly
in Qt Creator, Visual Studio, or another IDE with CMake support. Select a
`Release` configuration and build the `QMultiUnit` target.

## Cleaning a local build

Build directories are generated files and are ignored by Git. To start with a
fresh configuration, remove the specific build and package directories you
created, then rerun the configure commands:

```sh
rm -rf build package
```
