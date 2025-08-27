# Makefile cho ứng dụng Danh Bạ Điện Thoại
# Sử dụng g++ compiler

# Biến
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET = phonebook
DEMO_TARGET = exception_demo
ADVANCED_DEMO_TARGET = advanced_demo
SOURCES = main.cpp
DEMO_SOURCES = ExceptionDemo.cpp
ADVANCED_DEMO_SOURCES = AdvancedDemo.cpp
HEADERS = Contact.h BSTNode.h BinarySearchTree.h PhoneBook.h UI.h Exceptions.h ExceptionLogger.h ErrorHandler.h AdvancedValidator.h

# Mục tiêu mặc định
all: $(TARGET)

# Biên dịch chương trình
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Chạy chương trình
run: $(TARGET)
	./$(TARGET)

# Biên dịch và chạy demo exception
demo: $(DEMO_TARGET)
	./$(DEMO_TARGET)

# Biên dịch demo exception
$(DEMO_TARGET): $(DEMO_SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(DEMO_TARGET) $(DEMO_SOURCES)

# Biên dịch và chạy advanced demo
advanced: $(ADVANCED_DEMO_TARGET)
	./$(ADVANCED_DEMO_TARGET)

# Biên dịch advanced demo
$(ADVANCED_DEMO_TARGET): $(ADVANCED_DEMO_SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(ADVANCED_DEMO_TARGET) $(ADVANCED_DEMO_SOURCES)

# Dọn dẹp file biên dịch
clean:
	del /Q $(TARGET).exe $(DEMO_TARGET).exe $(ADVANCED_DEMO_TARGET).exe *.o 2>nul || echo "Đã dọn dẹp"

# Hiển thị thông tin
info:
	@echo "=== ỨNG DỤNG DANH BẠ ĐIỆN THOẠI ==="
	@echo "Tệp nguồn: $(SOURCES)"
	@echo "Tệp demo: $(DEMO_SOURCES)"
	@echo "Tệp advanced demo: $(ADVANCED_DEMO_SOURCES)"
	@echo "Tệp header: $(HEADERS)"
	@echo "Tệp thực thi: $(TARGET).exe"
	@echo "Tệp demo: $(DEMO_TARGET).exe"
	@echo "Tệp advanced demo: $(ADVANCED_DEMO_TARGET).exe"
	@echo ""
	@echo "Lệnh biên dịch: make"
	@echo "Lệnh chạy: make run"
	@echo "Lệnh demo: make demo"
	@echo "Lệnh advanced demo: make advanced"
	@echo "Lệnh dọn dẹp: make clean"

# Trợ giúp
help:
	@echo "Các lệnh có sẵn:"
	@echo "  make      - Biên dịch chương trình"
	@echo "  make run  - Chạy chương trình"
	@echo "  make demo - Chạy demo exception"
	@echo "  make advanced - Chạy advanced demo"
	@echo "  make clean- Dọn dẹp file biên dịch"
	@echo "  make info - Hiển thị thông tin"
	@echo "  make help - Hiển thị trợ giúp"

.PHONY: all run demo advanced clean info help
