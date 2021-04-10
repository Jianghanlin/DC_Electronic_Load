################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./system_msp432p401r.obj" \
"./ccs/startup_msp432p401r_ccs.obj" \
"./src/24cxx.obj" \
"./src/ADS1118.obj" \
"./src/GUI.obj" \
"./src/ST7796S.obj" \
"./src/USCI_B0_SPI.obj" \
"./src/dac8571.obj" \
"./src/delay.obj" \
"./src/device_init.obj" \
"./src/key.obj" \
"./src/myiic.obj" \
"./src/system_init.obj" \
"./src/test.obj" \
"./src/touch.obj" \
"./src/vector.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-l"ti/display/lib/display.aem4f" \
-l"ti/grlib/lib/ccs/m4f/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4f/spiffs.a" \
-l"ti/drivers/lib/drivers_msp432p401x.aem4f" \
-l"third_party/fatfs/lib/ccs/m4f/fatfs.a" \
-l"ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include ccs/subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include ccs/subdir_rules.mk
-include src/subdir_rules.mk
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
TFT_SPI_display_with_touch.out \

EXE_OUTPUTS__QUOTED += \
"TFT_SPI_display_with_touch.out" \

BIN_OUTPUTS += \
TFT_SPI_display_with_touch.hex \

BIN_OUTPUTS__QUOTED += \
"TFT_SPI_display_with_touch.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "TFT_SPI_display_with_touch.out"

# Tool invocations
TFT_SPI_display_with_touch.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=5 --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --c99 --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"TFT_SPI_display_with_touch.map" --stack_size=512 -i"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" -i"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="TFT_SPI_display_with_touch_linkInfo.xml" --rom_model -o "TFT_SPI_display_with_touch.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

TFT_SPI_display_with_touch.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armhex"  -o "TFT_SPI_display_with_touch.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "system_msp432p401r.obj" "ccs\startup_msp432p401r_ccs.obj" "src\24cxx.obj" "src\ADS1118.obj" "src\GUI.obj" "src\ST7796S.obj" "src\USCI_B0_SPI.obj" "src\dac8571.obj" "src\delay.obj" "src\device_init.obj" "src\key.obj" "src\myiic.obj" "src\system_init.obj" "src\test.obj" "src\touch.obj" "src\vector.obj" 
	-$(RM) "main.d" "system_msp432p401r.d" "ccs\startup_msp432p401r_ccs.d" "src\24cxx.d" "src\ADS1118.d" "src\GUI.d" "src\ST7796S.d" "src\USCI_B0_SPI.d" "src\dac8571.d" "src\delay.d" "src\device_init.d" "src\key.d" "src\myiic.d" "src\system_init.d" "src\test.d" "src\touch.d" "src\vector.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

