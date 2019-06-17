#include "tulip-jni.h"
#include "tulip-wrapping.h"
#include <jni.h>
#include <memory>
#include <mutex>

using tulipindicatorsjava::TulipBindings;
using tulipindicatorsjava::TulipResponse;

static std::unique_ptr<TulipBindings> global_list;
static std::mutex list_mutex;

JNIEXPORT void JNICALL Java_net_yageek_tulipindicators_Bindings_loadIndicators(JNIEnv *env, jobject obj)
{
    list_mutex.lock();
    if (!global_list)
    {
        global_list = std::unique_ptr<TulipBindings>(new TulipBindings());
    }
    list_mutex.unlock();
}

jobjectArray _java_string_array_from_c_string(JNIEnv *env, size_t len, char *const *names)
{
    // Get string class
    jclass string_cls = env->FindClass("java/lang/String");

    // Convert the first
    jstring first = env->NewStringUTF(names[0]);
    if (!first)
    {
        return nullptr;
    }

    jobjectArray array = env->NewObjectArray(len, string_cls, first);
    if (!array)
    {
        return nullptr;
    }

    for (int i = 1; i < len; i++)
    {
        jstring first = env->NewStringUTF(names[0]);
        if (!first)
        {
            return nullptr;
        }
        env->SetObjectArrayElement(array, i, first);
    }

    return array;
}

JNIEXPORT jobject JNICALL Java_net_yageek_tulipindicators_Bindings_getIndicatorInfo(JNIEnv *env, jobject obj, jstring name)
{

    if (!name)
    {
        return nullptr;
    }

    // Get the name of the indicator
    const char *input_name = env->GetStringUTFChars(name, nullptr);
    if (!input_name)
    {
        return nullptr;
    }
    std::string indicator_name(input_name);
    env->ReleaseStringUTFChars(name, input_name);

    // Search
    const ti_indicator_info *info = nullptr;
    list_mutex.lock();
    if (!global_list)
    {
        return nullptr;
    }
    info = global_list->indicator_info(indicator_name);
    list_mutex.unlock();

    // Allocate every element names
    jstring info_name = env->NewStringUTF(&info->name[0]);
    jstring info_full_name = env->NewStringUTF(&info->full_name[0]);
    jobjectArray info_inputs = _java_string_array_from_c_string(env, info->inputs, &info->input_names[0]);
    jobjectArray info_options = _java_string_array_from_c_string(env, info->options, &info->option_names[0]);
    jobjectArray info_outputs = _java_string_array_from_c_string(env, info->outputs, &info->output_names[0]);

    // Allocate Info
    jclass cls = env->FindClass("net/yageek/tulipindicators/Bindings$IndicatorInfo");
    if (!cls)
    {
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;I)V");
    if (!constructor)
    {
        return nullptr;
    }

    jobject indicator = env->NewObject(cls, constructor, info_name, info_full_name, info_inputs, info_options, info_outputs, info->type);
    return indicator;
}

JNIEXPORT jobject JNICALL Java_net_yageek_tulipindicators_Bindings_callIndicator(JNIEnv *env, jobject obj, jstring string, jdoubleArray inputs, jdoubleArray options)
{

    // Only options could be NULL
    if (!inputs || !string)
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
    if (!input_name)
    {
        return nullptr;
    }
    std::string indicator_name(input_name);
    env->ReleaseStringUTFChars(string, input_name);

    // Inputs
    inputsC = env->GetDoubleArrayElements(inputs, NULL);
    if (!inputsC)
    {
        goto out;
    }
    input_length = env->GetArrayLength(inputs);

    // Options
    if (options)
    {
        optionsC = env->GetDoubleArrayElements(options, NULL);
        if (!optionsC)
        {
            goto release_inputs;
        }
    }

    // We compute the value
    list_mutex.lock();
    if (!global_list)
    {
        return nullptr;
    }
    resp = global_list->call_indicator(indicator_name, size_t(input_length), &inputsC[0], &optionsC[0]);
    list_mutex.unlock();

    // Read the outputs values
    out_size = resp.outputs.size();
    outs = env->NewDoubleArray(out_size);
    if (!outs)
    {
        goto release_options;
    }

    env->SetDoubleArrayRegion(outs, 0, out_size, &resp.outputs[0]);

    // Now call the constructor response
    cls = env->FindClass("net/yageek/tulipindicators/Bindings$Response");
    if (!cls)
    {
        return nullptr;
    }
    constructor = env->GetMethodID(cls, "<init>", "(I[D)V");
    if (!constructor)
    {
        return nullptr;
    }
    resp_obj = env->NewObject(cls, constructor, resp.begin_index, outs);
    return resp_obj;

release_options:
    if (options)
    {
        env->ReleaseDoubleArrayElements(options, optionsC, 0);
    }
release_inputs:
    env->ReleaseDoubleArrayElements(inputs, inputsC, 0);
out:
    return nullptr;
}