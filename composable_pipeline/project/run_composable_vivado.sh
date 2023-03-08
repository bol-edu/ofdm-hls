#!/usr/bin/bash
# bash run_composable.sh


if [ -d "./composable_communcation/" ]
then
 rm -r ./composable_communcation/
 echo "start vivado project"
fi

if [ -d "./commun.hwh" ]
then
 rm ./commun.hwh
fi

if [ -d "./commun.bit" ]
then
 rm ./commun.bit
fi
#------RTL_QAM----#
cd vitis_hls_composable_project/QAM_RTL_tcl/
bash run_cp.sh
cd ../../
#------------------#

vivado -source composable_communcation.tcl -mode tcl

cp ./composable_communcation/composable_communcation.gen/sources_1/bd/commun/hw_handoff/commun.hwh jupyter_notebooks_project/commun.hwh
cp ./composable_communcation/composable_communcation.runs/impl_1/commun_wrapper.bit ./jupyter_notebooks_project/commun.bit

echo "======================================================================"
echo "                           vivado complete "
echo "======================================================================"

