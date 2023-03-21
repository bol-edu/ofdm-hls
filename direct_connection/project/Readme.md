## 。Build Setup
In this section, the whole building flow would be shown.  
Three different projects under different tools should be built up during the process. 

1. Change the current direction to `direct_connection/project/vitis_hls_project/`.  
2. The mode could be selected in the `run_hls.tcl`.  
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
3. Return to the folder `direct_connection/project/`.  
4. Run `bash run_main.sh` and the whole project will build up automatically.  
5. After the vitis_hls project and vivado project done. The `design_1.bit` and `design_1.hwh` will generate under `jupyter_notebooks_project/`.  
6. Upload all files include in `jupyter_notebooks_project/`.  
7. Run the corresponding host code for the mode, cell [1] for without ecc and cell [2] for with ecc. 
**Parameter Setting**
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
8.Clicked the start button at the toolbox then the process will automatically started.  
![image](https://user-images.githubusercontent.com/102524142/218928569-404af209-e9fb-42ae-b0c9-4122dd55beb1.png)
## 。Run Test
In this section, some example results would be shown.  
#### - The original figure
![image](https://user-images.githubusercontent.com/102524142/218643587-45041ab9-763b-453e-b0fe-ca159eef95aa.png)
#### - The figuer after transmitted and decoded by the basic OFDM system, for TAP_NUM=1 SNR=10dB  
![image](https://user-images.githubusercontent.com/102524142/226565344-1c8f9bb2-1825-4ee3-987d-6e52ffd10d9f.png)
#### - The figure after transmitted and decoded by the OFDM system with error correction code, for TAP_NUM=1 SNR=10dB  
![image](https://user-images.githubusercontent.com/102524142/226565435-8b26af75-7312-42be-b29f-5c3f85bd3deb.png)
#### - SNR(dB) v.s. BER, for TAP_NUM=1  
**#without ecc**  
SNR = [0, 5, 10, 15, 20]  
BER = [0.34173791458072586, 0.2110691750104297, 0.09312565185648728, 0.015298615456821028, 0.0001600307676261994]  
**#ecc**  
SNR = [0, 5, 10, 15, 20]  
BER = [0.49950576241134755, 0.4793715451606174, 0.07988964069670422, 0.000023336462244472255, 0]  
![image](https://user-images.githubusercontent.com/102524142/218736088-4d8435b8-b11e-4932-a178-be92088837ca.png)