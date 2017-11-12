@echo off
set xv_path=F:\\Xilinx\\Vivado\\2017.1\\bin
call %xv_path%/xsim test_des_behav -key {Behavioral:sim_1:Functional:test_des} -tclbatch test_des.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
