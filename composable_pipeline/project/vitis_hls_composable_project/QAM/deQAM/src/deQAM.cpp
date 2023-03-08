#include "deQAM.hpp"
#define module_num 10

void deQAM(hls::stream<ap_axiu_64>& data_in, hls::stream<ap_axiu_64>& data_out)
{
#pragma HLS INTERFACE mode=ap_ctrl_none port=return
#pragma HLS INTERFACE mode = axis port = data_in
#pragma HLS INTERFACE mode = axis port = data_out

	ap_int<2> sign_r; //+1 and -1
	ap_int<2> sign_i; //+1 and -1
	ap_uint<4> i; //max=sqrt(QAM)=8
	ap_uint<4> r; //max=8
	ap_int<4> v[2]; //max=7 and -7
	ap_uint<QAM_unsigned_bit> v_out;
	ap_fixed<IN_WL,IN_IL> read_in_real;
	ap_fixed<IN_WL,IN_IL> read_in_imag;
	ap_uint_64 read_in;
	ap_axiu_64 read_out;

	int DATA_LEN;
	int qam_num;
	int sym_num;
	int pilot_width;

	ap_uint_64 para_in;
	ap_axiu_64 para_out;
	int module_id;
	int para_id;
	int para_val;
	const int threshold = pow(2,module_id_bit)-1;

	do{
		para_out = data_in.read();
		para_in = para_out.data;
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
			para_out.data = para_in;
			data_out.write(para_out);
		}

	}while( module_id != threshold);

	for(int k = 0; k < (DATA_LEN*sym_num); k++){
		read_out = data_in.read();
		read_in = read_out.data;
		read_in_real(IN_WL-1,0) = read_in.range(32+IN_WL-1, 32);
		read_in_imag(IN_WL-1,0) = read_in.range(IN_WL-1, 0);

		if (read_in_real >= 0){
			sign_r = 1;
		}
		else{
			sign_r = -1; 
			read_in_real = (read_in_real)*(-1);
		}

		v[0] = sign_r;

		for(i=2;i<sqrt(qam_num);i=i+2){
			if(read_in_real >= i){
				v[0] = v[0] + sign_r*2;
			}
			else{
				v[0] = v[0];
			}
		}
		if (read_in_imag >= 0){
			sign_i = 1;
		}
		else{
			sign_i = -1;
			read_in_imag = (read_in_imag)*(-1);
		}

		v[1] = sign_i;

		for(i=2;i<sqrt(qam_num);i=i+2){
			if(read_in_imag>=i){
				v[1] = v[1] + sign_i*2;
			}
			else{
				v[1] = v[1];
			}
		}
		v_out = 0;
		if(qam_num==16){
			for(i=0;i<2;i++){
				if(i==0){
					r = 4;
				}
				else{
					r = 1;
				}
				switch(v[i]){
				case -3:
					v_out = v_out;
					break;
				case -1:
					v_out = v_out+r*1;
					break;
				case 1:
					v_out = v_out+r*3;
					break;
				default:
					v_out = v_out+r*2;
					break;
				}
			}
		}
		else if(qam_num==4){
			for(i=0;i<2;i++){
				if(i==0){
					r = 2;
				}
				else{
					r = 1;
				}
				switch(v[i]){
				case -1:
					v_out = v_out;
					break;
				default:
					v_out = v_out+r;
					break;
				}
			}
		}
		read_out.data = v_out;
		data_out.write(read_out);
		//read_out.data = v_out;
		//data_out.write(read_out);
	}
	return;
}
