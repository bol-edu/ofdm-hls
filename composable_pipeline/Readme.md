The block diagram of the system can be shown as follow
![image](https://user-images.githubusercontent.com/102524142/215822546-b3cc1d43-0e37-4f88-8b64-234bfb326c5b.png)

Every IP should be exported individually.
More detailed information could be found in the design document and workbook on the home page.

## 。Built Steps  
1. Change the direction to `cd project/`.  
2. Run `bash run_composable_main.sh` and the whole project will build up automatically.  
3. After the the vitis_hls project and vivado project done.  
4. The `commun.bit` and `commun.hwh` will generate under `jupyter_notebooks_project/`.  
5. Upload all files include in `jupyter_notebooks_project/`.  
6. For without ecc case, run the cells [1]->[2]->[3] in jupyter notebook.  
7. For with ecc case, run the cells [4]->[5]->[6] in jupyter notebook.  
8. Run cell [7] for the comparison of the two cases under TAP_NUM=1 and SNR = [0, 5, 10, 15, 20].  

## 。Folder Structure
In this section, the function of all folders in this project would be explained.
#### - jupyer_notebook_project
In this folder, all host code could be found, include:
###### - commun_path.json
###### - composable_pipeline.ipynb
After you use the command `bash run_composable_main.sh` to build porject, two files will be added to the file:
###### - commun.bit
###### - commun.hwh
When you want to use FPGA verification, put the files in this file into jupyer notebook.  

#### - vitis_hls_composable_project
In this folder, all vitis hls source code could be found.  
All source code can be used by `OFDM_HLS_Implementation/src_composable/project/run_composable_vitis.sh` tcl file to generate each vitis project.  
This tcl file is called by `run_composable_main.sh` in `project/` folder. 



- Be aware of the consistency of the vivado version and board. 
The version of vivado we are using is "2021.1",and use board "kv260".
![image](https://user-images.githubusercontent.com/102540321/218909422-b9c85355-c4ff-429c-96e6-6094b1cf5fb1.png)


