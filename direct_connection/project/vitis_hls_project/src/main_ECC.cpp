#include <iostream>
#include "top_module.h"
#include "data_path.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	int module_total_num = 15;
	int para_cnt[module_total_num] = {3, 4, 4, 4, 3, 4, 6, 4, 3, 5, 4, 4, 3, 1, 1};
	int DATA_LEN =  48;
	int qam_num =  16;
	int sym_num =  2;
	int pilot_width =  4;
	int CP_length = 16;
	int TAPS_NUM = 3;
	int SNR = 20;
	int total_input_num = DATA_LEN+1;
	int cnt = 0;

	for(int i = 0; i < module_total_num; i++){
		total_input_num = total_input_num+para_cnt[i];
	}
	cout << "total_input_num : " << total_input_num << endl;

	ap_uint_64 data_in[total_input_num];
	ap_uint_64 data_out[DATA_LEN];

	ap_uint_64 para_in;
	ap_uint_64 data_read_in;
	ap_uint_64 para_read_out;

	ap_uint<module_id_bit> module_id;
	ap_uint<para_id_bit> para_id;
	ap_uint<para_val_bit> para_val;

	module_id = pixl2sym_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = qam_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = encoder_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = qam_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = QAM_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = qam_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = pilot_insertion_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = CP_length;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = IFFT_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = CP_insertion_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = CP_length;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = channel_gen_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = CP_length;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 4;
	para_val = TAPS_NUM;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 5;
	para_val = SNR;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = CP_removal_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = CP_length;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = FFT_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = pilot_removal_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = CP_length;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 4;
	para_val = TAPS_NUM;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = deQAM_module_num;
	para_id = 0;
	para_val = DATA_LEN*2;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = qam_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = decoder_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = qam_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 3;
	para_val = pilot_width;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = sym2pixl_module_num;
	para_id = 0;
	para_val = DATA_LEN-4;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 1;
	para_val = qam_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;
	para_id = 2;
	para_val = sym_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = master2stream_module_num;
	para_id = 0;
	para_val = total_input_num;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = stream2master_module_num;
	para_id = 0;
	para_val = DATA_LEN-4;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in;
	cnt++;

	module_id = pow(2,16)-1;
	para_id = 0;
	para_val = 0;
	para_in = (module_id, para_id, para_val);
	data_in[cnt] = para_in; //stop
	cnt++;

	cout << ">> Start test!" << endl;
	cout << "------------------------" << endl;
	for(int i = cnt; i < total_input_num; i++) {
		if(i<total_input_num-4){
			data_read_in = (ap_uint_64)(i-cnt);
			data_in[i] = data_read_in;
		}
		else{
			data_in[i] = 0;
		}
	}

	top_module(data_in, data_out);

	int err = 0;
	int err_SER = 0;
 
	for(int i = 0; i < DATA_LEN-4; i++) {
		std::cout << data_in[i+total_input_num-DATA_LEN] << " : " << data_out[i] << "\n";
		if(data_out[i]!=data_in[i+total_input_num-DATA_LEN]){
			err_SER = err_SER+1;
		}
		for(int j = 0; j<pixl_bit; j++){
			if(data_out[i].range(j,j) != data_in[i+total_input_num-DATA_LEN].range(j,j)){
				err = err+1;
			}
		}
	}
	std::cout << "error_SER : " << (float)err_SER/(DATA_LEN-4) << endl;
	std::cout << "error_BER : " << (float)err/((DATA_LEN-4)*pixl_bit) << endl;
	cout << "------------------------" << endl;

	return 0;
}
