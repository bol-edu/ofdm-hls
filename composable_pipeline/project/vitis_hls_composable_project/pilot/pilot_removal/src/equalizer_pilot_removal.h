#ifndef __EQUALIZER_PILOT_REMOVAL_H__
#define __EQUALIZER_PILOT_REMOVAL_H__

#include "data_path.hpp"

void equalizer_pilot_removal(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out);

#endif
