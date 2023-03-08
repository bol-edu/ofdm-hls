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
#define TW_WL 16
#define TW_IL 3

#define pilot_real 1
#define pilot_imag 0
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

const ap_fixed_bit sqrt_QAM_norm = (ap_fixed<IN_WL,IN_IL>)sqrt(QAM_normalization);
const ap_fixed_bit sqrt_FFT_length = (ap_fixed<IN_WL,IN_IL>)sqrt(FFT_LEN);
#include "fixed/vt_fft.hpp"
using namespace xf::dsp::fft;

//typedef signed int int32_t;
typedef std::complex<ap_fixed<IN_WL,IN_IL>> T_in;

// Define parameter structure for FFT
//-------------------------------- IFFT ----------------------------------
#define IID0 0
struct fftParams0 : ssr_fft_default_params {
    static const int N = FFT_LEN;
    static const int R = SSR;
    static const fft_output_order_enum output_data_order = SSR_FFT_NATURAL; 
    static const transform_direction_enum transform_direction = REVERSE_TRANSFORM; //IFFT
    static const scaling_mode_enum scaling_mode = SSR_FFT_GROW_TO_MAX_WIDTH;
    static const int twiddle_table_word_length = TW_WL;
    static const int twiddle_table_intger_part_length = TW_IL;
};
typedef ssr_fft_output_type<fftParams0,T_in>::t_ssr_fft_out T_out0;
//------------------------------ IFFT end --------------------------------

//--------------------------------- FFT ----------------------------------
#define IID1 1
struct fftParams1 : ssr_fft_default_params {
    static const int N = FFT_LEN;
    static const int R = SSR;
    static const fft_output_order_enum output_data_order = SSR_FFT_NATURAL;
    static const transform_direction_enum transform_direction = FORWARD_TRANSFORM; //FFT
    static const scaling_mode_enum scaling_mode = SSR_FFT_GROW_TO_MAX_WIDTH;
    static const int twiddle_table_word_length = TW_WL;
    static const int twiddle_table_intger_part_length = TW_IL;
};
typedef ssr_fft_output_type<fftParams1,T_in>::t_ssr_fft_out T_out1;
//------------------------------- FFT end --------------------------------



#endif
