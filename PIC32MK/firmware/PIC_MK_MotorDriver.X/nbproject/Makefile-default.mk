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
SOURCEFILES_QUOTED_IF_SPACED=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/initMk.c ../src/mkCoreTimer.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/initMk.o ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d ${OBJECTDIR}/_ext/1386493499/boardType.o.d ${OBJECTDIR}/_ext/1386493499/command.o.d ${OBJECTDIR}/_ext/1386493499/commandUart.o.d ${OBJECTDIR}/_ext/1386493499/control.o.d ${OBJECTDIR}/_ext/1386493499/controlPic.o.d ${OBJECTDIR}/_ext/1386493499/env.o.d ${OBJECTDIR}/_ext/1386493499/main.o.d ${OBJECTDIR}/_ext/1386493499/monitor.o.d ${OBJECTDIR}/_ext/1386493499/nvm.o.d ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d ${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1360937237/initMk.o.d ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/initMk.o ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/initMk.c ../src/mkCoreTimer.c ../src/main.c



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
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/6b85d2e1c91d4feb04d1535059d2905e02b9fa0d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/9277e11da41342b74a7772e5c71c19255ea6322e.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/bdff5b744d1be7542dccf79c8bf28885980daee.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/8941d8de13bf46e3f9a64d3f1d6dc3d43be4b171.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/f461bae130bd06f9af5aa0a4c3d7bcf9db5c1563.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/d657d5a1e32c2bfb6a96843cc661088ea8c8a95.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/aeef29160f3598b517d134f937514c88b0c4981d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/1174755e15df8305686e19e4de763b5eb56e7c30.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/5b84130278d3f238a2f985d600884194a1e54409.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/5c99a822b0b724b9d25cdf0c5722c255e8bc417b.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/d6f04d984437af6e4783c63622dcfb362003d030.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/78dbe77a6ca5c76c73557b40a160dde61d653823.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/79d113bfeede8dab086eb85e10b2f971273348f5.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/c86759fb761840c8678e42d4a19a4395f37a1f7d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/c6a6df4a469819a70f86e30d53821b6e53c8855d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/6c7e4fc4015adb0155ce0cc1c1f54286ff6d1ca8.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/2a2c54ec6adccb6e25d8d7e24c1529088f145fe8.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/c1b3ab455d36ec943ef0c8238ed7062ccb1a2369.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/54fe06ecf800a4230a35fde9abec2d0acf6f3dca.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/8cd138c5a06e79c9ecf5a821886cfeeb5a7ddfa1.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/e63586b64220a5a6118096793254d45af2c363c6.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/c3425072ea4d27c26c278774e8a71f19fc4659f9.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/ccf766a021cb0f483c7bb129323f7530bcedad8b.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/initMk.o: ../src/initMk.c  .generated_files/2972823cedd6f87c7b2658e7564d708f38c00d2d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/initMk.o.d" -o ${OBJECTDIR}/_ext/1360937237/initMk.o ../src/initMk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o: ../src/mkCoreTimer.c  .generated_files/3cf07a3be44fbb21c94b676ed51df373d1bee4d5.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o.d" -o ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o ../src/mkCoreTimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/b591e58247d44ae6eebe0474a017e3705b83efdd.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/d4aaea5ef6067c628930d0244deced2eb2be3263.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/8915651fdb0a085e276e450ef20463460fd60a83.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/eda6c039cfa6c6ae45d351ce65024ffb32764f07.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/f6559adc28e87a6b3ce212f94594d095aa8fd3f6.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/8697b36f22b81e0c95d0c8eeeb880f59324ddb6.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/8babae4ef3135252d029b3876684326708c759c0.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/c9e933371cd769c99d1fac25f7aee867a08c94be.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/ed28167bf81b70237737acc16f0aac36fefb27d6.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/aa66bcd369a95b92ca4984216c09343394107d75.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/3c27f867c8ad985b8459a12f64016e6c54639b90.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/e530d18807e17ec85cfac7986429575843f5feaf.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/313b1994332a996330daa9e0d580f13489df0b30.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/84e146b0bfea17277be892225375cf5dfadda7f7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/e103d6647277981315783202db802e46f8789985.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/25ede7de0587d568d0683c068a9bc95733e2c352.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/33806039077b417c6f9280049a83c9585d8af6a1.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/a667a8dbfdfe0d787ed30d472ad19f93e7b13ef7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/c9e176a091137a38f0d5b83a22848189c69cf031.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/f0823291ae83f747a21c174f2ca90fcaf76282c7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/cb6ff4492ca100a88ae0b91ad34326f67fe62fb3.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/ab61acb6780196476d076c5e9651a152bae857db.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/6cb8c56d1a3522d76c54cb32b5e8948d73a7862f.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/650319a0969178060dd91067c7e7967bf2122b8e.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/initMk.o: ../src/initMk.c  .generated_files/e85bf3bbbbebe46bd7f087699a1e1f3aac940eb3.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/initMk.o.d" -o ${OBJECTDIR}/_ext/1360937237/initMk.o ../src/initMk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o: ../src/mkCoreTimer.c  .generated_files/5a4d26bcaf033c36d37c2e77d5c5864461bc1381.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o.d" -o ${OBJECTDIR}/_ext/1360937237/mkCoreTimer.o ../src/mkCoreTimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/120e5d1f1311cbc6a228a0e0372a7f0e8c73b01b.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x36F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
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
