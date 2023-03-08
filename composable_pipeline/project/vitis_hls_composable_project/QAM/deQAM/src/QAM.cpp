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

#include "QAM.hpp"
#define module_num 2

void QAM(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out){
#pragma HLS INTERFACE mode = axis port = data_in
#pragma HLS INTERFACE mode = axis port = data_out

	ap_uint_64 in_temp;
	ap_axiu_64 out_temp;
	ap_fixed<IN_WL,IN_IL> out_temp_real;
	ap_fixed<IN_WL,IN_IL> out_temp_imag;

	int DATA_LEN;
	int qam_num;
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
		if(module_id == module_num){
			para_id = para_in.range(para_id_bit+para_val_bit-1, para_val_bit);
			para_val = para_in.range(para_val_bit-1, 0);
			if(para_id == 0){
				DATA_LEN = para_val;
			}
			else if(para_id == 1){
				qam_num = para_val;
			}
			else if(para_id == 2){
				sym_num = para_val;
			}
			else if(para_id == 3){
				pilot_width = para_val;
			}
		}
		else{
			para_out.data = para_in;
			data_out.write(para_out);
		}
	}while( module_id != threshold);


	for(int k = 0; k < (DATA_LEN*sym_num); k++){
		in_temp = data_in.read().data;
		if(qam_num == 16){
			if((in_temp%4)==0){
				out_temp_imag = -3;
			}
			else if((in_temp%4)==1){
				out_temp_imag = -1;
			}
			else if((in_temp%4)==2){
				out_temp_imag = 3;
			}
			else{
				out_temp_imag = 1;
			}
			if((in_temp/4)==0){
				out_temp_real = -3;
			}
			else if((in_temp/4)==1){
				out_temp_real = -1;
			}
			else if((in_temp/4)==2){
				out_temp_real = 3;
			}
			else{
				out_temp_real = 1;
			}
		}
		else if(qam_num == 4){
			if((in_temp%2)==0){
				out_temp_imag = -1;
			}
			else{
				out_temp_imag = 1;
			}
			if((in_temp/2)==0){
				out_temp_real = -1;
			}
			else{
				out_temp_real = 1;
			}
		}

		out_temp.data.range(32+IN_WL-1,32) = out_temp_real.range(IN_WL-1,0);
		out_temp.data.range(IN_WL-1,0) = out_temp_imag.range(IN_WL-1,0);
		data_out.write(out_temp);
	}

	return;
}
