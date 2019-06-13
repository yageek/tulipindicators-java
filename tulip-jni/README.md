# tulip-jni

The JNI part of the java package.

## Development

First the `JAVA_HOME` variable correctly.

Then, assuming the java library has been compiled:

```fish
javah -classpath "$PWD/../../tulip-java/build/libs/net.yageek.tulipindicators.jar" -o include/tulip-wrapping.h -jni net.yageek.tulipindicators.Tulip
```
