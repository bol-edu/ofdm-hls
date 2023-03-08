#!/usr/bin/bash
# bash run_composable.sh


if [ -d "./QAM_RTL_IP/" ]
then
 rm -r ./QAM_RTL_IP/
 echo "start vivado project"
fi

rm *.log
rm *.jou

vivado -source QAM_RTL_IP.tcl -mode tcl

#cp ./composable_communcation/composable_communcation.gen/sources_1/bd/commun/hw_handoff/commun.hwh commun.hwh
#cp ./composable_communcation/composable_communcation.runs/impl_1/commun_wrapper.bit commun.bit

echo "======================================================================"
echo "                           vivado complete "
echo "======================================================================"

