#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/qei/plib_qei1.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/qei/plib_qei3.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/60178755/plib_qei3.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d ${OBJECTDIR}/_ext/1386493499/boardType.o.d ${OBJECTDIR}/_ext/1386493499/command.o.d ${OBJECTDIR}/_ext/1386493499/commandUart.o.d ${OBJECTDIR}/_ext/1386493499/control.o.d ${OBJECTDIR}/_ext/1386493499/controlPic.o.d ${OBJECTDIR}/_ext/1386493499/env.o.d ${OBJECTDIR}/_ext/1386493499/main.o.d ${OBJECTDIR}/_ext/1386493499/monitor.o.d ${OBJECTDIR}/_ext/1386493499/nvm.o.d ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d ${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d ${OBJECTDIR}/_ext/60178755/plib_qei1.o.d ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d ${OBJECTDIR}/_ext/60178755/plib_qei3.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/60178755/plib_qei3.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/qei/plib_qei1.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/qei/plib_qei3.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MK0512MCJ064
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\p32MK0512MCJ064.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/7c04bb0021df796c15c4783357a67610c8fd911a.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/fe661ff1fa9e0d559679b099de99674d7c1d6631.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/3cf78394c1c1f6fe1bf45d4a7abd85461a92a094.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/8f03c0f7f4ac80d3084dfe2a5712098b9ceff6b1.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/b762a0cfa9546c1f6a1297065fbadda61f9931cc.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/437e49e5ed5591e41b7eaf40e95770544bd2075e.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/2672e926a003fcd88be3d098eacea5d93f6f0109.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/b083fbcb7eb3776921248ec3b57e8c92831a4a5f.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/1cdc8a99d893ea47ddc08556b075f0641127029c.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/749ed3b0f03e109434337c3378e4f5a7d20556b4.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/ce38ece0ce42b319b2e55e9fcfbb9d3b417e64f3.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/fbc191c206ae8f9c417435fbc44335bca7eedfc0.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/3777219f24187fa34ff56d3d926265b53bcfe420.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/420c500dba45210f646c20a4a8b3d0c8b0f95583.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/277524d64618049895c3cc61973b0c5c2bda0eff.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/6316768b0dadc666d56012f0072f6af3fe1770e2.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/64eca6e19d0ebd9a7e70b149ab4725190f571cc0.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei1.o: ../src/config/default/peripheral/qei/plib_qei1.c  .generated_files/d935a45c7a67906a934deb7d195672f06e8f5a14.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei1.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ../src/config/default/peripheral/qei/plib_qei1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/b66a51398891e478dae9487851fc1f1076994746.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei3.o: ../src/config/default/peripheral/qei/plib_qei3.c  .generated_files/1de0b49ea19514381e100bdb16d8de095a1fc4a7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei3.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei3.o ../src/config/default/peripheral/qei/plib_qei3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/dad9b47c594f69900dead045806948bc51a98592.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/3226923b387536789e2f343d92c952f443897da0.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/261fecffcb76b72dd7cebb3d80b0b4f245fa3c13.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/c169f79169bd4a3770a3b6cd401254f1ec704b5f.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/af653cc644fae2cb38b869378501009801293e85.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/a31840327100522446de73233c1b85b82d75e4e.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/e92a25ebab8b52c1c8d3648d4ee5c58d138944c7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/4e3568d1d0e66e46a3252ac9e0723f4cf8045e61.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/7e0ed71eb1913ba105cb85a08af9b18291e9f148.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/eb15bee268b5593b1db37dcf21151226f31e8bb.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/ffc78c4994630632b310863682a754a298762b22.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/84f73e5885e194b3ecea4cbf3c9271fa0b2ff3e3.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/805621b49f7f01963e6b5548e8b890c645644ff5.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/bbfa318eade48e41312b4ec648a846fc1bfd882b.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/8adc114a6e740917552eca860a1522fd9123caf7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/95d814157bd47fb5e4421fd7517cdb9283b957ea.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/8d6efad3326baf0d971452bec6cb2f58ae2c93d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/92d1e56e6646a5433e9dfdc46803809204607be.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/2e98f3ba3ce5de5ec74459b5238cf091711f774.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/1d116aafd21e378309d96617a64dcc00876d03ee.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/c06f1253a2521ea1196aa5250b5ea0fe4b59256f.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/55f91b193f560b7a71369c4501063606002ff346.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/5be7a20015a3a4d522d775b55d7dda4e96a8592f.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/f5438ca0189495c59cd84f714c782d5eee59a528.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei1.o: ../src/config/default/peripheral/qei/plib_qei1.c  .generated_files/1ee18b8933004d2c0d5a12942a828b9c613c18f5.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei1.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ../src/config/default/peripheral/qei/plib_qei1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/c6832838ef1d95339d896aab926cdcb07a047a5a.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei3.o: ../src/config/default/peripheral/qei/plib_qei3.c  .generated_files/db7923ba414b7319d16a5c36d25ce0e4cea09c49.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei3.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei3.o ../src/config/default/peripheral/qei/plib_qei3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/7698a9cd701117253fef6269f46b47a127336204.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/aee13255e0f8cd3df245f0ece071e6d5be037238.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/377db7e56034372dbf6b248a26f01bc62be8184c.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/946fa8c6b13ccc85c1b9cd0e44486002b3d5bc4b.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/1c4389737a540d21cb4be97a2375f0d1c3ac9c41.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/badbc298bdd629c01625914e261abeb47c7588c5.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/6c38ea4906e5e2605995e25e5c016b6c77b39ed5.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/p32MK0512MCJ064.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/p32MK0512MCJ064.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
