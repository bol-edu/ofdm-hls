#include "CP_removal.h"
#define module_num 7

void CP_removal(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out)
{

#pragma HLS INTERFACE mode=ap_ctrl_none port=return
#pragma HLS INTERFACE mode=axis register_mode=both port=data_out register
#pragma HLS INTERFACE mode=axis register_mode=both port=data_in register

	ap_uint_64 read_in;
	ap_axiu_64 read_out;
	ap_uint_32 out_temp_r;
	ap_uint_32 out_temp_i;
	int DATA_LEN;
	int qam_num;
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
		para_in = data_in.read().data;
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
 
	for(int k = 0; k<DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width));k++){
		for(int t = 0; t < FFT_LEN+CP_length; t++){
			if(t < CP_length){
				read_in = data_in.read().data;
			}
			else{
				data_out.write(data_in.read());
			}
		}
	}

	return;
}