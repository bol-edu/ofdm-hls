#ifndef _DATA_PATH_H_
#define _DATA_PATH_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <cmath>
#include <complex>
#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_vector.h>

#define FFT_LEN 64
#define SSR 2

#define IN_WL 22
#define IN_IL 7

#define pixl_bit 8

#define QAM_unsigned_bit 4
#define QAM_signed_bit 3

#define module_id_bit 16
#define para_id_bit 16
#define para_val_bit 32

#define QAM_normalization 10

typedef ap_fixed<IN_WL,IN_IL> ap_fixed_bit;
typedef ap_uint<32> ap_uint_32;
typedef ap_uint<64> ap_uint_64;
typedef ap_axiu<64,1,1,1> ap_axiu_64;
typedef signed int int32_t;

const ap_fixed<IN_WL,IN_IL> sqrt_FFT_LENGTH = (ap_fixed<IN_WL,IN_IL>)sqrt(FFT_LEN);
const ap_fixed<IN_WL,IN_IL> sqrt_QAM_norm = (ap_fixed<IN_WL,IN_IL>)sqrt(QAM_normalization);
const ap_fixed<IN_WL,IN_IL> sqrt_2 = (ap_fixed<IN_WL,IN_IL>)sqrt(2);

#endif
