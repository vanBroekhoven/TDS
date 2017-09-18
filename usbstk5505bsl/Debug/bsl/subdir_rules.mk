################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
bsl/usbstk5505.obj: ../bsl/usbstk5505.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 -g --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --diag_warning=225 --large_memory_model --asm_source=mnemonic --preproc_with_compile --preproc_dependency="bsl/usbstk5505.d" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5505_gpio.obj: ../bsl/usbstk5505_gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 -g --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --diag_warning=225 --large_memory_model --asm_source=mnemonic --preproc_with_compile --preproc_dependency="bsl/usbstk5505_gpio.d" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5505_i2c.obj: ../bsl/usbstk5505_i2c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 -g --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --diag_warning=225 --large_memory_model --asm_source=mnemonic --preproc_with_compile --preproc_dependency="bsl/usbstk5505_i2c.d" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5505_i2s.obj: ../bsl/usbstk5505_i2s.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 -g --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --diag_warning=225 --large_memory_model --asm_source=mnemonic --preproc_with_compile --preproc_dependency="bsl/usbstk5505_i2s.d" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5505_led.obj: ../bsl/usbstk5505_led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 -g --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --diag_warning=225 --large_memory_model --asm_source=mnemonic --preproc_with_compile --preproc_dependency="bsl/usbstk5505_led.d" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5505_spirom.obj: ../bsl/usbstk5505_spirom.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 -g --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --diag_warning=225 --large_memory_model --asm_source=mnemonic --preproc_with_compile --preproc_dependency="bsl/usbstk5505_spirom.d" --obj_directory="bsl" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


