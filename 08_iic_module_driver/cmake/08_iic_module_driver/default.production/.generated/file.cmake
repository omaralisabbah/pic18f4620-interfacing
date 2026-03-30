# The following variables contains the files used by the different stages of the build process.
set(08_iic_module_driver_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${08_iic_module_driver_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${08_iic_module_driver_default_default_XC8_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(08_iic_module_driver_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${08_iic_module_driver_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${08_iic_module_driver_default_default_XC8_FILE_TYPE_assemblePreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(08_iic_module_driver_default_default_XC8_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ecu_layer/button/ecu_button.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ecu_layer/dc_motor/ecu_dc_motor.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ecu_layer/keypad/ecu_keypad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ecu_layer/lcd/ecu_lcd.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ecu_layer/led/ecu_led.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ecu_layer/relay/ecu_relay.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ecu_layer/seven_segment/ecu_seven_seg.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/adc/hal_adc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/ccp/hal_ccp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/device_config.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/eeprom/hal_eeprom.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/gpio/hal_gpio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/i2c/hal_i2c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/interrupt/mcal_external_interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/interrupt/mcal_internal_interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/interrupt/mcal_interrupt_manager.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/spi/hal_spi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/timer0/hal_timr0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/timer1/hal_timr1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/timer2/hal_timr2.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/timer3/hal_timr3.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mcal_layer/usart/hal_usart.c")
set_source_files_properties(${08_iic_module_driver_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(08_iic_module_driver_default_default_XC8_FILE_TYPE_link)
set(08_iic_module_driver_default_image_name "default-production.elf")
set(08_iic_module_driver_default_image_base_name "default-production")

# The output directory of the final image.
set(08_iic_module_driver_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/08_iic_module_driver/production")

# The full path to the final image.
set(08_iic_module_driver_default_full_path_to_image ${08_iic_module_driver_default_output_dir}/${08_iic_module_driver_default_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .hxl
    .mum
    .o
    .sdb
    .sym
    .cmf)
list(TRANSFORM output_extensions PREPEND "${08_iic_module_driver_default_output_dir}/${08_iic_module_driver_default_image_base_name}")
