#include "QAM.hpp"
#define module_num 2

void QAM(ap_uint_64_str& data_in, ap_uint_64_str& data_out){

#pragma HLS INTERFACE mode = ap_ctrl_none port = return bundle = control

	ap_uint_64 read_in;
	ap_uint_64 read_out;
	ap_fixed<IN_WL,IN_IL> out_temp_real;
	ap_fixed<IN_WL,IN_IL> out_temp_imag;

	int DATA_LEN;
	int qam_num;
	int sym_num;
	int pilot_width;

	ap_uint_64 para_in;
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


	for(int k = 0; k < (DATA_LEN*sym_num); k++){
		read_in = data_in.read();
		if(qam_num == 16){
			if((read_in%4)==0){
				out_temp_imag = -3;
			}
			else if((read_in%4)==1){
				out_temp_imag = -1;
			}
			else if((read_in%4)==2){
				out_temp_imag = 3;
			}
			else{
				out_temp_imag = 1;
			}
			if((read_in/4)==0){
				out_temp_real = -3;
			}
			else if((read_in/4)==1){
				out_temp_real = -1;
			}
			else if((read_in/4)==2){
				out_temp_real = 3;
			}
			else{
				out_temp_real = 1;
			}
		}
		else if(qam_num == 4){
			if((read_in%2)==0){
				out_temp_imag = -1;
			}
			else{
				out_temp_imag = 1;
			}
			if((read_in/2)==0){
				out_temp_real = -1;
			}
			else{
				out_temp_real = 1;
			}
		}

		read_out.range(32+IN_WL-1,32) = out_temp_real.range(IN_WL-1,0);
		read_out.range(IN_WL-1,0) = out_temp_imag.range(IN_WL-1,0);
		data_out.write(read_out);
	}

	return;
}
