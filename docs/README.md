# Hệ Thống Quản Lý Danh Bạ Thông Minh - Hướng Dẫn Sử Dụng

## 🎯 Mô tả dự án
Hệ thống quản lý danh bạ được xây dựng bằng C++ với các cấu trúc dữ liệu tối ưu:
- **Binary Search Tree** cho việc sắp xếp theo tên và ID
- **Red-Black Tree** cho việc quản lý số điện thoại và email (đảm bảo cân bằng)

## 🚀 Cách chạy ứng dụng

### Yêu cầu hệ thống
- **OS**: Hệ điều hành sử dụng kernel Linux (Debian, RedHat, Ubuntu, CentOS, etc.)
- **Compiler**: GCC 7+ hoặc Clang 5+
- **C++ Standard**: C++17

### Cách 1: Sử dụng script tự động
```bash
# Cấp quyền thực thi
chmod +x chayungdung.sh

# Chạy ứng dụng
./chayungdung.sh
```

### Cách 2: Sử dụng Makefile
```bash
# Build và chạy
make run

# Hoặc build riêng
make build
./smart_contact_cli
```

### Cách 3: Compile thủ công
```bash
g++ -std=c++17 -Wall -Wextra -O2 \
    -I./include \
    src/main.cpp \
    src/Contact.cpp \
    src/ContactManager.cpp \
    src/ContactUI.cpp \
    -o smart_contact_cli

./smart_contact_cli
```

## 🌳 Cấu trúc dữ liệu mới

### Binary Search Tree (BST)
- **Sử dụng cho**: `contactsByName` và `contactsById`
- **Ưu điểm**: Sắp xếp tự động, tìm kiếm O(log n)
- **Ứng dụng**: Sắp xếp liên hệ theo tên và ID

### Red-Black Tree (RBT)
- **Sử dụng cho**: `contactsByPhone` và `contactsByEmail`
- **Ưu điểm**: Cân bằng tự động, đảm bảo độ cao O(log n)
- **Ứng dụng**: Quản lý số điện thoại và email với hiệu suất cao

## 🔍 Tính năng mới

### Hiển thị cấu trúc cây dữ liệu
Sử dụng tùy chọn **"6. 🔍 Hiển thị cấu trúc cây dữ liệu"** trong menu chính để:
- Xem cấu trúc BST theo tên
- Xem cấu trúc RBT theo số điện thoại
- Xem cấu trúc RBT theo email
- Xem cấu trúc BST theo ID

### Cải thiện hiệu suất
- **Thêm liên hệ**: O(log n) với BST/RBT
- **Tìm kiếm**: O(log n) với BST/RBT
- **Xóa liên hệ**: O(log n) với BST/RBT
- **Cân bằng**: RBT tự động cân bằng, BST có thể mất cân bằng

## 📁 Cấu trúc thư mục mới
```
├── src/                    # Source code (.cpp files)
├── include/                # Header files (.h files)  
├── docs/                   # Documentation (thư mục này)
├── build/                  # Build files
├── tests/                  # Test files
├── examples/               # Example usage
├── CMakeLists.txt          # CMake configuration
├── Makefile                # Main build script
└── chayungdung.sh          # Auto-compile script
```

## 🛠️ Troubleshooting

### Lỗi compile thường gặp
1. **"No such file or directory"**: Đảm bảo bạn đang ở thư mục gốc của dự án
2. **"Permission denied"**: Chạy `chmod +x chayungdung.sh`
3. **"g++: command not found"**: Cài đặt GCC compiler

### Kiểm tra cấu trúc
```bash
# Kiểm tra thư mục hiện tại
pwd

# Liệt kê các file và thư mục
ls -la

# Kiểm tra cấu trúc src/
ls -la src/

# Kiểm tra cấu trúc include/
ls -la include/
```

## 📝 Ghi chú quan trọng

- Dự án sử dụng **Singleton Pattern** cho ContactManager
- **Template Classes** cho BST và RBT để tái sử dụng
- **Exception Handling** cho validation và error management
- **Memory Management** với proper cleanup
- Các cấu trúc dữ liệu mới thay thế hoàn toàn `std::map` và `std::set`

