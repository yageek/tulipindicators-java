#include <string.h>
#include "tulip-wrapping.h"

JNIEXPORT void JNICALL Java_simplejni_Main_printHello(JNIEnv *env, jobject obj)
{
    printf("hello Java \n");
}