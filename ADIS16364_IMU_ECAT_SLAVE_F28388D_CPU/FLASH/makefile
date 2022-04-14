################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./f2838x_codestartbranch.obj" \
"./CLA/CLA_init.obj" \
"./CLA/spi.obj" \
"./EtherCAT_slave/ADIS16364_F28388D_IMU_SLAVE_CPU1.obj" \
"./EtherCAT_slave/coeappl.obj" \
"./EtherCAT_slave/ecatappl.obj" \
"./EtherCAT_slave/ecatcoe.obj" \
"./EtherCAT_slave/ecatslv.obj" \
"./EtherCAT_slave/f2838x_cpu1_hw.obj" \
"./EtherCAT_slave/f2838x_cpu1_system.obj" \
"./EtherCAT_slave/mailbox.obj" \
"./EtherCAT_slave/objdef.obj" \
"./EtherCAT_slave/sdoserv.obj" \
"./SPI_ADIS16364_LIBRARY/SPI_init.obj" \
"./ethercat_f28388x_hal/device.obj" \
"./ethercat_f28388x_hal/ethercat_gpio_setup.obj" \
"./ethercat_f28388x_hal/ethercat_slave_cpu1_hal.obj" \
"../2838x_FLASH_lnk_ecat_cpu1.cmd" \
"C:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib/ccs/Debug/driverlib.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include CLA/subdir_vars.mk
-include EtherCAT_slave/subdir_vars.mk
-include SPI_ADIS16364_LIBRARY/subdir_vars.mk
-include ethercat_f28388x_hal/subdir_vars.mk
-include subdir_rules.mk
-include CLA/subdir_rules.mk
-include EtherCAT_slave/subdir_rules.mk
-include SPI_ADIS16364_LIBRARY/subdir_rules.mk
-include ethercat_f28388x_hal/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.out \

EXE_OUTPUTS__QUOTED += \
"ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.out" \

BIN_OUTPUTS += \
ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.hex \

BIN_OUTPUTS__QUOTED += \
"ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.out"

# Tool invocations
ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 -O2 --advice:performance=all --define=__TI_EABI__ --define=ETHERCAT_STACK --define=_FLASH --define=CPU1 --diag_suppress=10063 --diag_suppress=770 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.map" --heap_size=0x200 --stack_size=0x200 --warn_sections -i"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/lib" -i"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --reread_libs --define=_FLASH --define=__TI_EABI__ --diag_wrap=off --display_error_number --xml_link_info="ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU_linkInfo.xml" --entry_point=code_start --rom_model -o "ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/hex2000" --diag_wrap=off -o "ADIS16364_IMU_ECAT_SLAVE_F28388D_CPU.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "f2838x_codestartbranch.obj" "CLA\CLA_init.obj" "CLA\spi.obj" "EtherCAT_slave\ADIS16364_F28388D_IMU_SLAVE_CPU1.obj" "EtherCAT_slave\coeappl.obj" "EtherCAT_slave\ecatappl.obj" "EtherCAT_slave\ecatcoe.obj" "EtherCAT_slave\ecatslv.obj" "EtherCAT_slave\f2838x_cpu1_hw.obj" "EtherCAT_slave\f2838x_cpu1_system.obj" "EtherCAT_slave\mailbox.obj" "EtherCAT_slave\objdef.obj" "EtherCAT_slave\sdoserv.obj" "SPI_ADIS16364_LIBRARY\SPI_init.obj" "ethercat_f28388x_hal\device.obj" "ethercat_f28388x_hal\ethercat_gpio_setup.obj" "ethercat_f28388x_hal\ethercat_slave_cpu1_hal.obj" 
	-$(RM) "CLA\CLA_init.d" "EtherCAT_slave\ADIS16364_F28388D_IMU_SLAVE_CPU1.d" "EtherCAT_slave\coeappl.d" "EtherCAT_slave\ecatappl.d" "EtherCAT_slave\ecatcoe.d" "EtherCAT_slave\ecatslv.d" "EtherCAT_slave\f2838x_cpu1_hw.d" "EtherCAT_slave\f2838x_cpu1_system.d" "EtherCAT_slave\mailbox.d" "EtherCAT_slave\objdef.d" "EtherCAT_slave\sdoserv.d" "SPI_ADIS16364_LIBRARY\SPI_init.d" "ethercat_f28388x_hal\device.d" "ethercat_f28388x_hal\ethercat_gpio_setup.d" "ethercat_f28388x_hal\ethercat_slave_cpu1_hal.d" 
	-$(RM) "CLA\spi.d" 
	-$(RM) "f2838x_codestartbranch.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

