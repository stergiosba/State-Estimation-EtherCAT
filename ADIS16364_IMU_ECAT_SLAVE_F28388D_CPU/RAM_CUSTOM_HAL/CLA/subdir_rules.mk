################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CLA/%.obj: ../CLA/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 -Ooff --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/CLA" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/ethercat_f28388x_hal" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/SPI_ADIS16364_LIBRARY" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/EtherCAT_slave" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/libraries/communications/Ethercat/f2838x/examples/f2838x_cpu1_echoback_solution" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/device" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/device_support/f2838x/common/include" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --advice:performance=all --define=ETHERCAT_STACK --define=RAM --define=CPU1 --diag_suppress=10063 --diag_suppress=770 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="CLA/$(basename $(<F)).d_raw" --obj_directory="CLA" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CLA/%.obj: ../CLA/%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 -Ooff --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/CLA" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/ethercat_f28388x_hal" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/SPI_ADIS16364_LIBRARY" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/EtherCAT_slave" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/libraries/communications/Ethercat/f2838x/examples/f2838x_cpu1_echoback_solution" --include_path="C:/Users/Lupus/Desktop/NEW_ECAT/Pegasus/ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU/device" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib" --include_path="C:/ti/c2000/C2000Ware_4_00_00_00/device_support/f2838x/common/include" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --advice:performance=all --define=ETHERCAT_STACK --define=RAM --define=CPU1 --diag_suppress=10063 --diag_suppress=770 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="CLA/$(basename $(<F)).d_raw" --obj_directory="CLA" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


