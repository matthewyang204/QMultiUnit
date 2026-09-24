# Building and sideloading QMultiUnit on mobile

QMultiUnit does not have automated mobile build or release scripts yet. The
steps below describe the manual workflow for creating and installing a
development build.

The project currently includes an Android packaging manifest under
[`src/android`](src/android). iOS builds require an Apple development
environment and signing identity (only need a free developer account to get one if your goal
is to build for development only).

## Android

- A supported Qt 6 installation with an Android kit
- Android SDK, platform tools, and an Android NDK
- CMake and Ninja
- A USB-connected Android device with Developer options and USB debugging
  enabled

See Qt's official [Qt for Android](https://doc.qt.io/qt-6/android.html)
documentation and [Getting Started with Qt for
Android](https://doc.qt.io/qt-6/android-getting-started.html) for supported
SDK, NDK, JDK, and Qt version requirements.

### Build an APK

See the official documentation for instructions

### Sideload an APK

1. Enable **Developer options** and **USB debugging** on the Android device.
2. Connect the device over USB and accept its debugging authorization prompt.
3. Install the APK, replacing the path with the APK produced by the build (note that you
will need to connect it via adb first):

   ```sh
   adb install -r path/to/QMultiUnit.apk
   ```

5. Launch **QMultiUnit** from the device's app launcher.

If Android reports that the package cannot be installed, uninstall an older
build with the same package ID first, or ensure that the new APK is signed
with a compatible key.

## iOS

### Prerequisites

- macOS with Xcode and its command-line tools
- A supported Qt installation with an iOS kit
- An Apple ID or Apple Developer account configured for code signing
- An iPhone or iPad registered for development, or an iOS Simulator

Read Qt's official [Qt for iOS](https://doc.qt.io/qt-6/ios.html)
documentation before configuring the project. It covers the supported Apple
platforms, Xcode requirements, signing, and deployment considerations.

### Build an iOS application

Use the official Qt for iOS documentation for instructions on generating an Xcode project. Afterwards, open the project in Xcode, select a scheme, and build.

### Sideload to a physical device

Use Xcode to install the signed development build directly:

1. Connect the iPhone or iPad to the Mac and trust the computer on the device.
2. Select the device as the run destination in Xcode.
3. Set the QMultiUnit target's signing team and bundle identifier.
4. Build and run the target.
5. If prompted on the device, enable the developer trust setting under
   **Settings > Privacy & Security > Developer Mode** and rerun the app.

For installing it via AltStore:
1. Follow AltStore Classic/PAL instructions for installing AltStore on your device.
2. Make a Payload folder and move the app bundle into it. ZIP the Payload folder and rename it to `QMultiUnit.ipa`.
3. Open AltStore on your device, transfer the IPA, and use it to install the `QMultiUnit.ipa` file.

## Current limitations

- Mobile builds are manual; there is no mobile CI, release automation, or
  downloadable mobile package maintained by this repository yet.
- Android and iOS signing requirements are platform rules and may change with
  SDK, OS, Qt, or Xcode releases.
- Build output locations vary by Qt kit and configuration, so check the
  selected build directory for the generated APK or iOS application.
