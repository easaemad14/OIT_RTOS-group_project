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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=FreeRTOS/Source/croutine.c FreeRTOS/Source/portable/MemMang/heap_2.c FreeRTOS/Source/list.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c Lab.X/src/main.c Lab.X/src/elevator.c Lab.X/src/controllers.c Lab.X/src/leddrv.c Lab.X/src/swdrv.c Lab.X/src/uartdrv.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FreeRTOS/Source/croutine.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o ${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/Lab.X/src/main.o ${OBJECTDIR}/Lab.X/src/elevator.o ${OBJECTDIR}/Lab.X/src/controllers.o ${OBJECTDIR}/Lab.X/src/leddrv.o ${OBJECTDIR}/Lab.X/src/swdrv.o ${OBJECTDIR}/Lab.X/src/uartdrv.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FreeRTOS/Source/croutine.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o.d ${OBJECTDIR}/FreeRTOS/Source/list.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d ${OBJECTDIR}/FreeRTOS/Source/queue.o.d ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d ${OBJECTDIR}/Lab.X/src/main.o.d ${OBJECTDIR}/Lab.X/src/elevator.o.d ${OBJECTDIR}/Lab.X/src/controllers.o.d ${OBJECTDIR}/Lab.X/src/leddrv.o.d ${OBJECTDIR}/Lab.X/src/swdrv.o.d ${OBJECTDIR}/Lab.X/src/uartdrv.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FreeRTOS/Source/croutine.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o ${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/Lab.X/src/main.o ${OBJECTDIR}/Lab.X/src/elevator.o ${OBJECTDIR}/Lab.X/src/controllers.o ${OBJECTDIR}/Lab.X/src/leddrv.o ${OBJECTDIR}/Lab.X/src/swdrv.o ${OBJECTDIR}/Lab.X/src/uartdrv.o

# Source Files
SOURCEFILES=FreeRTOS/Source/croutine.c FreeRTOS/Source/portable/MemMang/heap_2.c FreeRTOS/Source/list.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c Lab.X/src/main.c Lab.X/src/elevator.c Lab.X/src/controllers.c Lab.X/src/leddrv.c Lab.X/src/swdrv.c Lab.X/src/uartdrv.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX360F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.ok ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d" "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -DSKDEPIC32PlatformTool=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"Lab.X/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d"  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=SKDEPIC32PlatformTool=1
	
else
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.ok ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d" "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"Lab.X/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d"  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FreeRTOS/Source/croutine.o: FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/croutine.o FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o: FreeRTOS/Source/portable/MemMang/heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o FreeRTOS/Source/portable/MemMang/heap_2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/list.o FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/queue.o FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o FreeRTOS/Source/tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/main.o: Lab.X/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/main.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/main.o.d" -o ${OBJECTDIR}/Lab.X/src/main.o Lab.X/src/main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/elevator.o: Lab.X/src/elevator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/elevator.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/elevator.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/elevator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/elevator.o.d" -o ${OBJECTDIR}/Lab.X/src/elevator.o Lab.X/src/elevator.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/controllers.o: Lab.X/src/controllers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/controllers.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/controllers.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/controllers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/controllers.o.d" -o ${OBJECTDIR}/Lab.X/src/controllers.o Lab.X/src/controllers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/leddrv.o: Lab.X/src/leddrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/leddrv.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/leddrv.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/leddrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/leddrv.o.d" -o ${OBJECTDIR}/Lab.X/src/leddrv.o Lab.X/src/leddrv.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/swdrv.o: Lab.X/src/swdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/swdrv.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/swdrv.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/swdrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/swdrv.o.d" -o ${OBJECTDIR}/Lab.X/src/swdrv.o Lab.X/src/swdrv.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/uartdrv.o: Lab.X/src/uartdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/uartdrv.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/uartdrv.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/uartdrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DSKDEPIC32PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/uartdrv.o.d" -o ${OBJECTDIR}/Lab.X/src/uartdrv.o Lab.X/src/uartdrv.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/FreeRTOS/Source/croutine.o: FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/croutine.o FreeRTOS/Source/croutine.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o: FreeRTOS/Source/portable/MemMang/heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_2.o FreeRTOS/Source/portable/MemMang/heap_2.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/list.o FreeRTOS/Source/list.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/queue.o FreeRTOS/Source/queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o FreeRTOS/Source/tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/main.o: Lab.X/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/main.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/main.o.d" -o ${OBJECTDIR}/Lab.X/src/main.o Lab.X/src/main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/elevator.o: Lab.X/src/elevator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/elevator.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/elevator.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/elevator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/elevator.o.d" -o ${OBJECTDIR}/Lab.X/src/elevator.o Lab.X/src/elevator.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/controllers.o: Lab.X/src/controllers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/controllers.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/controllers.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/controllers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/controllers.o.d" -o ${OBJECTDIR}/Lab.X/src/controllers.o Lab.X/src/controllers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/leddrv.o: Lab.X/src/leddrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/leddrv.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/leddrv.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/leddrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/leddrv.o.d" -o ${OBJECTDIR}/Lab.X/src/leddrv.o Lab.X/src/leddrv.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/swdrv.o: Lab.X/src/swdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/swdrv.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/swdrv.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/swdrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/swdrv.o.d" -o ${OBJECTDIR}/Lab.X/src/swdrv.o Lab.X/src/swdrv.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Lab.X/src/uartdrv.o: Lab.X/src/uartdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Lab.X/src" 
	@${RM} ${OBJECTDIR}/Lab.X/src/uartdrv.o.d 
	@${RM} ${OBJECTDIR}/Lab.X/src/uartdrv.o 
	@${FIXDEPS} "${OBJECTDIR}/Lab.X/src/uartdrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"Lab.X/include" -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/Lab.X/src/uartdrv.o.d" -o ${OBJECTDIR}/Lab.X/src/uartdrv.o Lab.X/src/uartdrv.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DSKDEPIC32PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=SKDEPIC32PlatformTool=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Elevator.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
