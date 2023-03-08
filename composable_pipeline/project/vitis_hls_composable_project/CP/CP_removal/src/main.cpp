#include "CP_insertion.h"
#include "CP_removal.h"
#include "data_path.hpp"

#define CP_insertion_module_num 5
#define CP_removal_module_num 7

using namespace std;

int main(int argc, char *argv[])
{
	ap_axiu_64 in_temp;
	ap_uint_64 out_temp;

	ap_fixed_bit in_r;
	ap_fixed_bit in_i;
	ap_uint_32 in_r_temp = 0;
	ap_uint_32 in_i_temp = 0;
	ap_fixed_bit out_r_temp = 0;
	ap_fixed_bit out_i_temp = 0;

	hls::stream<ap_axiu_64> data_in;
	hls::stream<ap_axiu_64> data_temp;
	hls::stream<ap_axiu_64> data_out;
	ap_axiu_64 para_in;
	ap_axiu_64 para_temp;
	ap_uint<16> module_id;
	ap_uint<16> para_id;
	ap_uint<32> para_val;
	int sym_num = 2;
	int DATA_LEN = 96;
	int pilot_width = 4;
	int CP_length = 16;
	const int threshold = pow(2,module_id_bit)-1;

	module_id = CP_insertion_module_num;
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

	module_id = CP_removal_module_num;
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
	cout << "CP Insertion" << endl;
	cout << "------------------------" << endl;
	for (int k = 0; k < DATA_LEN*sym_num*FFT_LEN/(FFT_LEN-(FFT_LEN/pilot_width)); k++){
		in_r = rand()/(RAND_MAX+1.0);
		in_i = rand()/(RAND_MAX+1.0);
		//cout << "in_r = " << (float)in_r << "    \t" << "in_i = " << (float)in_i << endl;
		in_r_temp(IN_WL-1,0) = in_r.range(IN_WL-1,0);
		in_i_temp(IN_WL-1,0) = in_i.range(IN_WL-1,0);
		cout << k << " : in_r = " << (int)in_r_temp << " in_i = " << (int)in_i_temp << endl;
		in_temp.data = (in_r_temp, in_i_temp);
		data_in.write(in_temp);
	}
	cout << "in finished" << endl;
	CP_insertion(data_in, data_temp);
	CP_removal(data_temp, data_out);
	cout << "out finished" << endl;

	do{
		out_temp = data_out.read().data;
	}while( module_id != threshold);
	cout << "------------------------" << endl;
	for (int k = 0; k < DATA_LEN*sym_num*(FFT_LEN)/(FFT_LEN-(FFT_LEN/pilot_width)); k++){
		out_temp = data_out.read().data;
		out_r_temp(IN_WL-1,0) = out_temp(32+IN_WL-1,32);
		out_i_temp(IN_WL-1,0) = out_temp(IN_WL-1,0);
		cout << k << " : out_r = " << (int)out_temp(32+IN_WL-1,32)<< " out_i = " << (int)out_temp(IN_WL-1,0) << endl;
		//cout << "r = " << (float)out_r_temp << "    \t" << "i = " << (float)out_i_temp << endl;
	}

	cout << ">> Finish test!" << endl;
	return 0;
}
