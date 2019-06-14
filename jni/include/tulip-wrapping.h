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

class TulipBindings
{
public:
    TulipBindings();
    TulipResponse call_indicator(const std::string &name, size_t inputs_len, double const *inputs, double const *options);

private:
    std::map<std::string, const ti_indicator_info *> indicators_map;
};
}; // namespace tulipindicatorsjava

#endif