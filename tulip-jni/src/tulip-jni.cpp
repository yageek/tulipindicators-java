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
    if (!global_list)
    {
        global_list = std::unique_ptr<TulipBindings>(new TulipBindings());
    }
    list_mutex.unlock();
}

JNIEXPORT jobject JNICALL Java_net_yageek_tulipindicators_Tulip_call_1indicator(JNIEnv *env, jobject obj, jstring string, jdoubleArray inputs, jdoubleArray options)
{
    // Only options could be NULL
    if (inputs == nullptr || string == nullptr)
    {
        return nullptr;
    }

    // We convert the elements from Java -> C++
    TulipResponse resp;
    jdouble *inputsC = nullptr;
    jdouble *optionsC = nullptr;
    jsize input_length = 0;

    jdoubleArray outs = nullptr;
    jclass cls = nullptr;
    jmethodID constructor = nullptr;
    jobject resp_obj = nullptr;
    jsize out_size = 0;

    // Name
    const char *input_name = env->GetStringUTFChars(string, nullptr);
    if (input_name == nullptr)
    {
        return nullptr;
    }
    std::string indicator_name(input_name);
    env->ReleaseStringUTFChars(string, input_name);

    // Inputs
    inputsC = env->GetDoubleArrayElements(inputs, NULL);
    if (inputsC == nullptr)
    {
        goto out;
    }
    input_length = env->GetArrayLength(inputs);

    // Options
    if (options != nullptr)
    {
        optionsC = env->GetDoubleArrayElements(options, NULL);
        if (optionsC == nullptr)
        {
            goto release_inputs;
        }
    }

    // We compute the value
    list_mutex.lock();
    resp = global_list->call_indicator(indicator_name, size_t(input_length), &inputsC, optionsC);
    list_mutex.unlock();

    // Read the outputs values
    outs = env->NewDoubleArray(out_size);
    if(outs == nullptr) {
        goto release_options;
    }

    env->SetDoubleArrayRegion(outs, 0, out_size, &resp.outputs[0]);

    // Now call the constructor response
    cls = env->FindClass("net/yageek/tulipindicators/TulipRawResponse");
    if(cls == nullptr) {
        return nullptr;
    }
    constructor = env->GetMethodID(cls, "<init>", "(I[D)V");
     if(constructor == nullptr) {
        return nullptr;
    }
    resp_obj = env->NewObject(cls, constructor, resp.begin_index, outs);
    return resp_obj;

release_options:
    if(options != nullptr) {
        env->ReleaseDoubleArrayElements(options, optionsC, 0);
    }
release_inputs:
    env->ReleaseDoubleArrayElements(inputs, inputsC, 0);
out:
    return nullptr;
}