#ifndef _DATA_PATH_H_
#define _DATA_PATH_H_

#include <complex>
#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <iostream>

#define FFT_LEN 64
//#define IN_WL 20
//#define IN_IL 5

#define pixl_bit 8
#define QAM_unsigned_bit 4
#define QAM_signed_bit 3
#define QAM_bit 4

#define module_id_bit 16
#define para_id_bit 16
#define para_val_bit 32

#define pixl2sym_module_num 0
#define sym2pixl_module_num 12

const int threshold = pow(2,module_id_bit)-1;

//const int pow_x_id_val = pow(2,48);
//const int pow_id_x_x = pow(2,16);
//const int pow_x_id_x = pow(2,16);
//const int pow_x_x_val = pow(2,32);

//#define QAM_normalization 10
//const ap_fixed<IN_WL,IN_IL> sqrt_QAM_norm = (ap_fixed<IN_WL,IN_IL>)sqrt(QAM_normalization);

typedef ap_uint<64> ap_uint_64;
typedef ap_axiu<64,0,0,0> ap_axiu_64;
typedef signed int int32_t;

#endif
