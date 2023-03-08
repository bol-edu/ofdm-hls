/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.

 */
//================================== End Lic =================================================
#include "fft.hpp"
#define module_num_IFFT 4
#define module_num_FFT 8

//IFFT
void fft_top0(ap_uint_64_str& data_in, ap_uint_64_str& data_out) {

#pragma HLS INTERFACE mode = ap_ctrl_none port = return bundle = control

	hls::stream<T_in> p_inData[SSR];
	hls::stream<T_out0> p_outData[SSR];

#pragma HLS STREAM depth = 64 variable = p_inData
#pragma HLS STREAM depth = 64 variable = p_outData

	ap_uint_64 read_in = 0;
	ap_uint_32 fft_out_real = 0;
	ap_uint_32 fft_out_imag = 0;
	ap_fixed_bit fft_in_real;
	ap_fixed_bit fft_in_imag;
	ap_fixed_bit read_ap_fixed_in;
	ap_fixed_bit read_Tout0_in_r;
	ap_fixed_bit read_Tout0_in_i;
	ap_fixed_bit sqrt_fft_len = (ap_fixed_bit)sqrt(FFT_LEN);
	T_out0 read_Tout0_in;

	int DATA_LEN = 0;
	int sym_num = 0;
	int pilot_width = 0;

	ap_uint_64 para_in = 0;
	int module_id = 0;
	int para_id = 0;
	int para_val = 0;
	int flag = 0;
	int flag_data = 0;
	int cnt = 0;

	do{
		if(!flag){
			para_in = data_in.read();
			module_id = para_in.range(63, para_id_bit+para_val_bit);
			if(module_id == module_num_IFFT){
				para_id = para_in.range(para_id_bit+para_val_bit-1, para_val_bit);
				para_val = para_in.range(para_val_bit-1, 0);
				if(para_id == 0){
					DATA_LEN = para_val;
				}
				else if(para_id == 1){
					sym_num = para_val;
				}
				else if(para_id == 2){
					pilot_width = para_val;
				}
			}
			else{
				data_out.write(para_in);
			}
			if(module_id == threshold){
				flag = 1;
			}
		}
		else{
			if(cnt < DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width))*FFT_LEN){
				read_in = data_in.read();
				fft_in_real(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				fft_in_imag(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				p_inData[cnt%2].write(T_in(fft_in_real,fft_in_imag));
			}
			if((cnt%FFT_LEN == FFT_LEN-1)&&(cnt != DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width))*FFT_LEN+FFT_LEN-1)){
				xf::dsp::fft::fft<fftParams0, IID0>(p_inData, p_outData);
			}
			if(cnt >= FFT_LEN){
				read_Tout0_in = p_outData[cnt%2].read();
				read_Tout0_in_r = ((ap_fixed_bit)read_Tout0_in.real())*sqrt_fft_len;
				read_Tout0_in_i = ((ap_fixed_bit)read_Tout0_in.imag())*sqrt_fft_len;
				fft_out_real(IN_WL-1,0) = read_Tout0_in_r.range(IN_WL-1,0);
				fft_out_imag(IN_WL-1,0) = read_Tout0_in_i.range(IN_WL-1,0);
				data_out.write((fft_out_real, fft_out_imag));
			}
			cnt = cnt+1;
			if(cnt == DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width))*FFT_LEN+FFT_LEN){
				flag_data = 1;
			}
		}
	}while(!flag_data);

	return;
}

//FFT
void fft_top1(ap_uint_64_str& data_in, ap_uint_64_str& data_out) {
#pragma HLS INTERFACE mode = ap_ctrl_none port = return

	hls::stream<T_in> p_inData[SSR];
	hls::stream<T_out1> p_outData[SSR];

#pragma HLS STREAM depth = 64 variable = p_inData
#pragma HLS STREAM depth = 64 variable = p_outData

	ap_uint_64 read_in = 0;
	ap_uint_32 fft_out_real = 0;
	ap_uint_32 fft_out_imag = 0;
	ap_fixed_bit fft_in_real;
	ap_fixed_bit fft_in_imag;
	ap_fixed_bit read_ap_fixed_in;
	ap_fixed_bit read_Tout1_in_r;
	ap_fixed_bit read_Tout1_in_i;
	ap_fixed_bit sqrt_fft_len = (ap_fixed_bit)sqrt(FFT_LEN);;
	T_out1 read_Tout1_in;

	int DATA_LEN = 0;
	int sym_num = 0;
	int pilot_width = 0;

	ap_uint_64 para_in = 0;
	int module_id = 0;
	int para_id = 0;
	int para_val = 0;
	int flag = 0;
	int flag_data = 0;
	int cnt = 0;

	do{
		if(!flag){
			para_in = data_in.read();
			module_id = para_in.range(63, para_id_bit+para_val_bit);
			if(module_id == module_num_FFT){
				para_id = para_in.range(para_id_bit+para_val_bit-1, para_val_bit);
				para_val = para_in.range(para_val_bit-1, 0);
				if(para_id == 0){
					DATA_LEN = para_val;
				}
				else if(para_id == 1){
					sym_num = para_val;
				}
				else if(para_id == 2){
					pilot_width = para_val;
				}
			}
			else{
				data_out.write(para_in);
			}
			if(module_id == threshold){
				flag = 1;
			}
		}
		else{
			if(cnt < DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width))*FFT_LEN){
				read_in = data_in.read();
				fft_in_real(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				fft_in_imag(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				p_inData[cnt%2].write(T_in(fft_in_real,fft_in_imag));
			}
			if((cnt%FFT_LEN == FFT_LEN-1)&&(cnt != DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width))*FFT_LEN+FFT_LEN-1)){
				xf::dsp::fft::fft<fftParams1, IID1>(p_inData, p_outData);
			}
			if(cnt >= FFT_LEN){
				read_Tout1_in = p_outData[cnt%2].read();
				read_Tout1_in_r = ((ap_fixed_bit)read_Tout1_in.real())/sqrt_fft_len;
				read_Tout1_in_i = ((ap_fixed_bit)read_Tout1_in.imag())/sqrt_fft_len;
				fft_out_real(IN_WL-1,0) = read_Tout1_in_r.range(IN_WL-1,0);
				fft_out_imag(IN_WL-1,0) = read_Tout1_in_i.range(IN_WL-1,0);
				data_out.write((fft_out_real, fft_out_imag));
			}
			cnt = cnt+1;
			if(cnt == DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width))*FFT_LEN+FFT_LEN){
				flag_data = 1;
			}
		}
	}while(!flag_data);

	return;
}
