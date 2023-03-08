#ifndef __DECODER_H__
#define __DECODER_H__
#include "data_path.hpp"

void decoder(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);
void decoder_bit(hls::stream<bool>& y0_in, hls::stream<bool>& y1_in , int mode , hls::stream<bool>& output);
#endif
