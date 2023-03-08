#include "pixl_to_symbol.h"
#define module_num 0

void pixl_to_symbol(ap_uint_64_str& data_in, ap_uint_64_str& data_out)
{

#pragma HLS INTERFACE mode = ap_ctrl_none port = return bundle = control

	int DATA_LEN;
	int qam_num;
	int sym_num;
	int module_id;
	int para_id;
	int para_val;
	int flag = 0;
	int flag_data = 0;
	int cnt = 0;

	ap_uint_64 para_in;
	ap_uint_64 data_in_temp;
	ap_uint_64 data_out_temp;

	do{
		if(!flag){
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
			}
			else{
				data_out.write(para_in);
			}
			if(module_id == threshold){
				flag = 1;
			}
		}
		else{
			if((cnt%2)==0){
				data_in_temp = data_in.read();
				data_out_temp = data_in_temp/qam_num;
			}
			else{
				data_out_temp = data_in_temp%qam_num;
			}
			data_out.write(data_out_temp);
			cnt = cnt+1;
			if(cnt == DATA_LEN*sym_num){
				flag_data = 1;
			}
		}
	}while(!flag_data);

	return;
}
