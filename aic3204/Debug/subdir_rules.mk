################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
aic3204_loop_linein.obj: ../aic3204_loop_linein.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="aic3204_loop_linein.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_test.obj: ../aic3204_test.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="aic3204_test.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_tone_headphone.obj: ../aic3204_tone_headphone.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="aic3204_tone_headphone.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="/opt/ti/ccsv7/tools/compiler/c5500_4.4.1/include" --include_path="/home/roy/Downloads/usbstk5505_v2/c55xx_csl/inc" --include_path="/home/roy/Downloads/usbstk5505_v2/include" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


