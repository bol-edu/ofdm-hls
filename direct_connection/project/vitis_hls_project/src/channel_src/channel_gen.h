#ifndef __CHANNEL_GEN_H__
#define __CHANNEL_GEN_H__
#include "../data_path.hpp"

void channel_gen(ap_uint_64_str& data_in, ap_uint_64_str& data_out);
void rand(hls::stream<ap_fixed_bit>& pic_out);

#endif
