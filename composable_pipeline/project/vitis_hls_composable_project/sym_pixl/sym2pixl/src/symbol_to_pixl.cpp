#include "symbol_to_pixl.h"
#define module_num 12

void symbol_to_pixl(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out)
{
#pragma HLS INTERFACE mode=ap_ctrl_none port=return
#pragma HLS INTERFACE mode=axis register_mode=both port=data_out register
#pragma HLS INTERFACE mode=axis register_mode=both port=data_in register

	ap_uint<QAM_unsigned_bit> out_temp_1;
	ap_uint<QAM_unsigned_bit> out_temp_2;
	ap_axiu_64 data_in_axiu;
	ap_axiu_64 data_out_temp;
	ap_axiu_64 para_out_temp;

	int DATA_LEN;
	int qam_num;
	int sym_num;
	int pilot_width;

	ap_axiu_64 para_in_axiu;
	ap_uint_64 para_in;
	int module_id;
	int para_id;
	int para_val;

	do{
		para_in_axiu = data_in.read();
		para_in = para_in_axiu.data;
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
			para_in_axiu.data = para_in;
			data_out.write(para_in_axiu);
		}
	}while( module_id != threshold);

	for(int i = 0; i<DATA_LEN*sym_num; i++){
		data_in_axiu = data_in.read();
		if(i==(DATA_LEN*sym_num-1))
			data_in_axiu.last = 1;
		else
			data_in_axiu.last = 0;
		if(i%2==0){
			out_temp_1(QAM_unsigned_bit-1,0) = data_in_axiu.data.range(QAM_unsigned_bit-1,0);
		}
		else{
			out_temp_2(QAM_unsigned_bit-1,0) = data_in_axiu.data.range(QAM_unsigned_bit-1,0);
			data_in_axiu.data = (out_temp_1, out_temp_2);
			data_out.write(data_in_axiu);
		}
	}

	return;
}
