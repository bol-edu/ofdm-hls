#ifndef __CP_REMOVAL_H__
#define __CP_REMOVAL_H__
#include "data_path.hpp"

void CP_removal(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);

#endif