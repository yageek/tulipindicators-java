# tulip-jni

The JNI part of the java package.

## Build

### macOS

```sh
meson build -Djni_include=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/JavaVM.framework/Versions/A/Headers/
cd build
ninja
```

## Development

First the `JAVA_HOME` variable correctly.

Then, assuming the java library has been compiled:

```fish
javah -classpath "$PWD/../../tulip-java/build/libs/net.yageek.tulipindicators.jar" -o include/tulip-wrapping.h -jni net.yageek.tulipindicators.Tulip
```
