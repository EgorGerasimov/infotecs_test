CFLAGS=-std=c++20 -Wall -Wextra
DFLAGS=-g3
CC=g++
TARGET=buffer.a
EXECUTABLE=buffer
FILEFORMAT=cpp

SRC_DIR=buffer_lib
BUILD_DIR=obj
BIN_DIR=bin

MODULES=$(shell find "$(SRC_DIR)" -name "*.$(FILEFORMAT)")
OBJECTS=$(MODULES:%.$(FILEFORMAT)=%.o)

.PHONY: all run build rebuild clean format_style valgrind_check $(TARGET)

all: format_style rebuild

$(TARGET): create_dir $(OBJECTS)
	@ar rcs $(BUILD_DIR)/$(TARGET) $(OBJECTS:%.o=$(BUILD_DIR)/%.o)

build: $(TARGET)
	@$(CC) $(CFLAGS) main.$(FILEFORMAT) $(BUILD_DIR)/$(TARGET) -o $(BIN_DIR)/$(EXECUTABLE)

rebuild: clean build

run: build
	@./$(BIN_DIR)/$(EXECUTABLE)

clean:
	@rm -rf obj bin log



debug: create_dir
	$(CC) $(DFLAGS) $(MODULES_RUN) -o $(BIN_DIR)/$@

format_style:
	@clang-format -i *.$(FILEFORMAT) */*.$(FILEFORMAT) */*.hpp 

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.$(FILEFORMAT) */*.$(FILEFORMAT) */*.hpp

valgrind_check: build
	valgrind --track-origins=yes --leak-check=full ./$(BIN_DIR)/$(EXECUTABLE)

%.o: %.$(FILEFORMAT)
	@$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $^

create_dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	@mkdir -p $(BIN_DIR)