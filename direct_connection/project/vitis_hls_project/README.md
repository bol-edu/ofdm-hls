## 。Information  
The FFT and rand function is included by the HLS library.

## 。Build Setup
This folder contains all the necessary source codes and the script for a vitis_hls project.  
The vitis_hls project could be built automatically by command `make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1` under this folder.  
There are 2 different modes, one with ECC and the other without.  
The mode could be selected in the `run_hls.tcl`.  
>#) === without ECC ===  
>add_files "src/top_module.cpp"  
>add_files "src/top_module.h"  
>add_files -tb "src/main.cpp" -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"  
>
>#) === with ECC ===  
>add_files "src/top_module_ECC.cpp"  
>add_files "src/top_module_ECC.h"  
>add_files -tb "src/main_ECC.cpp" -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"   

The IP exportation should be done in the vitis_hls GUI interface.
