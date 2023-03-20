#!/usr/bin/bash
# bash run_composable.sh

cd ./vitis_hls_project
make clean
echo "start vitis_hls project"
make run CSIM=1 CSYNTH=1 COSIM=1 EXPORT_IP=1

echo "======================================================================"
echo "                           vitis_hls complete "
echo "======================================================================"

