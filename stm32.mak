#This file is generated by VisualGDB.
#It contains GCC settings automatically derived from the board support package (BSP).
#DO NOT EDIT MANUALLY. THE FILE WILL BE OVERWRITTEN. 
#Use VisualGDB Project Properties dialog or modify Makefile or per-configuration .mak files instead.

#VisualGDB provides BSP_ROOT and TOOLCHAIN_ROOT via environment when running Make. The line below will only be active if GNU Make is started manually.
BSP_ROOT ?= $(LOCALAPPDATA)/VisualGDB/EmbeddedBSPs/arm-eabi/com.sysprogs.arm.stm32
EFP_BASE ?= $(LOCALAPPDATA)/VisualGDB/EmbeddedEFPs
TESTFW_BASE ?= $(LOCALAPPDATA)/VisualGDB/TestFrameworks
TOOLCHAIN_ROOT ?= C:/SysGCC/arm-eabi
#Embedded toolchain
CC := $(TOOLCHAIN_ROOT)/bin/arm-eabi-gcc.exe
CXX := $(TOOLCHAIN_ROOT)/bin/arm-eabi-g++.exe
LD := $(CXX)
AR := $(TOOLCHAIN_ROOT)/bin/arm-eabi-ar.exe
OBJCOPY := $(TOOLCHAIN_ROOT)/bin/arm-eabi-objcopy.exe

#Additional flags
PREPROCESSOR_MACROS += ARM_MATH_CM3 STM32F107VC
INCLUDE_DIRS += .
LIBRARY_DIRS += 
LIBRARY_NAMES += 
ADDITIONAL_LINKER_INPUTS += 
MACOS_FRAMEWORKS += 
LINUX_PACKAGES += 

CFLAGS += 
CXXFLAGS += 
ASFLAGS += 
LDFLAGS += --specs=nano.specs -u _printf_float --specs=nosys.specs
COMMONFLAGS += -mcpu=cortex-m3 -mthumb
LINKER_SCRIPT := $(BSP_ROOT)/STM32F1xxxx/LinkerScripts/STM32F107VC_flash.lds

