#include "tulip-wrapping.h"
#include <assert.h>
#include <iostream>
using namespace tulipindicatorsjava;

TulipBindings::TulipBindings()
{

    std::map<std::string, const ti_indicator_info *> map;
    // Load all the elements
    const ti_indicator_info *info = &ti_indicators[0];

    while (info->name != 0)
    {

        auto key = std::string(info->name);
        map.insert(std::pair<std::string, const ti_indicator_info *>(key, info));

        info += 1;
    }

    this->indicators_map = map;
}

TulipResponse TulipBindings::call_indicator(const std::string &name, size_t inputs_len, double const *const *inputs, double const *options)
{
    // We assume only valid call will be made
    auto search = this->indicators_map.find(name);
    if(search == this->indicators_map.end()) {
        std::cout << "Not FOUND" << std::endl;
    }
    const ti_indicator_info *info = search->second;

    size_t in_array_size = inputs_len / info->inputs;
    int begin_idx = info->start(options);
    size_t count = in_array_size - begin_idx;

    // Allocate outputs
    std::vector<double> outs(count);

    std::vector<const double *> all_inputs(info->inputs);
    for (auto i = 0; i < info->inputs; i++)
    {
        all_inputs[i] = inputs[i * in_array_size];
    }

    std::vector<double *> all_outputs(info->inputs);
    for (auto i = 0; i < info->outputs; i++)
    {
        all_outputs[i] = &outs[i * count];
    }

    int result = info->indicator(in_array_size, &all_inputs[0], options, &all_outputs[0]);

    assert(result == TI_OKAY);

    return TulipResponse{.begin_index = begin_idx, .outputs = outs};
}
