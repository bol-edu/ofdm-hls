#!/usr/bin/bash
# bash run_composable.sh

echo "start vitis_hls project"
cd ./vitis_hls_composable_project/channel
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../CP/CP_insertion
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../CP_removal
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../../ECC/decoder
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../encoder
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../../FFT/FFT
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../IFFT
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../../pilot/pilot_insertion
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../pilot_removal
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../../QAM/QAM
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../deQAM
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../../sym_pixl/pixl2sym
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1
cd ../sym2pixl
if [ -d "./prj_impulse_test.prj/" ]
then
  make clean
fi
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1

echo "======================================================================"
echo "                           vitis_hls complete "
echo "======================================================================"

