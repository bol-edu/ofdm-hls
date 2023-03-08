#include "top_module_ECC.h"

void top_module(ap_uint_64* data_in, ap_uint_64* data_out)
{
#pragma HLS INTERFACE mode = m_axi depth = 150 port = data_in bundle = gmem0
#pragma HLS INTERFACE mode = m_axi depth = 96 port = data_out bundle = gmem0
#pragma HLS INTERFACE mode = s_axilite port = data_in bundle = control
#pragma HLS INTERFACE mode = s_axilite port = data_out bundle = control
#pragma HLS INTERFACE mode = s_axilite port = return bundle = control
#pragma HLS DATAFLOW

	ap_uint_64_str master2stream_out;
	ap_uint_64_str pixl2symbol_out;
	ap_uint_64_str encoder_out;
	ap_uint_64_str QAM_out;
	ap_uint_64_str pilot_insertion_out;
	ap_uint_64_str IFFT_out;
	ap_uint_64_str cp_insertion_out;
	ap_uint_64_str channel_out;
	ap_uint_64_str cp_removal_out;
	ap_uint_64_str FFT_out;
	ap_uint_64_str equalizer_pilot_removal_out;
	ap_uint_64_str deQAM_out;
	ap_uint_64_str symbol2pixl_out;
	ap_uint_64_str decoder_out;

	master_to_stream(data_in, master2stream_out);
	pixl_to_symbol(master2stream_out, pixl2symbol_out);
	encoder(pixl2symbol_out, encoder_out);
	QAM(encoder_out, QAM_out);
	pilot_insertion(QAM_out, pilot_insertion_out);
	fft_top0(pilot_insertion_out, IFFT_out);
	CP_insertion(IFFT_out, cp_insertion_out);
	channel_gen(cp_insertion_out, channel_out);
	CP_removal(channel_out, cp_removal_out);
	fft_top1(cp_removal_out, FFT_out);
	equalizer_pilot_removal(FFT_out, equalizer_pilot_removal_out);
	deQAM(equalizer_pilot_removal_out, deQAM_out);
	decoder(deQAM_out, decoder_out);
	symbol_to_pixl(decoder_out, symbol2pixl_out);
	stream_to_master(symbol2pixl_out, data_out);

	return;
}
