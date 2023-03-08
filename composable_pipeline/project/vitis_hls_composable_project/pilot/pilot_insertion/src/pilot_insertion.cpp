#include "pilot_insertion.h"

#define module_num 3

void pilot_insertion(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out)
{
#pragma HLS INTERFACE mode=ap_ctrl_none port=return
#pragma HLS INTERFACE mode=axis register_mode=both port=data_out register
#pragma HLS INTERFACE mode=axis register_mode=both port=data_in register

	ap_axiu_64 out_temp;
	ap_uint_64 out_read;
	ap_uint_32 out_real_temp = 0;
	ap_uint_32 out_imag_temp = 0;
	ap_uint_32 out_real_temp_p = 0;
	ap_uint_32 out_imag_temp_p = 0;
	ap_fixed<IN_WL, IN_IL> out_real;
	ap_fixed<IN_WL, IN_IL> out_imag;
	ap_fixed<IN_WL, IN_IL> out_real_div;
	ap_fixed<IN_WL, IN_IL> out_imag_div;

	int DATA_LEN;
	int sym_num;
	int pilot_width;
	int CP_length;

	ap_uint_64 para_in;
	ap_axiu_64 para_out;
	int module_id;
	int para_id;
	int para_val;
	const int threshold = pow(2,module_id_bit)-1;

	do{
		//para_in = data_in.read().data;
		//
		para_out = data_in.read();
		para_in = para_out.data;
		//
		module_id = para_in.range(63, para_id_bit+para_val_bit);
		if(module_id == module_num){
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
			else if(para_id == 3){
				CP_length = para_val;
			}
		}
		else{
			para_out.data = para_in;
			data_out.write(para_out);
		}
	}while( module_id != threshold);

	for (int k = 0; k < DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width)); k++){
		for (int t = 0; t < FFT_LEN; t++) {
			if((t%pilot_width)==0){
				out_real_temp_p(IN_WL-1,IN_WL-IN_IL) = pilot_real;
				out_imag_temp_p(IN_WL-1,IN_WL-IN_IL) = pilot_imag;
				out_temp.data = (out_real_temp_p, out_imag_temp_p);
				data_out.write(out_temp);
			}
			else{
				out_read = data_in.read().data;
				//------
				out_real(IN_WL-1,0) = (out_read.range(32+IN_WL-1,32));
				out_imag(IN_WL-1,0) = (out_read.range(IN_WL-1,0));
				//------
				out_real_div = out_real/sqrt_QAM_norm;
				out_imag_div = out_imag/sqrt_QAM_norm;
				out_real_temp(IN_WL-1,0) = out_real_div.range(IN_WL-1,0);///sqrt_QAM_norm
				out_imag_temp(IN_WL-1,0) = out_imag_div.range(IN_WL-1,0);///sqrt_QAM_norm
				out_temp.data = (out_real_temp, out_imag_temp);
				data_out.write(out_temp);
			}
		}
	}

	return;
}
