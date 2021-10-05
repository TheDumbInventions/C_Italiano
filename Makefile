BUILD_NAME 			= app
CC     				= gcc

MAKEFILE_PATH 		= $(abspath $(lastword $(MAKEFILE_LIST)))
PROJ_DIR 			= $(patsubst %/,%,$(dir $(MAKEFILE_PATH)))

C_DIR 				= $(PROJ_DIR)/src
H_DIR 				= $(PROJ_DIR)/include
BUILD_DIR  			= $(PROJ_DIR)/build

PRETRADUTTORE 		= $(PROJ_DIR)/dependencies/exe/pretraduttore.exe
PRETRADUTTORE_DIR 	= $(PROJ_DIR)/pretraduttore

$(BUILD_DIR)/$(BUILD_NAME): $(wildcard $(C_DIR)/*.c) $(wildcard $(H_DIR)/*.h)
	$(PRETRADUTTORE) $(PRETRADUTTORE_DIR) $(wildcard $(C_DIR)/*.c) $(wildcard $(H_DIR)/*.h)
	$(CC) $(wildcard $(PRETRADUTTORE_DIR)/*.c) -o $(BUILD_DIR)/$(BUILD_NAME) -include $(PROJ_DIR)/dependencies/include/italiano.h