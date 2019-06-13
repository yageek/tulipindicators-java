#include "tulip-jni.h"
#include "tulip-wrapping.h"
#include <jni.h>
#include <memory>
#include <mutex>

using tulipindicatorsjava::TulipBindings;
using tulipindicatorsjava::TulipResponse;

static std::unique_ptr<TulipBindings> global_list;
static std::mutex list_mutex;

JNIEXPORT void JNICALL Java_net_yageek_tulipindicators_Tulip_loadIndicators(JNIEnv *env, jobject obj)
{
    list_mutex.lock();
    if(!global_list) {
        global_list = std::unique_ptr<TulipBindings>(new TulipBindings());
    }
    list_mutex.unlock();
}

JNIEXPORT jobject JNICALL Java_net_yageek_tulipindicators_Tulip_call_1indicator(JNIEnv *env, jobject obj, jstring string, jdoubleArray inputs, jdoubleArray options)
{       
    // We convert the elements from Java -> C++
    TulipResponse resp;
    jdouble *inputsC(nullptr);
    jdouble *optionsC(nullptr);
    jsize input_length = 0;

    // Name
    const char *input_name = env->GetStringUTFChars(string, nullptr);
    if (input_name == nullptr) {
        return nullptr;
    }
    std::string indicator_name(input_name);
    env->ReleaseStringUTFChars(string, input_name);

    // Inputs
    inputsC = env->GetDoubleArrayElements(inputs, NULL);
    if (inputsC == nullptr) {
        goto out;
    }
    input_length = env->GetArrayLength(inputs);

    // Options
    optionsC = env->GetDoubleArrayElements(options, NULL); 
    if (optionsC == nullptr) {
        goto release_inputs;
    }

    // We compute the value
    list_mutex.lock();
    resp = global_list->call_indicator(indicator_name, size_t(input_length), &inputsC, optionsC);
    list_mutex.unlock();

    // We transform the elements

    return nullptr;

    env->ReleaseDoubleArrayElements(options, optionsC, 0);
release_inputs:
    env->ReleaseDoubleArrayElements(inputs, inputsC, 0);
out:
    return nullptr;

}