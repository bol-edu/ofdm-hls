## 。Built Steps  
1. Change the direction to `cd project/`.  
2. Run `bash run_composable_main.sh` and the whole project will build up automatically.  
3. After the the vitis_hls project and vivado project done.  
4. The `commun.bit` and `commun.hwh` will generate under `jupyter_notebooks_project/`.  
5. Upload all files include in `jupyter_notebooks_project/`.  
6. For without ecc case, run the cells [1]->[2]->[3].  
7. For with ecc case, run the cells [4]->[5]->[6].  
8. Run cell [7] for the comparison of the two cases under TAP_NUM=1 and SNR = [0, 5, 10, 15, 20].  
