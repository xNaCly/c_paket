FLAGS := -fdiagnostics-color=always  \
									 -Wall \
									 -Wpedantic \
									 -std=c99 \
									 -Wextra \
									 -Werror \
									 -Wshadow \
									 -Wundef \
									 -fno-common

SRC_DIR := ./src
BUILD_DIR := ./dist
DEBUG_DIR := $(BUILD_DIR)/debug
PROD_DIR := $(BUILD_DIR)/prod

OUT_NAME := cpak

FILES := $(shell find $(SRC_DIR) -name "*.c") 
CORE_FILES := $(shell find $(SRC_DIR)/core -name "*.c") 
COMPILE := $(FLAGS) $(FILES) -lm -o 
default: help

## This help screen
help:
			@printf "Available targets:\n\n"
			@awk '/^[a-zA-Z\-\_0-9%:\\]+/ { \
				helpMessage = match(lastLine, /^## (.*)/); \
				if (helpMessage) { \
					helpCommand = $$1; \
					helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
		gsub("\\\\", "", helpCommand); \
		gsub(":+$$", "", helpCommand); \
					printf "  \x1b[32;01m%-35s\x1b[0m %s\n", helpCommand, helpMessage; \
				} \
			} \
			{ lastLine = $$0 }' $(MAKEFILE_LIST) | sort -u
			@printf "\n"


## Build dev and run  
all: build
	$(BUILD_DIR)/$(OUT_NAME).dev

## Build and run tests
run/utest: build/utest 
	$(BUILD_DIR)/test.dev

## Build debug build and run using gdb
run/debug: build/debug
	gdb $(DEBUG_DIR)/$(OUT_NAME).debug

## Build optimised and run
run/prod: build/prod
	$(PROD_DIR)/$(OUT_NAME)

## Build dev
build: pre
	gcc $(COMPILE) $(BUILD_DIR)/$(OUT_NAME).dev

## Build tests
build/utest: pre
	gcc $(FLAGS) ./tests/test.c $(CORE_FILES) -lm -o $(BUILD_DIR)/test.dev

## Build debug
build/debug: pre/debug
	gcc -g3 $(COMPILE) $(DEBUG_DIR)/$(OUT_NAME).debug

## Build production
build/prod: pre/prod
	gcc -O3 $(COMPILE) $(PROD_DIR)/$(OUT_NAME)

pre: 
	mkdir -p $(BUILD_DIR)

pre/debug:
	mkdir -p $(DEBUG_DIR)

pre/prod:
	mkdir -p $(PROD_DIR)

#install: build/prod
#	cp ./xc.1 ./xc.1_copy
#	gzip ./xc.1_copy
#	mv ./xc.1_copy.gz ./xc.1.gz
#	sudo mkdir -p /usr/local/share/man/man1
#	sudo mv xc.1.gz /usr/local/share/man/man1/xc.1.gz
#	sudo mv $(BUILD_DIR)/xc.out /usr/local/bin/xc
#
#uninstall:
#	sudo rm /usr/local/man/man1/xc.1.gz
#	sudo rm /usr/local/bin/xc

## Clean dir up
clean:
	rm -r $(BUILD_DIR)
