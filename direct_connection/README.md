## 。Introduction
This project is about the implementation of OFDM with multipath channel by HLS through direct connection.  
#### - System Architecture
**1. The Basic Block Diagram of HLS OFDM System**
![image](https://user-images.githubusercontent.com/102524142/218687408-c8a98b2e-8c77-40b5-a763-649ebd71a188.png)
**2. The Block Diagram with ECC of HLS OFDM System**
![image](https://user-images.githubusercontent.com/102524142/218687462-f4d4fbfd-b3d1-400e-84f1-d97df15432d2.png)

## 。Folder Structure
In this section, the function of all folders in this project will be explained.
#### - project
The whole project can be built by the command `bash run_main.sh` under this folder.  
1. **vitis_hls_project**  
In this folder, all source codes can be found in the folder `project/vitis_hls_project/src/`.  
After the command `bash run_vitis.sh` processed, the project `prj_umpulse_test.prj` will be built automatically under the folder `project/vitis_hls_project/`.  
2. **vivado_project**  
This folder contains a vivado project script file `project/vivado_project.tcl`.  
The vivado project could be automatically built under the folder by the command `bash run_vivado.sh`.  
3. **jupyter_notebooks_project**  
There are host codes and example files of .hwh and .bit files.  
And after generating the vivado bitstream, the .hwh and .bit files of the design will automatically copy to this folder.
The examples files mentioned above could directly process by the host code, or you could replaced by your own design.
#### - impl_result
The result reports of vitis_hls_project will be included in this folder.

## 。Build Setup
In this section, the whole building flow would be shown.  
By process the command `bash run_main.sh` under the folder `direct_connection/project/`, the vitis_hls and vivado project would be built automatically by the script.  
After all the processes done, then the target files `design1.bit` and `design1.hwh` will be copied to the folder `direct_connection/project/jupyter_notebooks_project/`.

Three different projects under different tools should be built up during the process.  
#### - Vitis_hls
1. **Resources**  
Change the current direction to `direct_connection/project/vitis_hls_project/`.  
All the source code files could be found in the folder `direct_connection/project/vitis_hls_project/src/`.  
2. **Project Setting Adjustment**  
There exists 2 modes for testing, one with error correction code and another is the basic one.  
Both modes have their own top_module.cpp, top_module.h and main.cpp.  
The setting could be modified in `direct_connection/project/vitis_hls_project/run_hls.tcl`.  
Just leave the part you need, and the corresponding files would be added automatically after the command implemented.  
> **#=== without ECC ===**  
>add_files "src/top_module.cpp"  
>add_files "src/top_module.h"  
>add_files -tb "src/main.cpp" -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"  
> **#=== with ECC ===**  
>add_files "src/top_module_ECC.cpp"  
>add_files "src/top_module_ECC.h"  
>add_files -tb "src/main_ECC.cpp" -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"  
3. **Simulations and Synthesis and Export IP**  
The steps CSIM, CSYNTH, COSIM and EXPORT_IP can directly implement by the command `bash run_vitis.sh` under the folder `direct_connection/project/vitis_hls_project/`.  
After that the project `prj_impulse_test.prj` would be built under the folder `direct_connection/project/vitis_hls_project/`.  
4. **Results**  
After all, the symbol error rate and the bit error rate could be checked.  
![image](https://user-images.githubusercontent.com/102524142/218661346-5eee9d67-79e7-410b-8258-9509217fa900.png)  

#### - Vivado
1. **Resources**  
Make sure your current direction is still in `direct_connection/project/vitis_hls_project/`.  
2. **Open the Vivado Project**  
The project could be built by the following command `bash run_vivado.sh`, And the bitstream would be generated automatically.

#### - Jupyter Notebooks
1. **Resources Downloading**  
Check the `.bit` and `.hwh` files are already in the folder `direct_connection/project/jupyter_notebooks_project/`. 
2. **Upload Necessary Files**  
Upload the .bit and .hwh files and rename those files should into the same name.  
Upload an arbitrary picture for testing.  
3. **Parameter Setting**
The parameters can be modified into different combinations for different situations.  
![image](https://user-images.githubusercontent.com/102524142/218928701-1fd3440d-c4c9-43bc-b805-7011c23c6131.png)  
>1. qam_num = 16 : The modulation type. (The system only supports 16QAM.)  
>2. sym_num = 2 : Since the length of a single pixel is 8, a single data can be turned into 8/(the length of a data be modulated) symbols.  
>3. pilot_width = 4 : The interval of two pilots. The smaller the value is, the result of the channel equalization would be more accurate.  
>(The system now supports the pilot length not bigger than 16)  
>4. CP_length = 16 : The length of the CP. 
>5. TAPS_NUM = 1 : (The system now can support the multipath channel with 1, 2, 3, 6 and 9 taps.)  
>6. SNR = [20] : The dB value of signal to noise ratio.  
>7. FFT_len = 64 : The size of the FFT should be modified directly in the data_path.hpp in the vitis_hls_project.  
>(The IP should be exported once again after modified the FFT_len) 
4. **Run the Process**  
Clicked the start button at the toolbox then the process will automatically started.  
![image](https://user-images.githubusercontent.com/102524142/218928569-404af209-e9fb-42ae-b0c9-4122dd55beb1.png)
## 。Run Test
In this section, some example results would be shown.  
#### - The original figure
![image](https://user-images.githubusercontent.com/102524142/218643587-45041ab9-763b-453e-b0fe-ca159eef95aa.png)
#### - The figuer after transmitted and decoded by the basic OFDM system, for TAP_NUM=1 SNR=10dB  
![image](https://user-images.githubusercontent.com/102524142/218643624-4938cba4-970a-45c3-b3a1-f99af5b0e384.png)
#### - The figure after transmitted and decoded by the OFDM system with error correction code, for TAP_NUM=1 SNR=10dB  
![image](https://user-images.githubusercontent.com/102524142/218643748-2ff0995e-0b8d-4a35-aeee-0a4ba823acf7.png)
#### - SNR(dB) v.s. BER, for TAP_NUM=1  
**#without ecc**  
SNR = [0, 5, 10, 15, 20]  
BER = [0.34173791458072586, 0.2110691750104297, 0.09312565185648728, 0.015298615456821028, 0.0001600307676261994]  
**#ecc**  
SNR = [0, 5, 10, 15, 20]  
BER = [0.49950576241134755, 0.4793715451606174, 0.07988964069670422, 0.000023336462244472255, 0]  
![image](https://user-images.githubusercontent.com/102524142/218736088-4d8435b8-b11e-4932-a178-be92088837ca.png)
