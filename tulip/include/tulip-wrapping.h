
#include <jni.h>

#ifndef __TULIP_JNI_WRAPPING
#define __TULIP_JNI_WRAPPING

extern "C"
{
    JNIEXPORT void JNICALL Java_simplejni_Main_printHello(JNIEnv *, jobject);
}
#endif