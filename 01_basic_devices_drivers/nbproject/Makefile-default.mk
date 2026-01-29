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
FINAL_IMAGE=${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=ecu_layer/button/ecu_button.c ecu_layer/dc_motor/ecu_dc_motor.c ecu_layer/keypad/ecu_keypad.c ecu_layer/lcd/ecu_lcd.c ecu_layer/led/ecu_led.c ecu_layer/relay/ecu_relay.c ecu_layer/seven_segment/ecu_seven_seg.c mcal_layer/gpio/hal_gpio.c mcal_layer/device_config.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ecu_layer/button/ecu_button.p1 ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1 ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1 ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1 ${OBJECTDIR}/ecu_layer/led/ecu_led.p1 ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1 ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1 ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1 ${OBJECTDIR}/mcal_layer/device_config.p1 ${OBJECTDIR}/main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/ecu_layer/button/ecu_button.p1.d ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1.d ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1.d ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1.d ${OBJECTDIR}/ecu_layer/led/ecu_led.p1.d ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1.d ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1.d ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1.d ${OBJECTDIR}/mcal_layer/device_config.p1.d ${OBJECTDIR}/main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ecu_layer/button/ecu_button.p1 ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1 ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1 ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1 ${OBJECTDIR}/ecu_layer/led/ecu_led.p1 ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1 ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1 ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1 ${OBJECTDIR}/mcal_layer/device_config.p1 ${OBJECTDIR}/main.p1

# Source Files
SOURCEFILES=ecu_layer/button/ecu_button.c ecu_layer/dc_motor/ecu_dc_motor.c ecu_layer/keypad/ecu_keypad.c ecu_layer/lcd/ecu_lcd.c ecu_layer/led/ecu_led.c ecu_layer/relay/ecu_relay.c ecu_layer/seven_segment/ecu_seven_seg.c mcal_layer/gpio/hal_gpio.c mcal_layer/device_config.c main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4620
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ecu_layer/button/ecu_button.p1: ecu_layer/button/ecu_button.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/button" 
	@${RM} ${OBJECTDIR}/ecu_layer/button/ecu_button.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/button/ecu_button.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/button/ecu_button.p1 ecu_layer/button/ecu_button.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/button/ecu_button.d ${OBJECTDIR}/ecu_layer/button/ecu_button.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/button/ecu_button.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1: ecu_layer/dc_motor/ecu_dc_motor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/dc_motor" 
	@${RM} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1 ecu_layer/dc_motor/ecu_dc_motor.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.d ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1: ecu_layer/keypad/ecu_keypad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/keypad" 
	@${RM} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1 ecu_layer/keypad/ecu_keypad.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.d ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1: ecu_layer/lcd/ecu_lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/lcd" 
	@${RM} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1 ecu_layer/lcd/ecu_lcd.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.d ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/led/ecu_led.p1: ecu_layer/led/ecu_led.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/led" 
	@${RM} ${OBJECTDIR}/ecu_layer/led/ecu_led.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/led/ecu_led.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/led/ecu_led.p1 ecu_layer/led/ecu_led.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/led/ecu_led.d ${OBJECTDIR}/ecu_layer/led/ecu_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/led/ecu_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1: ecu_layer/relay/ecu_relay.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/relay" 
	@${RM} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1 ecu_layer/relay/ecu_relay.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.d ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1: ecu_layer/seven_segment/ecu_seven_seg.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/seven_segment" 
	@${RM} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1 ecu_layer/seven_segment/ecu_seven_seg.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.d ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1: mcal_layer/gpio/hal_gpio.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcal_layer/gpio" 
	@${RM} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1.d 
	@${RM} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1 mcal_layer/gpio/hal_gpio.c 
	@-${MV} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.d ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcal_layer/device_config.p1: mcal_layer/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcal_layer" 
	@${RM} ${OBJECTDIR}/mcal_layer/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcal_layer/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcal_layer/device_config.p1 mcal_layer/device_config.c 
	@-${MV} ${OBJECTDIR}/mcal_layer/device_config.d ${OBJECTDIR}/mcal_layer/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcal_layer/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/ecu_layer/button/ecu_button.p1: ecu_layer/button/ecu_button.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/button" 
	@${RM} ${OBJECTDIR}/ecu_layer/button/ecu_button.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/button/ecu_button.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/button/ecu_button.p1 ecu_layer/button/ecu_button.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/button/ecu_button.d ${OBJECTDIR}/ecu_layer/button/ecu_button.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/button/ecu_button.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1: ecu_layer/dc_motor/ecu_dc_motor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/dc_motor" 
	@${RM} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1 ecu_layer/dc_motor/ecu_dc_motor.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.d ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/dc_motor/ecu_dc_motor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1: ecu_layer/keypad/ecu_keypad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/keypad" 
	@${RM} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1 ecu_layer/keypad/ecu_keypad.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.d ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/keypad/ecu_keypad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1: ecu_layer/lcd/ecu_lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/lcd" 
	@${RM} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1 ecu_layer/lcd/ecu_lcd.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.d ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/lcd/ecu_lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/led/ecu_led.p1: ecu_layer/led/ecu_led.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/led" 
	@${RM} ${OBJECTDIR}/ecu_layer/led/ecu_led.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/led/ecu_led.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/led/ecu_led.p1 ecu_layer/led/ecu_led.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/led/ecu_led.d ${OBJECTDIR}/ecu_layer/led/ecu_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/led/ecu_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1: ecu_layer/relay/ecu_relay.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/relay" 
	@${RM} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1 ecu_layer/relay/ecu_relay.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.d ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/relay/ecu_relay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1: ecu_layer/seven_segment/ecu_seven_seg.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ecu_layer/seven_segment" 
	@${RM} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1.d 
	@${RM} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1 ecu_layer/seven_segment/ecu_seven_seg.c 
	@-${MV} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.d ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ecu_layer/seven_segment/ecu_seven_seg.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1: mcal_layer/gpio/hal_gpio.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcal_layer/gpio" 
	@${RM} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1.d 
	@${RM} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1 mcal_layer/gpio/hal_gpio.c 
	@-${MV} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.d ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcal_layer/gpio/hal_gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcal_layer/device_config.p1: mcal_layer/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcal_layer" 
	@${RM} ${OBJECTDIR}/mcal_layer/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcal_layer/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcal_layer/device_config.p1 mcal_layer/device_config.c 
	@-${MV} ${OBJECTDIR}/mcal_layer/device_config.d ${OBJECTDIR}/mcal_layer/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcal_layer/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gcoff -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gcoff -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/01_basic_devices_drivers.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
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
