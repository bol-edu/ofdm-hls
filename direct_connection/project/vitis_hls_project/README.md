## 。Information  
The FFT and rand function is included by the HLS library.

## 。Built Steps  
1. Change the direction to `cd project/`.  
2. The mode could be selected in the `run_hls.tcl`.  
>#) === without ECC ===  
>add_files "src/top_module.cpp"  
>add_files "src/top_module.h"  
>add_files -tb "src/main.cpp" -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"  
>
>#) === with ECC ===  
>add_files "src/top_module_ECC.cpp"  
>add_files "src/top_module_ECC.h"  
>add_files -tb "src/main_ECC.cpp" -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"   
4. Run `bash run_main.sh` and the whole project will build up automatically.  
5. After the the vitis_hls project and vivado project done.  
6. The `design_1.bit` and `design_1.hwh` will generate under `jupyter_notebooks_project/`.  
7. Upload all files include in `jupyter_notebooks_project/`.  
8. Run the corresponding host code for the mode.   
9. Run cell [7] for the comparison of the two cases under TAP_NUM=1 and SNR = [0, 5, 10, 15, 20]. 
