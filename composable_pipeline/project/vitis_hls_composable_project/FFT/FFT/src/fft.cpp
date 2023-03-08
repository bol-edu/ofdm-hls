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
void fft_top0(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out) {

#pragma HLS INTERFACE mode=axis register_mode=both port=data_out register
#pragma HLS INTERFACE mode=axis register_mode=both port=data_in register

	ap_uint_64 read_in;
	ap_axiu_64 read_out;
	ap_fixed_bit fft_in_real;
	ap_fixed_bit fft_in_imag;
	ap_fixed_bit read_ap_fixed_in;
	ap_uint_32 fft_out_real;
	ap_uint_32 fft_out_imag;
	hls::stream<T_in> p_inData[SSR];
	hls::stream<T_out0> p_outData[SSR];
	T_out0 read_Tout0_in;
	ap_fixed_bit read_Tout0_in_r;
	ap_fixed_bit read_Tout0_in_i;
#pragma HLS STREAM depth=128 variable=p_inData
#pragma HLS STREAM depth=128 variable=p_outData

	int DATA_LEN;
	int sym_num;
	int pilot_width;

	ap_uint_64 para_in;
	ap_axiu_64 para_out;
	int module_id;
	int para_id;
	int para_val;
	const int threshold = pow(2,module_id_bit)-1;

	do{
		para_in = data_in.read().data;
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
			para_out.data = para_in;
			data_out.write(para_out);
		}
	}while( module_id != threshold); 

	for(int k = 0; k < DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width)); k++){
		for (int t = 0; t < (FFT_LEN/SSR); t++) {
			for(int i = 0; i < SSR; i++){
				read_in = data_in.read().data;
				fft_in_real(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				fft_in_imag(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				p_inData[i].write(T_in(fft_in_real,fft_in_imag));
			}
		}

		xf::dsp::fft::fft<fftParams0, IID0>(p_inData, p_outData);

		for (int t = 0; t < (FFT_LEN/SSR); t++) {
			for(int i = 0; i < SSR; i++){
				read_Tout0_in = p_outData[i].read();
				read_Tout0_in_r = (ap_fixed_bit)read_Tout0_in.real()*sqrt_FFT_length;
				read_Tout0_in_i = (ap_fixed_bit)read_Tout0_in.imag()*sqrt_FFT_length;
				fft_out_real(IN_WL-1,0) = read_Tout0_in_r.range(IN_WL-1,0);
				fft_out_imag(IN_WL-1,0) = read_Tout0_in_i.range(IN_WL-1,0);
				read_out.data = (fft_out_real, fft_out_imag);
				data_out.write(read_out);
			}
		}
	}
}

//FFT
void fft_top1(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out) {
#pragma HLS INTERFACE mode=ap_ctrl_none port=return
#pragma HLS INTERFACE mode=axis register_mode=both port=data_out register
#pragma HLS INTERFACE mode=axis register_mode=both port=data_in register

	ap_uint_64 read_in;
	ap_axiu_64 read_out;
	ap_fixed_bit fft_in_real;
	ap_fixed_bit fft_in_imag;
	ap_fixed_bit read_ap_fixed_in;
	ap_uint_32 fft_out_real;
	ap_uint_32 fft_out_imag;
	hls::stream<T_in> p_inData[SSR];
	hls::stream<T_out1> p_outData[SSR];
	T_out1 read_Tout1_in;
	ap_fixed_bit read_Tout1_in_r;
	ap_fixed_bit read_Tout1_in_i;
#pragma HLS STREAM depth=128 variable=p_inData
#pragma HLS STREAM depth=128 variable=p_outData

	int DATA_LEN;
	int sym_num;
	int pilot_width;

	ap_uint_64 para_in;
	ap_axiu_64 para_out;
	int module_id;
	int para_id;
	int para_val;
	const int threshold = pow(2,module_id_bit)-1;

	do{
		para_in = data_in.read().data;
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
			para_out.data = para_in;
			data_out.write(para_out);
		}
	}while( module_id != threshold);

	for(int k = 0; k < DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width)); k++){
		for (int t = 0; t < (FFT_LEN/SSR); t++) {
			for(int i = 0; i < SSR; i++){
				read_in = data_in.read().data;
				fft_in_real(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				fft_in_imag(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				p_inData[i].write(T_in(fft_in_real,fft_in_imag));
			}
		}

		xf::dsp::fft::fft<fftParams1, IID1>(p_inData, p_outData);

		for (int t = 0; t < (FFT_LEN/SSR); t++) {
			for(int i = 0; i < SSR; i++){
				read_Tout1_in = p_outData[i].read();
				read_Tout1_in_r = (ap_fixed_bit)read_Tout1_in.real()/sqrt_FFT_length;
				read_Tout1_in_i = (ap_fixed_bit)read_Tout1_in.imag()/sqrt_FFT_length;
				fft_out_real(IN_WL-1,0) = read_Tout1_in_r.range(IN_WL-1,0);
				fft_out_imag(IN_WL-1,0) = read_Tout1_in_i.range(IN_WL-1,0);
				read_out.data = (fft_out_real, fft_out_imag);
				data_out.write(read_out);
			}
		}
	}
}
