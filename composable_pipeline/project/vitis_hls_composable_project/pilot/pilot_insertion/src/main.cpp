#include "pilot_insertion.h"
#include "equalizer_pilot_removal.h"
#include "data_path.hpp"
#define pilot_insertion_module_num 3
#define pilot_removal_module_num 9

using namespace std;

int main(int argc, char *argv[])
{
	ap_axiu_64 in_temp;
	ap_uint_64 out_temp;

	ap_fixed_bit in_r;
	ap_fixed_bit in_i;
	ap_uint_32 in_r_temp = 0;
	ap_uint_32 in_i_temp = 0;
	ap_uint_32 out_r_temp = 0;
	ap_uint_32 out_i_temp = 0;

	hls::stream<ap_axiu_64> data_in;
	hls::stream<ap_axiu_64> data_temp;
	hls::stream<ap_axiu_64> data_out;
	ap_axiu_64 para_in;
	ap_axiu_64 para_temp;
	ap_uint<16> module_id;
	ap_uint<16> para_id;
	ap_uint<32> para_val;
	int DATA_LEN = 48;
	int sym_num = 2;
	int pilot_width = 4;
	int CP_length = 16;

	cout << ">> Start test!" << endl;

	module_id = pilot_insertion_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 1;
	para_val = sym_num;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 2;
	para_val = pilot_width;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 3;
	para_val = CP_length;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);

	module_id = pilot_removal_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 1;
	para_val = sym_num;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 2;
	para_val = pilot_width;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 3;
	para_val = CP_length;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);

	module_id = pow(2,16)-1;
	para_id = 0;
	para_val = 0;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in); //stop

	srand(time(NULL));

	cout << ">> Start test!" << endl;
	cout << ">> Pilot Insertion" << endl;
	cout << "------------------------" << endl;
	for (int k = 0; k < DATA_LEN*sym_num; k++){
		in_r = rand()/(RAND_MAX+1.0);
		in_i = rand()/(RAND_MAX+1.0);
		in_r_temp(IN_WL-1,0) = in_r.range(IN_WL-1,0);
		in_i_temp(IN_WL-1,0) = in_i.range(IN_WL-1,0);
		cout << "r = " << (int)in_r_temp << "    \t" << "i = " << (int)in_i_temp << endl;
		in_temp.data = (in_r_temp, in_i_temp);
		data_in.write(in_temp);
	}
	cout << "------------------------" << endl;
	cout << endl;	

	pilot_insertion(data_in, data_temp);
	equalizer_pilot_removal(data_temp, data_out);

	cout << ">> Output Check" << endl;
	cout << "------------------------" << endl;
	for (int k = 0; k < DATA_LEN*sym_num; k++){
		out_temp = data_out.read().data;
		out_r_temp(19,0) = out_temp(51,32);
		out_i_temp(19,0) = out_temp(19,0);
		cout << "k : " << k << "r = " << (int)out_r_temp << "    \t" << "i = " << (int)out_i_temp << endl;
	}
	cout << "------------------------" << endl;

	return 0;
}
