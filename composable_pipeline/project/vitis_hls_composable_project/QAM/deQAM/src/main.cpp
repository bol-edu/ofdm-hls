#include "QAM.hpp"
#include "deQAM.hpp"
#include "data_path.hpp"

using namespace std;

int main(int argc, char *argv[]){

	ap_int_32 QAM_r;
	ap_int_32 QAM_i;
	hls::stream<ap_axiu_64> QAM_in;
	hls::stream<ap_axiu_64> QAM_temp;
	hls::stream<ap_axiu_64> QAM_out;
	ap_axiu_64 para_in;
	ap_axiu_64 para_temp;
	ap_uint<16> module_id;
	ap_uint<16> para_id;
	ap_uint<32> para_val;

	int DATA_LEN =  30;
	int qam_num =  16;
	int sym_num =  2;
	int pilot_width =  4;
	int CP_length = 16;

	module_id = QAM_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);
	para_id = 1;
	para_val = qam_num;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);
	para_id = 2;
	para_val = sym_num;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);
	para_id = 3;
	para_val = pilot_width;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);

	module_id = deQAM_module_num;
	para_id = 0;
	para_val = DATA_LEN;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);
	para_id = 1;
	para_val = qam_num;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);
	para_id = 2;
	para_val = sym_num;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);
	para_id = 3;
	para_val = pilot_width;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in);

	module_id = pow(2,16)-1;
	para_id = 0;
	para_val = 0;
	para_in.data = (module_id, para_id, para_val);
	QAM_in.write(para_in); //stop

	cout << ">> Start test!" << endl;
	for(int k = 0; k < (DATA_LEN*sym_num); k++){
		para_temp.data = (ap_uint_64)(k%16);
		QAM_in.write(para_temp);
	}
	QAM(QAM_in, QAM_temp);
	cout << "QAM_finished" << endl;
	deQAM(QAM_temp, QAM_out);
	for(int k = 0; k < (DATA_LEN*sym_num); k++){
		std::cout << k << "  " << (QAM_out.read().data) << endl;
	}
	std::cout << "  " << (QAM_out.read().data) << endl;
	cout << ">> Test Finished!" << endl;
	return 0;
}
