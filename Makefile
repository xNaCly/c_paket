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
DEV_DIR := $(BUILD_DIR)/dev
TEST_DIR := $(BUILD_DIR)/test
PROD_DIR := $(BUILD_DIR)/prod
OUT_NAME := cpak
FILES := $(shell find $(SRC_DIR) -name "*.c")
CORE_FILES := $(shell find $(SRC_DIR)/core -name "*.c")
COMPILE := $(FLAGS) $(FILES) -o
V := alpha-0.0.1

all: build
	$(DEV_DIR)/$(OUT_NAME).dev $(cmd)

install: release build/prod
	sudo mv $(PROD_DIR)/$(OUT_NAME) /usr/local/bin/$(OUT_NAME)

uninstall:
	sudo rm /usr/local/bin/$(OUT_NAME)

release: build/prod
	# TODO: replace VERSION placeholder in src/cpak.h and in cpak.1 with the current release
	# TODO: build
	# TODO: zip executable and man page

test/unit: build/unit
	export CPAK_TESTING=true && export CPAK_CONFIG_HOME="$(PWD)/tests/example_config" && \
	$(TEST_DIR)/t_unit.dev

test/cli: build/cli
	export CPAK_TESTING=true && export CPAK_CONFIG_HOME="$(PWD)/tests/example_config" && \
	$(TEST_DIR)/t_cli.dev

run/debug: build/debug
	gdb $(DEBUG_DIR)/$(OUT_NAME).debug

run/prod: build/prod
	$(PROD_DIR)/$(OUT_NAME)

build: pre
	gcc $(COMPILE) $(DEV_DIR)/$(OUT_NAME).dev

build/unit: pre
	gcc -g3 $(FLAGS) ./tests/t_unit.c $(CORE_FILES) -o $(TEST_DIR)/t_unit.dev

build/cli: pre pre/test
	gcc -g3 $(FLAGS) ./tests/t_cli.c $(CORE_FILES) -o $(TEST_DIR)/t_cli.dev

build/debug: pre
	gcc -g3 $(COMPILE) $(DEBUG_DIR)/$(OUT_NAME).debug

build/prod: pre
	gcc -O3 $(COMPILE) $(PROD_DIR)/$(OUT_NAME)

pre:
	sed -i -e 's/__VERSION__/$(V)/g' ./cpak.1
	sed -i -e 's/__VERSION__/\"$(V)\"/g' ./src/cpak.h
	mkdir -p $(DEV_DIR)
	mkdir -p $(DEBUG_DIR)
	mkdir -p $(TEST_DIR)
	mkdir -p $(PROD_DIR)

pre/test:
	mkdir -p ./tests/output

clean:
	rm -r $(BUILD_DIR)
	git restore cpak.1 src/cpak.h
	unlink ./cpak_modules/*
	rm -r ./cpak_modules
