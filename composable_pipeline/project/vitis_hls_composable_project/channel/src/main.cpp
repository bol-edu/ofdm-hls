#include "channel_gen.h"
#include "data_path.hpp"
#define channel_module_num 6

using namespace std;

int main(int argc, char *argv[])
{
	ap_axiu_64 data_temp;
	hls::stream<ap_axiu_64> data_in;
	hls::stream<ap_axiu_64> data_out;

	ap_uint<32> real_temp;
	ap_uint<32> imag_temp;
	ap_fixed_bit real_temp_fixed;
	ap_fixed_bit imag_temp_fixed;

	ap_axiu_64 para_in;
	ap_axiu_64 para_temp;
	ap_uint<16> module_id;
	ap_uint<16> para_id;
	ap_uint<32> para_val;
	ap_uint<64> out_temp;

	int DATA_LEN = 48;
	int sym_num = 2;
	int pilot_width = 4;
	int CP_length = 16;
	int TAPS_NUM = 1;
	int SNR = 30;
	const int threshold = pow(2,module_id_bit)-1;

	cout << ">> Start test!" << endl;

	module_id = channel_module_num;
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
	para_id = 4;
	para_val = TAPS_NUM;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);
	para_id = 5;
	para_val = SNR;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in);

	module_id = pow(2,module_id_bit)-1;
	para_id = 0;
	para_val = 0;
	para_in.data = (module_id, para_id, para_val);
	data_in.write(para_in); //stop
	srand(time(NULL));

	cout << ">> Start test!" << endl;
	cout << "------------------------" << endl;

	for(int t = 0; t < (FFT_LEN+CP_length)*DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width)); t++) {
		real_temp = t*pow(2,IN_WL-IN_IL);
		imag_temp = t*pow(2,IN_WL-IN_IL);
		data_temp.data = 0;
		//cout << "in => real : " << real_temp/pow(2,IN_WL-IN_IL) << " real : " << imag_temp/pow(2,IN_WL-IN_IL) << endl;
		data_in.write(data_temp);
	}

    channel_gen(data_in, data_out);
    cout << endl;
   	cout << "------------------------" << endl;
   	cout << endl;

   	do{
		out_temp = data_out.read().data;
	}while( module_id != threshold);
	for(int t = 0; t < (FFT_LEN+CP_length)*DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width)); t++) {
		out_temp = data_out.read().data;
		real_temp_fixed(IN_WL-1,0) = out_temp.range(32+IN_WL-1, 32);
		imag_temp_fixed(IN_WL-1,0) = out_temp.range(IN_WL-1, 0);
		cout << "out => real : " << real_temp_fixed << " imag : " << imag_temp_fixed << endl;
	}
	cout << "------------------------" << endl;

	return 0;
}
