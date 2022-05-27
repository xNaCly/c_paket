FLAGS := -fdiagnostics-color=always  \
									 -Wall \
									 -Wpedantic \
									 -std=c11 \
									 -Wextra \
									 -Werror \
									 -Wshadow \
									 -Wundef \
									 -I./cpak_modules/libgit2/include\
									 -lgit2 \
									 -fno-common

SRC_DIR := ./src
BUILD_DIR := ./dist
DEBUG_DIR := $(BUILD_DIR)/debug
DEV_DIR := $(BUILD_DIR)/dev
TEST_DIR := $(BUILD_DIR)/test
PROD_DIR := $(BUILD_DIR)/prod

OUT_NAME := cpak

FILES := $(shell find $(SRC_DIR) -name "*.c")
CORE_FILES := $(shell find $(SRC_DIR)/core -name "*.c")
COMPILE := $(FLAGS) $(FILES) -o
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
	$(DEV_DIR)/$(OUT_NAME).dev $(cmd)

## install cpak
install: build/prod
	sudo mv $(PROD_DIR)/$(OUT_NAME) /usr/local/bin/$(OUT_NAME)

## uninstall cpak
uninstall:
	sudo rm /usr/local/bin/$(OUT_NAME)

## Build and run unit tests
test/unit: build/unit
	export CPAK_TESTING=true && export CPAK_CONFIG_HOME="$(PWD)/tests/example_config" && \
	$(TEST_DIR)/t_unit.dev

## Build and run cli tests
test/cli: build/cli
	export CPAK_TESTING=true && export CPAK_CONFIG_HOME="$(PWD)/tests/example_config" && \
	$(TEST_DIR)/t_cli.dev

## Build debug build and run using gdb
run/debug: build/debug
	gdb $(DEBUG_DIR)/$(OUT_NAME).debug

## Build optimised and run
run/prod: build/prod
	$(PROD_DIR)/$(OUT_NAME)

build: pre/dev
	gcc $(COMPILE) $(DEV_DIR)/$(OUT_NAME).dev

build/unit: pre/test
	gcc -g3 $(FLAGS) ./tests/t_unit.c $(CORE_FILES) -o $(TEST_DIR)/t_unit.dev

build/cli: pre/test
	gcc -g3 $(FLAGS) ./tests/t_cli.c $(CORE_FILES) -o $(TEST_DIR)/t_cli.dev

build/debug: pre/debug
	gcc -g3 $(COMPILE) $(DEBUG_DIR)/$(OUT_NAME).debug

build/prod: pre/prod
	gcc -O3 $(COMPILE) $(PROD_DIR)/$(OUT_NAME)

pre/dev:
	mkdir -p $(DEV_DIR)

pre/debug:
	mkdir -p $(DEBUG_DIR)

pre/test:
	./bin/cpak a libgit2/libgit2
	mkdir -p ./tests/output
	mkdir -p $(TEST_DIR)

pre/prod:
	mkdir -p $(PROD_DIR)


## Clean dir up
clean:
	rm -r $(BUILD_DIR)
