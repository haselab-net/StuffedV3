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
ifeq "$(wildcard nbproject/Makefile-local-Simulation.mk)" "nbproject/Makefile-local-Simulation.mk"
include nbproject/Makefile-local-Simulation.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Simulation
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/uart1.c mcc_generated_files/adc1.c mcc_generated_files/interrupt_manager.c mcc_generated_files/exceptions.c mcc_generated_files/mccp1_compare.c mcc_generated_files/coretimer.c mcc_generated_files/uart2.c mcc_generated_files/sccp3_compare.c mcc_generated_files/sccp2_compare.c mcc_generated_files/spi2_driver.c mcc_generated_files/tmr1.c main.c atan2Fixed.c command.c control.c monitor.c env.c controlPic.c commandUart.c nvm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o ${OBJECTDIR}/mcc_generated_files/spi2_driver.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/atan2Fixed.o ${OBJECTDIR}/command.o ${OBJECTDIR}/control.o ${OBJECTDIR}/monitor.o ${OBJECTDIR}/env.o ${OBJECTDIR}/controlPic.o ${OBJECTDIR}/commandUart.o ${OBJECTDIR}/nvm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/pin_manager.o.d ${OBJECTDIR}/mcc_generated_files/mcc.o.d ${OBJECTDIR}/mcc_generated_files/uart1.o.d ${OBJECTDIR}/mcc_generated_files/adc1.o.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d ${OBJECTDIR}/mcc_generated_files/exceptions.o.d ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o.d ${OBJECTDIR}/mcc_generated_files/coretimer.o.d ${OBJECTDIR}/mcc_generated_files/uart2.o.d ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o.d ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o.d ${OBJECTDIR}/mcc_generated_files/spi2_driver.o.d ${OBJECTDIR}/mcc_generated_files/tmr1.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/atan2Fixed.o.d ${OBJECTDIR}/command.o.d ${OBJECTDIR}/control.o.d ${OBJECTDIR}/monitor.o.d ${OBJECTDIR}/env.o.d ${OBJECTDIR}/controlPic.o.d ${OBJECTDIR}/commandUart.o.d ${OBJECTDIR}/nvm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/pin_manager.o ${OBJECTDIR}/mcc_generated_files/mcc.o ${OBJECTDIR}/mcc_generated_files/uart1.o ${OBJECTDIR}/mcc_generated_files/adc1.o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o ${OBJECTDIR}/mcc_generated_files/exceptions.o ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o ${OBJECTDIR}/mcc_generated_files/coretimer.o ${OBJECTDIR}/mcc_generated_files/uart2.o ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o ${OBJECTDIR}/mcc_generated_files/spi2_driver.o ${OBJECTDIR}/mcc_generated_files/tmr1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/atan2Fixed.o ${OBJECTDIR}/command.o ${OBJECTDIR}/control.o ${OBJECTDIR}/monitor.o ${OBJECTDIR}/env.o ${OBJECTDIR}/controlPic.o ${OBJECTDIR}/commandUart.o ${OBJECTDIR}/nvm.o

# Source Files
SOURCEFILES=mcc_generated_files/pin_manager.c mcc_generated_files/mcc.c mcc_generated_files/uart1.c mcc_generated_files/adc1.c mcc_generated_files/interrupt_manager.c mcc_generated_files/exceptions.c mcc_generated_files/mccp1_compare.c mcc_generated_files/coretimer.c mcc_generated_files/uart2.c mcc_generated_files/sccp3_compare.c mcc_generated_files/sccp2_compare.c mcc_generated_files/spi2_driver.c mcc_generated_files/tmr1.c main.c atan2Fixed.c command.c control.c monitor.c env.c controlPic.c commandUart.c nvm.c


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
	${MAKE}  -f nbproject/Makefile-Simulation.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MM0064GPL036
MP_LINKER_FILE_OPTION=,--script="p32MM0064GPL036.ld"
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
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/mcc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/adc1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d" -o ${OBJECTDIR}/mcc_generated_files/adc1.o mcc_generated_files/adc1.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/mccp1_compare.o: mcc_generated_files/mccp1_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/mccp1_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/mccp1_compare.o.d" -o ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o mcc_generated_files/mccp1_compare.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/sccp3_compare.o: mcc_generated_files/sccp3_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/sccp3_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp3_compare.o.d" -o ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o mcc_generated_files/sccp3_compare.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/sccp2_compare.o: mcc_generated_files/sccp2_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/sccp2_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp2_compare.o.d" -o ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o mcc_generated_files/sccp2_compare.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/spi2_driver.o: mcc_generated_files/spi2_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2_driver.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/spi2_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi2_driver.o.d" -o ${OBJECTDIR}/mcc_generated_files/spi2_driver.o mcc_generated_files/spi2_driver.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/atan2Fixed.o: atan2Fixed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/atan2Fixed.o 
	@${FIXDEPS} "${OBJECTDIR}/atan2Fixed.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/atan2Fixed.o.d" -o ${OBJECTDIR}/atan2Fixed.o atan2Fixed.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/command.o: command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/command.o.d 
	@${RM} ${OBJECTDIR}/command.o 
	@${FIXDEPS} "${OBJECTDIR}/command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/command.o.d" -o ${OBJECTDIR}/command.o command.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/control.o: control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/control.o.d 
	@${RM} ${OBJECTDIR}/control.o 
	@${FIXDEPS} "${OBJECTDIR}/control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/control.o.d" -o ${OBJECTDIR}/control.o control.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/monitor.o: monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/monitor.o.d 
	@${RM} ${OBJECTDIR}/monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/monitor.o.d" -o ${OBJECTDIR}/monitor.o monitor.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/env.o: env.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/env.o.d 
	@${RM} ${OBJECTDIR}/env.o 
	@${FIXDEPS} "${OBJECTDIR}/env.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/env.o.d" -o ${OBJECTDIR}/env.o env.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/controlPic.o: controlPic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/controlPic.o.d 
	@${RM} ${OBJECTDIR}/controlPic.o 
	@${FIXDEPS} "${OBJECTDIR}/controlPic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/controlPic.o.d" -o ${OBJECTDIR}/controlPic.o controlPic.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/commandUart.o: commandUart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/commandUart.o.d 
	@${RM} ${OBJECTDIR}/commandUart.o 
	@${FIXDEPS} "${OBJECTDIR}/commandUart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/commandUart.o.d" -o ${OBJECTDIR}/commandUart.o commandUart.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/nvm.o: nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/nvm.o.d 
	@${RM} ${OBJECTDIR}/nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSimulator=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/nvm.o.d" -o ${OBJECTDIR}/nvm.o nvm.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/mcc_generated_files/pin_manager.o: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/pin_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/pin_manager.o mcc_generated_files/pin_manager.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/mcc.o: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/mcc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/mcc.o.d" -o ${OBJECTDIR}/mcc_generated_files/mcc.o mcc_generated_files/mcc.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/uart1.o: mcc_generated_files/uart1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart1.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/uart1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart1.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart1.o mcc_generated_files/uart1.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/adc1.o: mcc_generated_files/adc1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc1.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/adc1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc1.o.d" -o ${OBJECTDIR}/mcc_generated_files/adc1.o mcc_generated_files/adc1.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.o: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/interrupt_manager.o.d" -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.o mcc_generated_files/interrupt_manager.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/exceptions.o: mcc_generated_files/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/exceptions.o.d" -o ${OBJECTDIR}/mcc_generated_files/exceptions.o mcc_generated_files/exceptions.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/mccp1_compare.o: mcc_generated_files/mccp1_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/mccp1_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/mccp1_compare.o.d" -o ${OBJECTDIR}/mcc_generated_files/mccp1_compare.o mcc_generated_files/mccp1_compare.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/coretimer.o: mcc_generated_files/coretimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/coretimer.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/coretimer.o.d" -o ${OBJECTDIR}/mcc_generated_files/coretimer.o mcc_generated_files/coretimer.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/uart2.o: mcc_generated_files/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart2.o.d" -o ${OBJECTDIR}/mcc_generated_files/uart2.o mcc_generated_files/uart2.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/sccp3_compare.o: mcc_generated_files/sccp3_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/sccp3_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp3_compare.o.d" -o ${OBJECTDIR}/mcc_generated_files/sccp3_compare.o mcc_generated_files/sccp3_compare.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/sccp2_compare.o: mcc_generated_files/sccp2_compare.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/sccp2_compare.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/sccp2_compare.o.d" -o ${OBJECTDIR}/mcc_generated_files/sccp2_compare.o mcc_generated_files/sccp2_compare.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/spi2_driver.o: mcc_generated_files/spi2_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2_driver.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/spi2_driver.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/spi2_driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/spi2_driver.o.d" -o ${OBJECTDIR}/mcc_generated_files/spi2_driver.o mcc_generated_files/spi2_driver.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mcc_generated_files/tmr1.o: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.o 
	@${FIXDEPS} "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/mcc_generated_files/tmr1.o.d" -o ${OBJECTDIR}/mcc_generated_files/tmr1.o mcc_generated_files/tmr1.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/atan2Fixed.o: atan2Fixed.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/atan2Fixed.o.d 
	@${RM} ${OBJECTDIR}/atan2Fixed.o 
	@${FIXDEPS} "${OBJECTDIR}/atan2Fixed.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/atan2Fixed.o.d" -o ${OBJECTDIR}/atan2Fixed.o atan2Fixed.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/command.o: command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/command.o.d 
	@${RM} ${OBJECTDIR}/command.o 
	@${FIXDEPS} "${OBJECTDIR}/command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/command.o.d" -o ${OBJECTDIR}/command.o command.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/control.o: control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/control.o.d 
	@${RM} ${OBJECTDIR}/control.o 
	@${FIXDEPS} "${OBJECTDIR}/control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/control.o.d" -o ${OBJECTDIR}/control.o control.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/monitor.o: monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/monitor.o.d 
	@${RM} ${OBJECTDIR}/monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/monitor.o.d" -o ${OBJECTDIR}/monitor.o monitor.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/env.o: env.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/env.o.d 
	@${RM} ${OBJECTDIR}/env.o 
	@${FIXDEPS} "${OBJECTDIR}/env.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/env.o.d" -o ${OBJECTDIR}/env.o env.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/controlPic.o: controlPic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/controlPic.o.d 
	@${RM} ${OBJECTDIR}/controlPic.o 
	@${FIXDEPS} "${OBJECTDIR}/controlPic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/controlPic.o.d" -o ${OBJECTDIR}/controlPic.o controlPic.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/commandUart.o: commandUart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/commandUart.o.d 
	@${RM} ${OBJECTDIR}/commandUart.o 
	@${FIXDEPS} "${OBJECTDIR}/commandUart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/commandUart.o.d" -o ${OBJECTDIR}/commandUart.o commandUart.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/nvm.o: nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/nvm.o.d 
	@${RM} ${OBJECTDIR}/nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-toplevel-reorder -D__MPLAB_DEBUGGER_SIMULATOR -Werror -MMD -MF "${OBJECTDIR}/nvm.o.d" -o ${OBJECTDIR}/nvm.o nvm.c    -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p32MM0064GPL036.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DSimulator=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=Simulator=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p32MM0064GPL036.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Simulation=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIC.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Simulation
	${RM} -r dist/Simulation

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
