#ifndef __SYMBOL_TO_PIXL_H__
#define __SYMBOL_TO_PIXL_H__
#include "data_path.hpp"

void symbol_to_pixl(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);

#endif
