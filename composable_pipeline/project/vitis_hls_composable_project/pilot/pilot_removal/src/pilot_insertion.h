#ifndef __PILOT_INSERTION_H__
#define __PILOT_INSERTION_H__
#include "data_path.hpp"

void pilot_insertion(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);

#endif
