#ifndef _DATA_PATH_H_
#define _DATA_PATH_H_

#include <iostream>
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include <math.h>

#define FFT_LEN 64
#define SSR 2
#define IN_WL 22
#define IN_IL 7
#define TW_WL 16
#define TW_IL 3

#define pixl_bit 8
#define QAM_unsigned_bit 4
#define QAM_signed_bit 3
#define QAM_bit 4
#define pilot_real 1
#define pilot_imag 0

#define module_id_bit 16
#define para_id_bit 16
#define para_val_bit 32

#define pixl2sym_module_num 0
#define encoder_module_num 1
#define QAM_module_num 2
#define pilot_insertion_module_num 3
#define IFFT_module_num 4
#define CP_insertion_module_num 5
#define channel_gen_module_num 6
#define CP_removal_module_num 7
#define FFT_module_num 8
#define pilot_removal_module_num 9
#define deQAM_module_num 10
#define decoder_module_num 11
#define sym2pixl_module_num 12
#define master2stream_module_num 13
#define stream2master_module_num 14

const int threshold = 65535;//pow(2,module_id_bit)-1;

typedef ap_int<32> ap_int_32;
typedef ap_uint<32> ap_uint_32;
typedef ap_uint<64> ap_uint_64;
typedef hls::stream<ap_uint_64> ap_uint_64_str;
typedef ap_fixed<IN_WL,IN_IL> ap_fixed_bit;
typedef signed int int32_t;

#define QAM_normalization 10
const ap_fixed_bit sqrt_QAM_norm = sqrt(QAM_normalization);
const ap_fixed_bit sqrt_2 = sqrt(2);

#include "IFFT_src/fixed/vt_fft.hpp"
using namespace xf::dsp::fft;
typedef std::complex<ap_fixed_bit> T_in;

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
