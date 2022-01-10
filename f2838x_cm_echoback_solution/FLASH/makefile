################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := G:/ti/ccs1100/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./ethercat_slave_cm_hal.obj" \
"./startup_cm.obj" \
"./Src/NEWECAT Slave.obj" \
"./Src/coeappl.obj" \
"./Src/ecatappl.obj" \
"./Src/ecatcoe.obj" \
"./Src/ecatslv.obj" \
"./Src/f2838x_cm_hw.obj" \
"./Src/f2838x_cm_system.obj" \
"./Src/mailbox.obj" \
"./Src/objdef.obj" \
"./Src/sdoserv.obj" \
"./device/cm.obj" \
"../2838x_FLASH_lnk_ecat_cm.cmd" \
"G:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib_cm/ccs/Debug/driverlib_cm.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Src/subdir_vars.mk
-include device/subdir_vars.mk
-include subdir_rules.mk
-include Src/subdir_rules.mk
-include device/subdir_rules.mk
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
f2838x_cm_echoback_solution.out \

EXE_OUTPUTS__QUOTED += \
"f2838x_cm_echoback_solution.out" \

BIN_OUTPUTS += \
f2838x_cm_echoback_solution.hex \

BIN_OUTPUTS__QUOTED += \
"f2838x_cm_echoback_solution.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "f2838x_cm_echoback_solution.out"

# Tool invocations
f2838x_cm_echoback_solution.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"G:/ti/ccs1100/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --float_support=none -me -O2 --define=ETHERCAT_STACK --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --verbose_diagnostics --gen_func_subsections=on --embedded_constants=off -z -m"f2838x_cm_echoback_solution.map" --heap_size=0x200 --stack_size=0x200 -i"G:/ti/ccs1100/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/lib" -i"G:/ti/ccs1100/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --reread_libs --define=_FLASH --diag_wrap=off --display_error_number --warn_sections --xml_link_info="f2838x_cm_echoback_solution_linkInfo.xml" --rom_model -o "f2838x_cm_echoback_solution.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

f2838x_cm_echoback_solution.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"G:/ti/ccs1100/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armhex" --diag_wrap=off -o "f2838x_cm_echoback_solution.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "ethercat_slave_cm_hal.obj" "startup_cm.obj" "Src\NEWECAT Slave.obj" "Src\coeappl.obj" "Src\ecatappl.obj" "Src\ecatcoe.obj" "Src\ecatslv.obj" "Src\f2838x_cm_hw.obj" "Src\f2838x_cm_system.obj" "Src\mailbox.obj" "Src\objdef.obj" "Src\sdoserv.obj" "device\cm.obj" 
	-$(RM) "ethercat_slave_cm_hal.d" "startup_cm.d" "Src\NEWECAT Slave.d" "Src\coeappl.d" "Src\ecatappl.d" "Src\ecatcoe.d" "Src\ecatslv.d" "Src\f2838x_cm_hw.d" "Src\f2838x_cm_system.d" "Src\mailbox.d" "Src\objdef.d" "Src\sdoserv.d" "device\cm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

