#include "channel_gen.h"
#define module_num 6

void channel_gen(ap_uint_64_str& data_in, ap_uint_64_str& data_out)
{

#pragma HLS INTERFACE mode=ap_ctrl_none port=return

	ap_uint_64 read_in = 0;
	ap_uint_64 read_out = 0;
	ap_uint_32 data_temp_r = 0;
	ap_uint_32 data_temp_i = 0;
	ap_fixed<IN_WL,IN_IL> random_temp_r = 0.0;
	ap_fixed<IN_WL,IN_IL> random_temp_i = 0.0;
	int index_count = 0;
	ap_uint_32 i;
	ap_fixed<IN_WL,IN_IL> x_out_r = 0.0;
	ap_fixed<IN_WL,IN_IL> x_out_i = 0.0;
	ap_fixed<IN_WL,IN_IL> x_real_1taps = 0.0;
	ap_fixed<IN_WL,IN_IL> x_imag_1taps = 0.0;
	ap_fixed<IN_WL,IN_IL> n_1taps = 0;
	ap_fixed<IN_WL,IN_IL> x_real_2taps[2] = {0.0};
	ap_fixed<IN_WL,IN_IL> x_imag_2taps[2] = {0.0};
	ap_fixed<IN_WL,IN_IL> n_2taps[2];
	ap_fixed<IN_WL,IN_IL> weight_2taps[2] = {0.85, 0.5267};
	ap_fixed<IN_WL,IN_IL> x_real_3taps[3] = {0.0};
	ap_fixed<IN_WL,IN_IL> x_imag_3taps[3] = {0.0};
	ap_fixed<IN_WL,IN_IL> n_3taps[3];
	ap_fixed<IN_WL,IN_IL> weight_3taps[3] = {0.8, 0.5, 0.3317};
	ap_fixed<IN_WL,IN_IL> x_real_6taps[6] = {0.0};
	ap_fixed<IN_WL,IN_IL> x_imag_6taps[6] = {0.0};
	ap_fixed<IN_WL,IN_IL> n_6taps[6];
	ap_fixed<IN_WL,IN_IL> weight_6taps[6] = {0.7943, 0.3981, 0.3162, 0.2512, 0.1778, 0.1259};
	ap_fixed<IN_WL,IN_IL> x_real_9taps[9] = {0.0};
	ap_fixed<IN_WL,IN_IL> x_imag_9taps[9] = {0.0};
	ap_fixed<IN_WL,IN_IL> n_9taps[9];
	ap_fixed<IN_WL,IN_IL> weight_9taps[9] = {0.5, 0.31, 0.19, 0.06, 0.03, 0.02, 0.008, 0.004, 0.002};
	ap_fixed<IN_WL,IN_IL> random_num_value_real = 0.0;
	ap_fixed<IN_WL,IN_IL> random_num_value_imag = 0.0;
	hls::stream<ap_fixed<IN_WL,IN_IL>> random_num;

	int DATA_LEN;
	int sym_num;
	int pilot_width;
	int CP_length;
	int TAPS_NUM;
	int SNR;

	ap_uint_64 para_in;
	int module_id;
	int para_id;
	int para_val;
	const int threshold = pow(2,module_id_bit)-1;

	do{
		para_in = data_in.read();
		module_id = para_in.range(63, para_id_bit+para_val_bit);
		if(module_id == module_num){
			para_id = para_in.range(para_id_bit+para_val_bit-1, para_val_bit);
			para_val = para_in.range(para_val_bit-1, 0);
			if(para_id == 0){
				DATA_LEN = para_val;
			}
			else if(para_id == 1){
				sym_num = para_val;
			}
			else if(para_id == 2){
				pilot_width = para_val;
			}
			else if(para_id == 3){
				CP_length = para_val;
			}
			else if(para_id == 4){
				TAPS_NUM = para_val;
			}
			else if(para_id == 5){
				SNR = para_val;
			}
		}
		else{
			data_out.write(para_in);
		}
	}while( module_id != threshold);

	const ap_fixed<IN_WL,IN_IL> sqrt_No = (ap_fixed<IN_WL,IN_IL>)(1/sqrt(pow(10.0,SNR/10.0)));

	for(int k = 0; k < DATA_LEN*sym_num/(FFT_LEN-(FFT_LEN/pilot_width)); k++){
		for(int j = 0; j < FFT_LEN+CP_length; j++){
			rand(random_num);
			random_num_value_real = random_num.read()*sqrt_No/sqrt_2;
			rand(random_num);
			random_num_value_imag = random_num.read()*sqrt_No/sqrt_2;
			if(TAPS_NUM==1){
				read_in = data_in.read();
				x_real_1taps(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				x_imag_1taps(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				random_temp_r = x_real_1taps+random_num_value_real;
				random_temp_i = x_imag_1taps+random_num_value_imag;
				data_temp_r(IN_WL-1,0) = random_temp_r(IN_WL-1,0);
				data_temp_i(IN_WL-1,0) = random_temp_i(IN_WL-1,0);
				read_out = (data_temp_r, data_temp_i);
				data_out.write(read_out);
			}
			else if(TAPS_NUM==2){
				for (i = TAPS_NUM-1 ;i > 0; i--){
					x_real_2taps[i] = x_real_2taps[i-1];
					x_imag_2taps[i] = x_imag_2taps[i-1];
				}
				read_in = data_in.read();
				x_real_2taps[0].range(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				x_imag_2taps[0].range(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				if(j==0){
					for(i = 0; i < TAPS_NUM; i++){
						rand(random_num);
						n_2taps[i] = random_num.read();
					}
				}
				x_out_r = 0;
				x_out_i = 0;
				for(i = 0; i < TAPS_NUM; i++){
					x_out_r = x_out_r + (ap_fixed<IN_WL,IN_IL>)(weight_2taps[i]*n_2taps[i])*x_real_2taps[i];
					x_out_i = x_out_i + (ap_fixed<IN_WL,IN_IL>)(weight_2taps[i]*n_2taps[i])*x_imag_2taps[i];
				}
				random_temp_r = x_out_r+random_num_value_real;
				random_temp_i = x_out_i+random_num_value_imag;
				data_temp_r(IN_WL-1,0) = random_temp_r(IN_WL-1,0);
				data_temp_i(IN_WL-1,0) = random_temp_i(IN_WL-1,0);
				read_out = (data_temp_r, data_temp_i);
				data_out.write(read_out);
			}
			else if(TAPS_NUM==3){
				for (i = TAPS_NUM-1 ;i > 0; i--){
					x_real_3taps[i] = x_real_3taps[i-1];
					x_imag_3taps[i] = x_imag_3taps[i-1];
				}
				read_in = data_in.read();
				x_real_3taps[0].range(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				x_imag_3taps[0].range(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				if(j==0){
					for(i = 0; i < TAPS_NUM; i++){
						rand(random_num);
						n_3taps[i] = random_num.read();
					}
				}
				x_out_r = 0;
				x_out_i = 0;
				for(i = 0; i < TAPS_NUM; i++){
					x_out_r = x_out_r + (ap_fixed<IN_WL,IN_IL>)(weight_3taps[i]*n_3taps[i])*x_real_3taps[i];
					x_out_i = x_out_i + (ap_fixed<IN_WL,IN_IL>)(weight_3taps[i]*n_3taps[i])*x_imag_3taps[i];
				}
				random_temp_r = x_out_r+random_num_value_real;
				random_temp_i = x_out_i+random_num_value_imag;
				data_temp_r(IN_WL-1,0) = random_temp_r(IN_WL-1,0);
				data_temp_i(IN_WL-1,0) = random_temp_i(IN_WL-1,0);
				read_out = (data_temp_r, data_temp_i);
				data_out.write(read_out);
			}
			else if(TAPS_NUM==6){
				for (i = TAPS_NUM-1 ;i > 0; i--){
					x_real_6taps[i] = x_real_6taps[i-1];
					x_imag_6taps[i] = x_imag_6taps[i-1];
				}
				read_in = data_in.read();
				x_real_6taps[0].range(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				x_imag_6taps[0].range(IN_WL-1,0) = read_in.range(IN_WL-1,0);

				if(j==0){
					for(i = 0; i < TAPS_NUM; i++){
						rand(random_num);
						n_6taps[i] = random_num.read();
					}
				}
				x_out_r = 0;
				x_out_i = 0;
				for(i = 0; i < TAPS_NUM; i++){
					x_out_r = x_out_r + (ap_fixed<IN_WL,IN_IL>)(weight_6taps[i]*n_6taps[i])*x_real_6taps[i];
					x_out_i = x_out_i + (ap_fixed<IN_WL,IN_IL>)(weight_6taps[i]*n_6taps[i])*x_imag_6taps[i];
				}
				random_temp_r = x_out_r+random_num_value_real;
				random_temp_i = x_out_i+random_num_value_imag;
				data_temp_r(IN_WL-1,0) = random_temp_r(IN_WL-1,0);
				data_temp_i(IN_WL-1,0) = random_temp_i(IN_WL-1,0);
				read_out = (data_temp_r, data_temp_i);
				data_out.write(read_out);
			}

			//else{
			else if(TAPS_NUM==9){
				for (i = TAPS_NUM-1 ;i > 0; i--){
					x_real_9taps[i] = x_real_9taps[i-1];
					x_imag_9taps[i] = x_imag_9taps[i-1];
				}
				read_in = data_in.read();
				x_real_9taps[0].range(IN_WL-1,0) = read_in.range(32+IN_WL-1,32);
				x_imag_9taps[0].range(IN_WL-1,0) = read_in.range(IN_WL-1,0);
				if(j==0){
					for(i = 0; i < TAPS_NUM; i++){
						rand(random_num);
						n_9taps[i] = random_num.read();
					}
				}
				x_out_r = 0;
				x_out_i = 0;
				for(i = 0; i < TAPS_NUM; i++){
					x_out_r = x_out_r + (ap_fixed<IN_WL,IN_IL>)(weight_9taps[i]+n_9taps[i])*x_real_9taps[i];
					x_out_i = x_out_i + (ap_fixed<IN_WL,IN_IL>)(weight_9taps[i]+n_9taps[i])*x_imag_9taps[i];
				}
				random_temp_r = x_out_r+random_num_value_real;
				random_temp_i = x_out_i+random_num_value_imag;
				data_temp_r(IN_WL-1,0) = random_temp_r(IN_WL-1,0);
				data_temp_i(IN_WL-1,0) = random_temp_i(IN_WL-1,0);
				read_out = (data_temp_r, data_temp_i);
				data_out.write(read_out);
			}
		}
	}

	return;
}