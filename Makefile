FLAGS := -fdiagnostics-color=always  \
									 -Wall \
									 -Wpedantic \
									 -std=c11 \
									 -Wextra \
									 -Werror \
									 -Wshadow \
									 -Wundef \
									 -fno-common

SRC_DIR := ./src
BUILD_DIR := ./dist
DEBUG_DIR := $(BUILD_DIR)/debug
TEST_DIR := $(BUILD_DIR)/test
PROD_DIR := $(BUILD_DIR)/prod

OUT_NAME := cpak

FILES := $(shell find $(SRC_DIR) -name "*.c") 
CORE_FILES := $(shell find $(SRC_DIR)/core -name "*.c") 
COMPILE := $(FLAGS) $(FILES) -lm -o 
default: help

help:
			@printf "Available targets:\n\n"
			@awk '/^[a-zA-Z\-_0-9%:\\]+/ { \
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
	$(BUILD_DIR)/$(OUT_NAME).dev $(cmd)

## install cpak
install: build/prod
	sudo mv $(PROD_DIR)/$(OUT_NAME) /usr/local/bin/$(OUT_NAME)

## uninstall cpak
uninstall:
	sudo rm /usr/local/bin/$(OUT_NAME)

test/lint:
	cppcheck --enable=all --error-exitcode=1 src/** --suppress=unusedFunction

## Build and run unit tests
test/unit: build/unit
	cp -r ./tests/example_config ~/.config/cpak
	export CPAK_TESTING=true && \
	$(TEST_DIR)/t_unit.dev

## Build and run cli tests
test/cli: build/cli
	cp -r ./tests/example_config ~/.config/cpak
	export CPAK_TESTING=true && \
	$(TEST_DIR)/t_cli.dev

## Build debug build and run using gdb
run/debug: build/debug
	gdb $(DEBUG_DIR)/$(OUT_NAME).debug

## Build optimised and run
run/prod: build/prod
	$(PROD_DIR)/$(OUT_NAME)

build: pre 
	gcc $(COMPILE) $(BUILD_DIR)/$(OUT_NAME).dev

build/unit: pre/test
	gcc -g3 $(FLAGS) ./tests/t_unit.c $(CORE_FILES) -lm -o $(TEST_DIR)/t_unit.dev

build/cli: pre/test
	gcc -g3 $(FLAGS) ./tests/t_cli.c $(CORE_FILES) -lm -o $(TEST_DIR)/t_cli.dev

build/debug: pre/debug
	gcc -g3 $(COMPILE) $(DEBUG_DIR)/$(OUT_NAME).debug

build/prod: pre/prod
	gcc -O3 $(COMPILE) $(PROD_DIR)/$(OUT_NAME)

pre: 
	mkdir -p $(BUILD_DIR)

pre/debug:
	mkdir -p $(DEBUG_DIR)

pre/test:
	mkdir -p $(TEST_DIR)

pre/prod:
	mkdir -p $(PROD_DIR)

## Clean dir up
clean:
	rm -r $(BUILD_DIR)
