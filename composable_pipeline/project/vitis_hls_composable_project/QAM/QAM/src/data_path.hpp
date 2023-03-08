#ifndef _DATA_PATH_H_
#define _DATA_PATH_H_

#include <iostream>
#include <complex>
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <math.h>

#define QAM_unsigned_bit 4
#define QAM_signed_bit 3
#define FFT_LEN 64
#define IN_WL 22
#define IN_IL 7

#define module_id_bit 16
#define para_id_bit 16
#define para_val_bit 32

#define QAM_module_num 2
#define deQAM_module_num 10

typedef ap_uint<64> ap_uint_64;
typedef ap_axiu<64,1,1,1> ap_axiu_64;
typedef ap_int<32> ap_int_32;
typedef signed int int32_t;

#endif
