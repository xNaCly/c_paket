MAIN_FILE := main
BUILD_DIR := ./dist

all: build
	$(BUILD_DIR)/$(MAIN_FILE).out

build: pre
	gcc $(MAIN_FILE).c -o $(BUILD_DIR)/$(MAIN_FILE).out

pre:
	mkdir -p $(BUILD_DIR)

clean:
	rm -r $(BUILD_DIR)
