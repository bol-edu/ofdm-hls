#ifndef __CHANNEL_GEN_H__
#define __CHANNEL_GEN_H__
#include "data_path.hpp"

void channel_gen(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);
void rand(hls::stream<ap_fixed<IN_WL,IN_IL>>& pic_out);

#endif
