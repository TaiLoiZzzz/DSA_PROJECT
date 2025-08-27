# Makefile cho Test Suite
# Sử dụng g++ compiler

# Biến
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
INCLUDES = -I../include

# Đường dẫn
BUILD_DIR = ../build
BIN_DIR = ../bin

# Test targets
TEST_INPUT = test_input
TEST_MEMORY = test_memory

# Source files
TEST_INPUT_SRC = test_input.cpp
TEST_MEMORY_SRC = test_memory.cpp

# Header files
HEADERS = $(wildcard ../include/*.h)

# Mục tiêu mặc định
all: $(TEST_INPUT) $(TEST_MEMORY)

# Tạo thư mục bin nếu chưa có
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Biên dịch test input
$(TEST_INPUT): $(TEST_INPUT_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(TEST_INPUT) $(TEST_INPUT_SRC)

# Biên dịch test memory
$(TEST_MEMORY): $(TEST_MEMORY_SRC) $(HEADERS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(TEST_MEMORY) $(TEST_MEMORY_SRC)

# Chạy test input
run_input: $(TEST_INPUT)
	$(BIN_DIR)/$(TEST_INPUT)

# Chạy test memory
run_memory: $(TEST_MEMORY)
	$(BIN_DIR)/$(TEST_MEMORY)

# Chạy tất cả test
run_all: run_input run_memory

# Dọn dẹp
clean:
	rm -f $(BIN_DIR)/$(TEST_INPUT) $(BIN_DIR)/$(TEST_MEMORY)

# Hiển thị thông tin
info:
	@echo "=== TEST SUITE ==="
	@echo "Test Input: $(TEST_INPUT)"
	@echo "Test Memory: $(TEST_MEMORY)"
	@echo "Thư mục include: ../include"
	@echo "Thư mục bin: $(BIN_DIR)"
	@echo ""
	@echo "Lệnh biên dịch: make"
	@echo "Lệnh chạy test input: make run_input"
	@echo "Lệnh chạy test memory: make run_memory"
	@echo "Lệnh chạy tất cả: make run_all"
	@echo "Lệnh dọn dẹp: make clean"

# Trợ giúp
help:
	@echo "Các lệnh có sẵn:"
	@echo "  make         - Biên dịch tất cả test"
	@echo "  make run_input  - Chạy test input"
	@echo "  make run_memory - Chạy test memory"
	@echo "  make run_all    - Chạy tất cả test"
	@echo "  make clean   - Dọn dẹp file test"
	@echo "  make info    - Hiển thị thông tin"
	@echo "  make help    - Hiển thị trợ giúp"

.PHONY: all run_input run_memory run_all clean info help
