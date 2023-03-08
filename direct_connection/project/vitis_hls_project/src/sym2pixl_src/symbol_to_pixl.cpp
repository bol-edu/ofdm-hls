#include "symbol_to_pixl.h"
#define module_num 12

void symbol_to_pixl(ap_uint_64_str& data_in, ap_uint_64_str& data_out)
{

#pragma HLS INTERFACE mode = ap_ctrl_none port = return bundle = control

	ap_uint_64 data_in_temp;
	ap_uint_64 data_out_temp;
	ap_uint<QAM_unsigned_bit> out_temp_1;
	ap_uint<QAM_unsigned_bit> out_temp_2;

	int DATA_LEN;
	int qam_num;
	int sym_num;

	ap_uint_64 para_in;
	int module_id;
	int para_id;
	int para_val;
	int flag = 0;
	int flag_data = 0;
	int cnt = 0;

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
			data_in_temp = data_in.read();
			if(cnt%2==0){
				out_temp_1(QAM_unsigned_bit-1,0) = data_in_temp.range(QAM_unsigned_bit-1,0);
			}
			else{
				out_temp_2(QAM_unsigned_bit-1,0) = data_in_temp.range(QAM_unsigned_bit-1,0);
				data_out_temp = (out_temp_1, out_temp_2);
				data_out.write(data_out_temp);
			}
			cnt = cnt+1;
			if(cnt == DATA_LEN*sym_num){
				flag_data = 1;
			}
		}
	}while(!flag_data);

	return;
}
