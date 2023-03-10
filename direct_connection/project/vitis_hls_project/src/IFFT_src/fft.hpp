/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.

*/
//================================== End Lic =================================================
#ifndef __FFT_H__
#define __FFT_H__
#include "../data_path.hpp"

void fft_top0(ap_uint_64_str& data_in, ap_uint_64_str& data_out); //IFFT
void fft_top1(ap_uint_64_str& data_in, ap_uint_64_str& data_out); //FFT

#endif
