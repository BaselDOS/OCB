# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\projects\final\a_final_system\_ide\scripts\systemdebugger_a_final_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\projects\final\a_final_system\_ide\scripts\systemdebugger_a_final_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT1 210203AF5594A" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT1-210203AF5594A-43651093-0"}
fpga -file D:/projects/final/a_final/_ide/bitstream/download.bit
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
loadhw -hw D:/projects/final/final_platform/export/final_platform/hw/final_platform.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow D:/projects/final/a_final/Debug/a_final.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
