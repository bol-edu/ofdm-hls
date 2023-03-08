#ifndef __ENCODER_H__
#define __ENCODER_H__
#include "data_path.hpp"

void encoder(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);

#endif
