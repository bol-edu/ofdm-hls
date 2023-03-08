#include "stream2master.h"
#define module_num 14

void stream_to_master(ap_uint_64_str& data_in, ap_uint_64* data_out)
{

	ap_uint_64 para_in;
	ap_uint_64 read_in;
	int module_id = 0;
	int para_id = 0;
	int para_val = 0;
	int DATA_LEN = 0;
	int cnt = 0;
	int flag = 0;
	int flag_data = 0;

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
			}
			if(module_id == threshold){
				flag = 1;
			}
		}
		else{
			read_in = data_in.read();
			data_out[cnt] = read_in;
			cnt = cnt+1;
			if(cnt==DATA_LEN){
				flag_data = 1;
			}
		}
	}while(!flag_data);

	return;
}
