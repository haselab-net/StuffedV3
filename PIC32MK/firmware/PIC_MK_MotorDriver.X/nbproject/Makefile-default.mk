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
FINAL_IMAGE=${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/peripheral/tmr1/plib_tmr1.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/initMk.c ../src/main.c ../src/config/default/peripheral/qei/plib_qei1.c ../src/config/default/peripheral/qei/plib_qei3.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/initMk.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ${OBJECTDIR}/_ext/60178755/plib_qei3.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d ${OBJECTDIR}/_ext/1386493499/boardType.o.d ${OBJECTDIR}/_ext/1386493499/command.o.d ${OBJECTDIR}/_ext/1386493499/commandUart.o.d ${OBJECTDIR}/_ext/1386493499/control.o.d ${OBJECTDIR}/_ext/1386493499/controlPic.o.d ${OBJECTDIR}/_ext/1386493499/env.o.d ${OBJECTDIR}/_ext/1386493499/main.o.d ${OBJECTDIR}/_ext/1386493499/monitor.o.d ${OBJECTDIR}/_ext/1386493499/nvm.o.d ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d ${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1360937237/initMk.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/60178755/plib_qei1.o.d ${OBJECTDIR}/_ext/60178755/plib_qei3.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ${OBJECTDIR}/_ext/1386493499/boardType.o ${OBJECTDIR}/_ext/1386493499/command.o ${OBJECTDIR}/_ext/1386493499/commandUart.o ${OBJECTDIR}/_ext/1386493499/control.o ${OBJECTDIR}/_ext/1386493499/controlPic.o ${OBJECTDIR}/_ext/1386493499/env.o ${OBJECTDIR}/_ext/1386493499/main.o ${OBJECTDIR}/_ext/1386493499/monitor.o ${OBJECTDIR}/_ext/1386493499/nvm.o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1360937237/initMk.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ${OBJECTDIR}/_ext/60178755/plib_qei3.o

# Source Files
SOURCEFILES=../../../PIC/atan2Fixed.c ../../../PIC/boardType.c ../../../PIC/command.c ../../../PIC/commandUart.c ../../../PIC/control.c ../../../PIC/controlPic.c ../../../PIC/env.c ../../../PIC/main.c ../../../PIC/monitor.c ../../../PIC/nvm.c ../../../PIC/monitorOut.c ../src/config/default/peripheral/adchs/plib_adchs.c ../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/mcpwm/plib_mcpwm.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/qei/plib_qei2.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/peripheral/tmr1/plib_tmr1.c ../src/config/default/peripheral/uart/plib_uart1.c ../src/config/default/peripheral/uart/plib_uart2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/initMk.c ../src/main.c ../src/config/default/peripheral/qei/plib_qei1.c ../src/config/default/peripheral/qei/plib_qei3.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/flags/default/e4bda992c02dde40ccb598aff223a93bf46d664f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/flags/default/11d8a36951fce748c5a88ce98a615e0888e5978a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/flags/default/b949504b0045ab1336e2810c4a92c3f5af6c4f3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/flags/default/52da8e2e5f339a6ea5f08e5ce1add99d3fd3222d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/flags/default/c1c30a78dcaad2f685e9ebb12fc4df8df11c2b4a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/flags/default/76dc5d0712123d5e74e2fc4a9e0f71064348a2d6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/flags/default/6f591b2795871c5ade7af427b1e781db9be9c397 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/flags/default/61912ec40cdcf5d8eea116c30fd9ef7ac7187db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/flags/default/663ec49f39d1d34bd9d0d2728509c1f78dbee108 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/flags/default/1757216e95a08f7250b94364fe112316fd66d050 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/flags/default/aac0e569be39063ecd5efecf4c95e67e838e3d94 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/flags/default/26cfb24193df7681bf5d00d607f470ea26f1cab0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/flags/default/5de529b003a70efe048848736224714be817e5fe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/flags/default/f11d477f0a4998ba15ded86bc9cb5563b322fca0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/flags/default/2b4e7acaaed70afd7c23da648afbdd09cccaec1b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/flags/default/fbfff9daa8a7ec0aed805ad0842b9c27516d440d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/flags/default/16e582574bab19349fba450daaaece4690edd946 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/flags/default/68e0e9ae616f9d561c2bb019f45fcf7e1caab738 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/flags/default/8242ab2eaaf5d07d345dc0dd968af2fcf2aef72f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865638794/plib_tmr1.o: ../src/config/default/peripheral/tmr1/plib_tmr1.c  .generated_files/flags/default/dc2085757717c9a6ae4aafafe47e2e4c5c0a4c08 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865638794" 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d" -o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ../src/config/default/peripheral/tmr1/plib_tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/flags/default/ba9c7c3208f523b4544609575f2a9f08f00726c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/flags/default/f67fafbde3a2e6422f58566095e896a801914317 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/54b33da59e4066c37d94cd9b99fc77359457f5ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/9dc846eabc94287a331fbca93a3dde8889647487 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/e0c0c6f87c3165547605c0c0d16c6f52b5ab8a3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/6b1d84fa166d1f18da805207f05baca326c3da58 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/initMk.o: ../src/initMk.c  .generated_files/flags/default/d901e1610f41aca94958fa2352084d0551fb371f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/initMk.o.d" -o ${OBJECTDIR}/_ext/1360937237/initMk.o ../src/initMk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/ab45c3cc0b725365b6813dae0f5bde78d7cfa321 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60178755/plib_qei1.o: ../src/config/default/peripheral/qei/plib_qei1.c  .generated_files/flags/default/3c31e4766408ee50f06ddea0efaffe9af46742f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei1.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ../src/config/default/peripheral/qei/plib_qei1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60178755/plib_qei3.o: ../src/config/default/peripheral/qei/plib_qei3.c  .generated_files/flags/default/d37531db4346f68a1af808e5fffcfc8f07a7eaaf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei3.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei3.o ../src/config/default/peripheral/qei/plib_qei3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/_ext/1386493499/atan2Fixed.o: ../../../PIC/atan2Fixed.c  .generated_files/flags/default/956ebeec0ba1448358593b510ffbccd0b5d5de7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/atan2Fixed.o.d" -o ${OBJECTDIR}/_ext/1386493499/atan2Fixed.o ../../../PIC/atan2Fixed.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/boardType.o: ../../../PIC/boardType.c  .generated_files/flags/default/8d88f15e7616749e61ca0b693c79ca7351f4ccdf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/boardType.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/boardType.o.d" -o ${OBJECTDIR}/_ext/1386493499/boardType.o ../../../PIC/boardType.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/command.o: ../../../PIC/command.c  .generated_files/flags/default/6dac2f86a43fdba43493dd2b5b8497345f86e08a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/command.o.d" -o ${OBJECTDIR}/_ext/1386493499/command.o ../../../PIC/command.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/commandUart.o: ../../../PIC/commandUart.c  .generated_files/flags/default/425156b52a6f4308ff9924376ab23f1c3ac0fe63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/commandUart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/commandUart.o.d" -o ${OBJECTDIR}/_ext/1386493499/commandUart.o ../../../PIC/commandUart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/control.o: ../../../PIC/control.c  .generated_files/flags/default/119bf6ce5456541f52cb6fcd0d2e334d1fe09c21 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/control.o.d" -o ${OBJECTDIR}/_ext/1386493499/control.o ../../../PIC/control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/controlPic.o: ../../../PIC/controlPic.c  .generated_files/flags/default/b84f9e08cff8b61f6e29bfefb55f31c34deb3fdb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/controlPic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/controlPic.o.d" -o ${OBJECTDIR}/_ext/1386493499/controlPic.o ../../../PIC/controlPic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/env.o: ../../../PIC/env.c  .generated_files/flags/default/bcf50480d891c3ae0c9184217453ebaaf966d45a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/env.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/env.o.d" -o ${OBJECTDIR}/_ext/1386493499/env.o ../../../PIC/env.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/main.o: ../../../PIC/main.c  .generated_files/flags/default/7b6678309ac13ebb36c8d40f1085ac416dbb62b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/main.o.d" -o ${OBJECTDIR}/_ext/1386493499/main.o ../../../PIC/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/monitor.o: ../../../PIC/monitor.c  .generated_files/flags/default/f08cc9d5e081a490d5b9b80bb418338afcdb84bf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitor.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitor.o ../../../PIC/monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/nvm.o: ../../../PIC/nvm.c  .generated_files/flags/default/f335cd1c6afe748d3f850a47c42e6c01c02a47e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/nvm.o.d" -o ${OBJECTDIR}/_ext/1386493499/nvm.o ../../../PIC/nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1386493499/monitorOut.o: ../../../PIC/monitorOut.c  .generated_files/flags/default/755615572de64e697b85b9a63a7dac5c19ff8eaf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1386493499" 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/1386493499/monitorOut.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1386493499/monitorOut.o.d" -o ${OBJECTDIR}/_ext/1386493499/monitorOut.o ../../../PIC/monitorOut.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1982400153/plib_adchs.o: ../src/config/default/peripheral/adchs/plib_adchs.c  .generated_files/flags/default/ce1bd3e2c36b431c4f17f601d8b22d665b9e9d25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1982400153" 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1982400153/plib_adchs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1982400153/plib_adchs.o.d" -o ${OBJECTDIR}/_ext/1982400153/plib_adchs.o ../src/config/default/peripheral/adchs/plib_adchs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/flags/default/c3006f27b59cdca88b95700ceba934de22b9fc00 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/flags/default/92d8f4cbc925c157a9823efa3f848b319b0400b8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/flags/default/ae563f01023200158f760ad4d56ee090f676a415 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o: ../src/config/default/peripheral/mcpwm/plib_mcpwm.c  .generated_files/flags/default/5a4c79c9073d718ca268e9c0443d6bfda4f95699 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1993465566" 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o.d" -o ${OBJECTDIR}/_ext/1993465566/plib_mcpwm.o ../src/config/default/peripheral/mcpwm/plib_mcpwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/flags/default/e504f8404ab2fe997f4726166013e904aedc44d0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60178755/plib_qei2.o: ../src/config/default/peripheral/qei/plib_qei2.c  .generated_files/flags/default/64d1e2efb337318a4259dd08550f3783f0f320a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei2.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei2.o ../src/config/default/peripheral/qei/plib_qei2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/flags/default/3006ff375c4a4bc0faf3264fe806a2a8b94502c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865638794/plib_tmr1.o: ../src/config/default/peripheral/tmr1/plib_tmr1.c  .generated_files/flags/default/1357ee975ccfcdb8855d19175747d7d6d37a905 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865638794" 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865638794/plib_tmr1.o.d" -o ${OBJECTDIR}/_ext/1865638794/plib_tmr1.o ../src/config/default/peripheral/tmr1/plib_tmr1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865657120/plib_uart1.o: ../src/config/default/peripheral/uart/plib_uart1.c  .generated_files/flags/default/1591ac572b69084869644a2231c51b523725af4e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart1.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart1.o ../src/config/default/peripheral/uart/plib_uart1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1865657120/plib_uart2.o: ../src/config/default/peripheral/uart/plib_uart2.c  .generated_files/flags/default/ea3d5fb90597aeb9c40148390f01fc2ffcee40ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865657120" 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865657120/plib_uart2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865657120/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/1865657120/plib_uart2.o ../src/config/default/peripheral/uart/plib_uart2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/343f7b57f45c58389deeb555cdd734518026c123 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/ab85854f64c70c9b7bc6856639f6ca9c832463e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/3773055df3e19921c8ef6b00138e875a3cbfedfd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/62906829beb4637f01f60a0f1f484d733af970a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/initMk.o: ../src/initMk.c  .generated_files/flags/default/69e2aa7bfa9909bf669a0b4b89b92447d008e1b1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/initMk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/initMk.o.d" -o ${OBJECTDIR}/_ext/1360937237/initMk.o ../src/initMk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/c2211096266c6f8ebd90c57087738555a17d1363 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60178755/plib_qei1.o: ../src/config/default/peripheral/qei/plib_qei1.c  .generated_files/flags/default/c8f68361c5c7a074e4fc9dc7566ce40dea7c4612 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei1.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei1.o ../src/config/default/peripheral/qei/plib_qei1.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/60178755/plib_qei3.o: ../src/config/default/peripheral/qei/plib_qei3.c  .generated_files/flags/default/e10031c903915b69373837beb85ef22f4aa1b299 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60178755" 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60178755/plib_qei3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../src" -I"../../../PIC" -ffunction-sections -O1 -D__32MK0512MCJ064__ -I"../src" -I"../src/config/default" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60178755/plib_qei3.o.d" -o ${OBJECTDIR}/_ext/60178755/plib_qei3.o ../src/config/default/peripheral/qei/plib_qei3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/p32MK0512MCJ064.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x36F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/p32MK0512MCJ064.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/PIC_MK_MotorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
