# Application name
APPL ?= freertos_iot_aws_smarthomedemo

# Heap Size Settings
HEAPSZ ?= 1048676
STACKSZ ?= 1048576

# Logging level control in AWS SDK
#LOG_FLAGS += -DIOT_DEBUG
LOG_FLAGS += -DIOT_INFO
LOG_FLAGS += -DIOT_WARN
LOG_FLAGS += -DIOT_ERROR

APPL_DEFINES  = $(LOG_FLAGS) -DMBEDTLS_CONFIG_FILE=\"mbedtls_config.h\"

#
# root dir of embARC
#
EMBARC_ROOT = ../../../../..

# Selected OS
OS_SEL ?= freertos
MID_SEL = common fatfs mbedtls lwip lwip-contrib aws

# application source dirs
APPL_CSRC_DIR = .
APPL_ASMSRC_DIR = .

# application include dirs
APPL_INC_DIR = .

# include current project makefile
COMMON_COMPILE_PREREQUISITES += makefile

### Options above must be added before include options.mk ###
# include key embARC build system makefile
override EMBARC_ROOT := $(strip $(subst \,/,$(EMBARC_ROOT)))
include $(EMBARC_ROOT)/options/options.mk
