# Hướng dẫn biên dịch và chạy ứng dụng Danh Bạ Điện Thoại trên Linux

## 🔍 **Vấn đề gặp phải**

### **Vấn đề 1: Windows API không tương thích**
Ứng dụng gốc được viết cho Windows và sử dụng:
- `#include <windows.h>` - Thư viện Windows API
- `system("chcp 65001")` - Lệnh Windows để thiết lập UTF-8
- Windows-specific console functions

### **Vấn đề 2: Buffer Input không được xử lý đúng cách**
**Nguyên nhân chính**: Khi sử dụng `cin >> choice` trong menu, ký tự xuống dòng `\n` không được đọc và còn lại trong buffer. Khi gọi `getline()` sau đó, nó sẽ đọc ngay `\n` và trả về chuỗi rỗng.

**Luồng lỗi**:
1. User nhập `1` + Enter
2. `cin >> choice` đọc `1` nhưng để lại `\n` trong buffer
3. `inputName()` gọi `getline(cin, name)` → đọc `\n` → `name = ""`
4. Validation thất bại → Exception

**Giải pháp**: Thêm `cin.ignore()` sau `cin >> choice` để xóa buffer input.

## ✅ **Giải pháp**
Đã tạo các file tương thích với Linux:
- `UI_linux.h` - Thay thế Windows API bằng ANSI escape codes
- `main_linux.cpp` - Loại bỏ Windows-specific code
- `Makefile.linux` - Makefile tương thích với Linux
- `build.sh` - Script bash tự động hóa

## 🚀 **Cách biên dịch và chạy**

### **Test luồng input trước khi chạy ứng dụng chính**
```bash
# Biên dịch file test
g++ -std=c++11 -Wall -Wextra -pedantic -o test_input test_input.cpp

# Chạy test
./test_input
```

**Kết quả mong đợi**:
- Nhập lựa chọn: `1`
- Nhập tên: `Nguyen Van A`
- Nhập số điện thoại: `0123456789`
- Nhập email: `test@example.com`

Nếu test này hoạt động bình thường, ứng dụng chính sẽ hoạt động tốt.

### **Test memory management**
```bash
# Biên dịch test memory
g++ -std=c++11 -Wall -Wextra -pedantic -o test_memory test_memory.cpp

# Chạy test
./test_memory
```

**Mục đích**: Kiểm tra copy constructor, assignment operator và memory leak.

### **Phương pháp 1: Sử dụng Makefile**
```bash
# Biên dịch tất cả
make -f Makefile.linux

# Chạy chương trình chính
make -f Makefile.linux run

# Chạy demo exception
make -f Makefile.linux demo

# Chạy advanced demo
make -f Makefile.linux advanced

# Dọn dẹp
make -f Makefile.linux clean
```

### **Phương pháp 2: Sử dụng script bash**
```bash
# Cấp quyền thực thi
chmod +x build.sh

# Chạy script
./build.sh
```

### **Phương pháp 3: Biên dịch thủ công**
```bash
# Biên dịch chương trình chính
g++ -std=c++11 -Wall -Wextra -pedantic -o phonebook main_linux.cpp

# Biên dịch demo exception
g++ -std=c++11 -Wall -Wextra -pedantic -o exception_demo ExceptionDemo.cpp

# Biên dịch advanced demo
g++ -std=c++11 -Wall -Wextra -pedantic -o advanced_demo AdvancedDemo.cpp

# Chạy chương trình
./phonebook
```

## 📋 **Yêu cầu hệ thống**
- **OS**: Linux (Ubuntu, Debian, CentOS, etc.)
- **Compiler**: g++ (GNU C++ Compiler)
- **Build tools**: build-essential

## 🔧 **Cài đặt dependencies**
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential

# CentOS/RHEL
sudo yum groupinstall "Development Tools"

# Fedora
sudo dnf groupinstall "Development Tools"
```

## 📁 **Cấu trúc file**
```
├── main_linux.cpp          # Main program (Linux compatible)
├── UI_linux.h             # UI class (Linux compatible)
├── Makefile.linux         # Makefile for Linux
├── build.sh               # Build script
├── Contact.h              # Contact class
├── BSTNode.h              # Binary Search Tree Node
├── BinarySearchTree.h     # Binary Search Tree implementation
├── PhoneBook.h            # PhoneBook class
├── Exceptions.h           # Exception classes
├── ExceptionLogger.h      # Exception logging
├── ErrorHandler.h         # Error handling
├── AdvancedValidator.h    # Advanced validation
├── ExceptionDemo.cpp      # Exception demo
└── AdvancedDemo.cpp       # Advanced demo
```

## 🎨 **Tính năng UI trên Linux**
- **Màu sắc**: Sử dụng ANSI escape codes
- **Xóa màn hình**: `\033[2J\033[H`
- **Màu chữ**: Đỏ, xanh lá, vàng, xanh dương
- **Tương thích**: Hoạt động trên hầu hết terminal Linux

## ⚠️ **Lưu ý quan trọng**
1. **Terminal support**: Đảm bảo terminal hỗ trợ ANSI escape codes
2. **UTF-8**: Linux mặc định hỗ trợ UTF-8, không cần thiết lập đặc biệt
3. **Permissions**: Đảm bảo file có quyền thực thi: `chmod +x build.sh`

## 🐛 **Xử lý lỗi thường gặp**

### **Lỗi: g++ not found**
```bash
sudo apt install build-essential
```

### **Lỗi: Permission denied**
```bash
chmod +x build.sh
```

### **Lỗi: ANSI colors not working**
- Kiểm tra terminal có hỗ trợ ANSI escape codes
- Thử terminal khác (gnome-terminal, xterm, etc.)

### **Lỗi: Không thể nhập tên/số điện thoại**
- **Nguyên nhân**: Buffer input không được xử lý đúng cách
- **Giải pháp**: Đảm bảo đã thêm `cin.ignore()` sau `cin >> choice` trong main
- **Test**: Chạy `test_input.cpp` để kiểm tra luồng input

## 📚 **Tài liệu tham khảo**
- [GNU Make Manual](https://www.gnu.org/software/make/manual/)
- [ANSI Escape Codes](https://en.wikipedia.org/wiki/ANSI_escape_code)
- [GCC Compiler Options](https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html)

## 🤝 **Hỗ trợ**
Nếu gặp vấn đề, hãy kiểm tra:
1. Phiên bản g++: `g++ --version`
2. Phiên bản make: `make --version`
3. Terminal type: `echo $TERM`
4. System locale: `locale`

---
**Phiên bản**: Linux Compatible v1.0  
**Cập nhật**: $(date)  
**Tác giả**: Hỗ trợ biên dịch thủ công
