#include "encoder.h"
#define module_num 1

void encoder(ap_uint_64_str& data_in, ap_uint_64_str& data_out)
{

#pragma HLS INTERFACE mode=ap_ctrl_none port=return

	ap_uint_64 data_out_temp = 0;
	ap_uint_64 data_in_axiu = 0;
	ap_uint_64 data_in_temp = 0;
	int DATA_LEN;
	int qam_num;
	int sym_num;
	int pilot_width;
	ap_uint_64 para_in_axiu = 0;
	ap_uint_64 para_in = 0;
	int module_id;
	int para_id;
	int para_val;

	do{
		para_in = data_in.read();
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
			data_out.write(para_in);
		}
	}while( module_id != threshold);
	//------------------------------------------------//
	static ap_uint<6> s = 0;
	ap_uint<pixl_bit> out = 0;
	for(int i = 0; i < DATA_LEN*sym_num*2; i++){
		if(i<DATA_LEN*sym_num*2){
			if((i%2)==0){
				data_in_temp = data_in.read();
			}
		}else{
			data_in_temp = 0;
		}
		for(int j=0 ; j<2 ; j++){
			out[j*2] = data_in_temp[(i%2)*2+j]^s[1]^s[2]^s[4]^s[5];
			out[j*2+1] = data_in_temp[(i%2)*2+j]^s[0]^s[1]^s[2]^s[5];
			s =  s << 1;
			s[0] = data_in_temp[(i%2)*2+j];
		}
		data_in_axiu = (ap_uint_64)out;
		data_out.write(data_in_axiu);
	}
 
	return;
}
