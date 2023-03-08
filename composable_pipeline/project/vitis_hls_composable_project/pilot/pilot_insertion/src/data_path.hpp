#ifndef _DATA_PATH_H_
#define _DATA_PATH_H_

#include <complex>
#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>

#define FFT_LEN 64
#define IN_WL 22
#define IN_IL 7
#define para_num 10
#define pilot_real 1
#define pilot_imag 0

#define QAM_unsigned_bit 4
#define QAM_signed_bit 3

#define module_id_bit 16
#define para_id_bit 16
#define para_val_bit 32

#define pilot_insertion_module_num 3
#define pilot_removal_module_num 9

const int truncation_val = pow(2,IN_WL-IN_IL);

#define QAM_normalization 10
const ap_fixed<IN_WL,IN_IL> sqrt_QAM_norm = (ap_fixed<IN_WL,IN_IL>)sqrt(QAM_normalization);

typedef ap_fixed<IN_WL,IN_IL> ap_fixed_bit;
typedef ap_uint<32> ap_uint_32;
typedef ap_uint<64> ap_uint_64;
typedef ap_axiu<64,1,1,1> ap_axiu_64;
typedef signed int int32_t;

#endif
