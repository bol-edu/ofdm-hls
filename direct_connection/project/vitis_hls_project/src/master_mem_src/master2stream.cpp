#include "master2stream.h"
#define module_num 13

void master_to_stream(ap_uint_64* data_in, ap_uint_64_str& data_out)
{

	ap_uint_64 para_in;
	ap_uint_64 read_in;
	int module_id = 0;
	int para_id = 0;
	int para_val = 0;
	int total_input_num = 0;
	int cnt = 0;
	int flag = 0;
	int flag_data = 0;


	do{
		if(!flag){
			para_in = data_in[cnt];
			module_id = para_in.range(63, para_id_bit+para_val_bit);
			if(module_id == module_num){
				para_id = para_in.range(para_id_bit+para_val_bit-1, para_val_bit);
				para_val = para_in.range(para_val_bit-1, 0);
				if(para_id == 0){
					total_input_num = para_val;
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
			data_out.write(data_in[cnt]);
			if(cnt == (total_input_num-1)){
				flag_data = 1;
			}
		}
		cnt = cnt+1;
	}while(!flag_data);

  return;
}
