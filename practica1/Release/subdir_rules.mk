################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Vectors_intr.obj: ../Vectors_intr.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.6/bin/cl6x" -mv6700 --abi=coffabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.6/include" --include_path="C:/Users/adrian/Documents/Docencia/LC2/workspace/dskinit" --include_path="C:/DSK6713/c6000/dsk6713/include" --include_path="C:/DSK6713/c6000/bios/include" --define=c6713 --define=CHIP_6713 --display_error_number --diag_warning=225 --diag_wrap=off --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="Vectors_intr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

prac1_int.obj: ../prac1_int.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.6/bin/cl6x" -mv6700 --abi=coffabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.6/include" --include_path="C:/Users/adrian/Documents/Docencia/LC2/workspace/dskinit" --include_path="C:/DSK6713/c6000/dsk6713/include" --include_path="C:/DSK6713/c6000/bios/include" --define=c6713 --define=CHIP_6713 --display_error_number --diag_warning=225 --diag_wrap=off --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="prac1_int.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


