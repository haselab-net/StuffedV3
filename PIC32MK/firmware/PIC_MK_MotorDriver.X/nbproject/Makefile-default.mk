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
SOURCEFILES_QUOTED_IF_SPACED=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/peripheral/tmr1/plib_tmr1.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/initMk.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/initMk.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d ${OBJECTDIR}/_ext/1386493499/boardType.o.d ${OBJECTDIR}/_ext/1386493499/command.o.d ${OBJECTDIR}/_ext/1386493499/commandUart.o.d ${OBJECTDIR}/_ext/1386493499/control.o.d ${OBJECTDIR}/_ext/1386493499/controlPic.o.d ${OBJECTDIR}/_ext/1386493499/env.o.d ${OBJECTDIR}/_ext/1386493499/main.o.d ${OBJECTDIR}/_ext/1386493499/monitor.o.d ${OBJECTDIR}/_ext/1386493499/nvm.o.d ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d ${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1360937237/initMk.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/initMk.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/peripheral/tmr1/plib_tmr1.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/initMk.c ../src/main.c



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
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/2a9df21b0af2ab7fa0ba7f69076319a91dc410e4.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/7151418bd8d9b9f9c9cd829facae4b18865dcab6.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/950fd69d73c0e95103d989679c3c2a0d1841c5d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/2b5329b851159a265e35668888eaa9a20ff344c5.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/873d7d31627e545864cda551d9a9e172cba67314.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/d51adc1c59455b6929b6924c1cb51f7aa294b79a.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/63dddebebf926f4cb441a37bc9ccb810aa4d5ed0.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/336ce351fa5df71190211361ad53ccc9f7e8cdf0.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/f9a3aab1f0e6c9bb6a9bc94c38154d475f1c0a5c.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/a8c1b1ca3c07843209621e6d1e477504bdc07e62.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/d6b15ec29a44aa6fe1e730ed218975d74c7702ca.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/f206c14a0fe1b3bef3dac12e43c6dc390dd0c148.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/1c40453c25bd261ac25224e8bc095f46f99f8a23.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/3310dc7d10dad18ffab60f01f716f06cd1eb6387.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/2acfd569f463fd7943f4a6b72e001c7c897ce989.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/c1859696e9a3fb3cb31204488810199a50a5ac1f.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/b6e095fad35e6b463e7fa7f8dbd33a86756fc5de.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/c5910203e4119913f627ed38a0cd8f68746095f9.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/9f0efd706fa4546fdca0ba53ee2f4ceb289397f3.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865638794/plib_tmr1.o: ../src/config/default/peripheral/tmr1/plib_tmr1.c  .generated_files/e338ccc01590a5d79e1d8510374f26c46ce08d4a.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865638794" 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d" -o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ../src/config/default/peripheral/tmr1/plib_tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/7873beee0745fa2c56f8c32d11d83c7031fc334.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/9594e2b486dc536a4a52ac9f1e451589aab990f8.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/1d2b062263ff4ed1489f31c102ce1355c34633d4.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/ab6f4cec3a2e9828e89d0b60baf0c013030015f7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/5a0d3dd2e70c9d8a52ff5ef89d5435a6f0c93130.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/6b9067df246616031d5f2ed5e07da886e88f0d48.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/initMk.o: ../src/initMk.c  .generated_files/bfecc006afd55498d12c376dce56c4945f89ccd4.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/initMk.o.d" -o ${OBJECTDIR}/_ext/1360937237/initMk.o ../src/initMk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/2912d25af14f8520de3c85f3a8d58d2749d2623b.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/80e79f2d2e9bd13e0cd8382c1dc0bdc45a670201.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/c7ad8ee4a5e57a126d6e118b3701a4af3fe5a545.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/f8f29754a9967c769b9408e3d41bdeb65dea3f8d.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/3438ce0ccca7908259921e8c9647712f4024cc55.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/9cb3af4944083e5c5ed662ed1dcd2a0b6e9aba43.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/27d406f405e65aed74cb9d417b76539ce4cff8f8.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/e03cb679d36021a9899bf4a394039b4857b03522.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/c8b770078ebf28af9debecabbef86a834c496fb4.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/285a3149365614810429305757d3574a6aa4da45.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/7bdf2439d025cd35030d14b67bdf20ea38f7a8ad.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/3e93db96186e913055ea0dd2c70714309e765461.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/fe6e7d603371aefaf716c9396c05b74832288039.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/888842fed732ee57cdbd78119922bbe921899689.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/737c0171c31b346e07a4552e8a2f6d075b050bfa.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/8be8aec04762fa4095282781cc12f82e8fc09243.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/8eac67f2ea7bdeac351f6308f3b97bd16ea7d022.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/703315ebe043e11d67c9907965d007a8234c739.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/e4724b50e2e7e31f92662ab94335dd9732d94610.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/16d0f667021fd49db2d623f3c51c6dcd25ec47ef.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865638794/plib_tmr1.o: ../src/config/default/peripheral/tmr1/plib_tmr1.c  .generated_files/3f6ebd9b498df44298d2db206d86e0a7dc3dd369.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865638794" 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d" -o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ../src/config/default/peripheral/tmr1/plib_tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/6904377d87b9ddb246b7b42ed726f6238e6bd1cf.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/733baee5a31630c80260e1776cdf33aafe682e25.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/dbd9437348fe5d3a30c3aacaf8e3f355f5659224.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/8a049727be8579219af64a89b0ad19014e8a429a.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/eb987fbde1f9f3a005b690d544a3cfdd61c22efc.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/19e482eeca79b15530d7a978eb9eb956e8eb91c7.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/initMk.o: ../src/initMk.c  .generated_files/e8ad193339afde823b8fd56ae8895a92d737a737.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/initMk.o.d" -o ${OBJECTDIR}/_ext/1360937237/initMk.o ../src/initMk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/b3ccf008701bcfdf8f18ba1c49ffeaf55af8cfd9.flag .generated_files/f927575cf405b07867624a9f5160ad56c8744abc.flag
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
