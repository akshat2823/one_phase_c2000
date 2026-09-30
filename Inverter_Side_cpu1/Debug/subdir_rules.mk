################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc --fp_mode=relaxed --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/My Files/Headers" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Device/Common Include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Device/Headers Include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Device/driverlib" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Device/driverlib/inc" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Libraries/DCL_Control/include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Libraries/FFT/include/fpu32" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Libraries/IQ_math/include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Libraries/Power Measurement/include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Libraries/Rampgen/include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Libraries/Spll/include" --include_path="C:/Users/LENEVO/Desktop/one_phase_C2000/ACPS_1phase/Inverter_Side_cpu1/Libraries/transforms" --advice:performance=all --define=CPU1 --define=DEBUG --define=_FLASH --define=_LAUNCHXL_F28388D -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


