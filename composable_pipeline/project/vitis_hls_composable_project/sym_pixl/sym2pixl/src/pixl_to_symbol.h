#ifndef __PIXL_TO_SYMBOL_H__
#define __PIXL_TO_SYMBOL_H__
#include "data_path.hpp"

void pixl_to_symbol(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);

#endif
