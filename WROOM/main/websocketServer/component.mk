#
# Main Makefile. This is basically the same as a component makefile.
#
# This Makefile should, at the very least, just include $(SDK_PATH)/make/component_common.mk. By default, 
# this will take the sources in the src/ directory, compile them and link them into 
# lib(subdirectory_name).a in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#

COMPONENT_ADD_INCLUDEDIRS := . ../softRobot ../duktapeEsp32/include

COMPONENT_ADD_LDFLAGS := -L$(BUILD_DIR_BASE)/softRobot -lsoftRobot \
							-L$(BUILD_DIR_BASE)/duktapeEsp32 -lduktapeEsp32
