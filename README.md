# QMultiUnit

<img alt="QMultiUnit screenshot" src="https://archive.org/download/misc-objects-storage/QMultiUnit-screenshot-1.png" width="450"/>

QMultiUnit is a unit converter built with C++ and Qt. It is available as a
portable application bundle for macOS & Linux, and the Windows build are packaged as an
installer that can be installed into either the per-user program files or the system program files directories.

## System requirements
- Windows 7 or later, macOS High Sierra or later, Linux (any modern distribution), iOS 15 or later, or Android 10 or later

### Additional Requirements For Building From Source
- Windows 10 or later, macOS Big Sur or later, or Linux (same as the system requirements above)
- Qt 6.5 or later (recommended), or Qt 5.15 when building with the Qt 5
  compatibility option
- CMake 3.19 or later
- A C++ compiler supported by the selected Qt version

## Installing

Download a package from the project's releases, or build one locally by
following [BUILDING.md](BUILDING.md), which provides instructions for building
for desktop.

On Windows, run the generated setup installer. The
installer allows a per-user installation or an installation under Program
Files.

On macOS, download the ZIP containing the application, and extract it to your desired location. Please note that currently because the application is not notarized, you will need to use `xattr -cr <path-to-application>` or disable Gatekeeper before using it.

On Linux, download the ZIP containing the application, and extract it to your desired location. The executable is located at `<your-extraction-path>/bin/QMultiUnit`.

iOS & Android are coming soon to their respective application stores, but for now you will need to sideload it. Follow [MOBILE.md](MOBILE.md) for instructions for mobile platforms.

## Building

Build requirements, platform-specific dependencies, CMake commands, deployment
steps, and Windows installer instructions for desktop are documented in
[BUILDING.md](BUILDING.md).

Info for mobile platforms is in [MOBILE.md](MOBILE.md).

Qt also has pretty good documentation for those new to building applications with it on its [website](https://doc.qt.io/).

## License

QMultiUnit is licensed under the GNU General Public License v3.0. See
[LICENSE](LICENSE) for the full license text.
