################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
device/%.obj: ../device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --float_support=none -me -O2 --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/f2838x_cm_echoback_solution/Src" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/f2838x_cm_echoback_solution" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/libraries/communications/Ethercat/f2838x/examples/f2838x_cm_echoback_solution" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/f2838x_cm_echoback_solution/device" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/driverlib/f2838x/driverlib_cm" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/device_support/f2838x/common/include" --include_path="C:/ti/c2000/C2000Ware_3_04_00_00/libraries/communications/Ethercat/f2838x/include" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=ETHERCAT_STACK --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --embedded_constants=off --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


