#ifndef __TOP_MODULE_ECC_H__
#define __TOP_MODULE_ECC_H__
#include "data_path.hpp"
#include "master_mem_src/master2stream.h"
#include "master_mem_src/stream2master.h"
#include "sym2pixl_src/pixl_to_symbol.h"
#include "sym2pixl_src/symbol_to_pixl.h"
#include "QAM_src/QAM.hpp"
#include "QAM_src/deQAM.hpp"
#include "pilot_src/pilot_insertion.h"
#include "pilot_src/equalizer_pilot_removal.h"
#include "IFFT_src/fft.hpp"
#include "CP_src/CP_insertion.h"
#include "CP_src/CP_removal.h"
#include "channel_src/channel_gen.h"
#include "ecc_src/encoder.h"
#include "ecc_src/decoder.h"

void top_module(ap_uint_64* data_in, ap_uint_64* data_out);

#endif
