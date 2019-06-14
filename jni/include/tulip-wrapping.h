#ifndef __TULIP_JNI
#define __TULIP_JNI

#include "indicators.h"
#include <map>
#include <string>
#include <vector>

namespace tulipindicatorsjava
{

struct TulipResponse
{
    int begin_index;
    std::vector<double> outputs;
};

struct TulipIndicatorInfo
{
    std::string name;
    std::string full_name;

    std::vector<std::string> inputs;
    std::vector<std::string> options;
    std::vector<std::string> outputs;

    int indicator_type;
};

class TulipBindings
{
public:
    TulipBindings();
    TulipResponse call_indicator(const std::string &name, size_t inputs_len, double const *inputs, double const *options);
    const ti_indicator_info *indicator_info(const std::string &name);

private:
    std::map<std::string, const ti_indicator_info *> indicators_map;
};
}; // namespace tulipindicatorsjava

#endif