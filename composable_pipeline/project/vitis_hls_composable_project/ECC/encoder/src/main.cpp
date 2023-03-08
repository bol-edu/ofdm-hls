#include <iostream>
#include "encoder.h"
#include "decoder.h"
#include "data_path.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	hls::stream<ap_axiu_64> data_in;
	hls::stream<ap_axiu_64> data_temp;
	hls::stream<ap_axiu_64> data_out;

	ap_axiu_64 para_in;
	ap_axiu_64 data_read_in;
	ap_uint_64 para_read_out;

	ap_uint<module_id_bit> module_id;
	ap_uint<para_id_bit> para_id;
	ap_uint<para_val_bit> para_val;

	int DATA_LEN = 480;
	int qam_num =  16;
	int sym_num =  2;
	int pilot_width =  4;

	module_id = encoder_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 1;
	para_val = qam_num;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 2;
	para_val = sym_num;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 3;
	para_val = pilot_width;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);

	module_id = decoder_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 1;
	para_val = qam_num;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 2;
	para_val = sym_num;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 3;
	para_val = pilot_width;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);

	module_id = pow(2,16)-1;
	para_id = 0;
	para_val = 0;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in); //stop

	cout << ">> Start test!" << endl;
	cout << "------------------------" << endl;
	for(int i = 0; i < DATA_LEN*2; i++) {
		data_read_in.data = (ap_uint_64)i%16;
		data_in.write(data_read_in);
	}

	encoder(data_in, data_temp);
	decoder(data_temp, data_out);
	do{
		para_read_out = data_out.read().data;
		module_id = para_read_out(63,para_id_bit+para_val_bit);
	}while(module_id != threshold);
	for(int i = 0; i < DATA_LEN*2-4; i++) {
		cout << i << " : " << (int)data_out.read().data << endl;
	}
	cout << "------------------------" << endl;

	return 0;
}
