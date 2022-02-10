################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := G:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./asin.obj" \
"./cla_ex1_asin.obj" \
"./f2838x_globalvariabledefs.obj" \
"./setvalue.obj" \
"./device/device.obj" \
"./device/f2838x_codestartbranch.obj" \
"../2838x_RAM_CLA_lnk_cpu1.cmd" \
"C:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2838x/driverlib/ccs/Debug/driverlib.lib" \
"../f2838x_headers_nonBIOS_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include device/subdir_vars.mk
-include subdir_rules.mk
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
cla_ex1_asin.out \

EXE_OUTPUTS__QUOTED += \
"cla_ex1_asin.out" \

BIN_OUTPUTS += \
cla_ex1_asin.hex \

BIN_OUTPUTS__QUOTED += \
"cla_ex1_asin.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "cla_ex1_asin.out"

# Tool invocations
cla_ex1_asin.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"G:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O2 --opt_for_speed=2 --advice:performance=all --define=_DUAL_HEADERS --define=RAM --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --cla_background_task=off --cla_signed_compare_workaround=on -z -m"cla_ex1_asin.map" --heap_size=0x200 --stack_size=0x3F8 --warn_sections -i"G:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/lib" -i"G:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="cla_ex1_asin_linkInfo.xml" --entry_point=code_start --rom_model -o "cla_ex1_asin.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

cla_ex1_asin.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"G:/ti/ccs1110/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/hex2000" --diag_wrap=off -o "cla_ex1_asin.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "asin.obj" "cla_ex1_asin.obj" "f2838x_globalvariabledefs.obj" "setvalue.obj" "device\device.obj" "device\f2838x_codestartbranch.obj" 
	-$(RM) "cla_ex1_asin.d" "f2838x_globalvariabledefs.d" "setvalue.d" "device\device.d" 
	-$(RM) "asin.d" 
	-$(RM) "device\f2838x_codestartbranch.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-if 0 == 1  mkdir "G:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/simulation"
	-if 0 == 1  C:/TDM-GCC-64/bin/g++  -c -DCLB_SIM -IC:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc-2.3.3/src -IC:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/include/type3 -IG:/ti-workspace_v11_22/cla_ex1_asin -IC:/TDM-GCC-64/bin/include -Og -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MFG:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/simulation/clb_sim.d -MTG:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/simulation/clb_sim.o -IG:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/syscfg   -fno-threadsafe-statics  -oG:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/simulation/clb_sim.o G:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/syscfg/clb_sim.cpp
	-if 0 == 1  C:/TDM-GCC-64/bin/g++ -DCLB_SIM -Og -g -gdwarf-3 -gstrict-dwarf -Wall -Wl,-Map,G:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/simulation/simulation_output.map -LC:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc-2.3.3/build/src -oG:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/simulation/simulation_output.exe G:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/simulation/clb_sim.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_FSM_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_HLC_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_LUT4_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_OutputLUT_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_counter_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_counter_top_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_FSM_top_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_LUT4_top_SC_model.o C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/systemc/src/type3/CLB_OutputLUT_top_SC_model.o  -Wl,--start-group -lsystemc -Wl,--end-group
	-if 0 == 1  "./simulation/simulation_output.exe"
	-if 0 == 1  G:/ti/ccs1110/ccs/tools/node/node.exe "C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/dot_file_libraries/clbDotUtility.js"  "C:/ti/c2000/C2000Ware_4_00_00_00/utilities/clb_tool/clb_syscfg/" "G:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/syscfg" "G:/ti-workspace_v11_22/cla_ex1_asin/CPU1_RAM/syscfg/clb.dot"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

