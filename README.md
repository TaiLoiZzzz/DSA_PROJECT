# Hệ Thống Quản Lý Danh Bạ Thông Minh

## 🎯 Mô tả dự án
Hệ thống quản lý danh bạ được xây dựng bằng C++ với các cấu trúc dữ liệu tối ưu:
- **Binary Search Tree** cho việc sắp xếp theo tên và ID
- **Red-Black Tree** cho việc quản lý số điện thoại và email (đảm bảo cân bằng)

## 🏗️ Cấu trúc thư mục
```
├── src/                    # Source code (.cpp files)
│   ├── main.cpp           # Entry point
│   ├── Contact.cpp        # Contact class implementation
│   ├── ContactManager.cpp # Main business logic
│   └── ContactUI.cpp      # User interface
├── include/                # Header files (.h files)
│   ├── Contact.h          # Contact class definition
│   ├── ContactManager.h   # Manager class definition
│   ├── ContactUI.h        # UI class definition
│   ├── ContactException.h # Exception handling
│   ├── BinarySearchTree.h # Custom BST implementation
│   └── RedBlackTree.h     # Custom RBT implementation
├── docs/                   # Documentation
│   ├── README.md          # This file
│   ├── UML_Documentation.md
│   └── Design_Patterns_Documentation.md
├── build/                  # Build files
│   └── Makefile           # Build configuration
├── tests/                  # Test files (future)
├── examples/               # Example usage (future)
├── CMakeLists.txt          # CMake configuration
└── Makefile                # Main build script
```

## 🚀 Cách sử dụng

### Build với Make
```bash
# Build từ thư mục gốc
make build

# Chạy ứng dụng
make run

# Dọn dẹp
make clean
```

### Build với CMake
```bash
mkdir build && cd build
cmake ..
make
```

## 🌳 Cấu trúc dữ liệu

### Binary Search Tree (BST)
- **Sử dụng cho**: `contactsByName` và `contactsById`
- **Ưu điểm**: Sắp xếp tự động, tìm kiếm O(log n)
- **Ứng dụng**: Sắp xếp liên hệ theo tên và ID

### Red-Black Tree (RBT)
- **Sử dụng cho**: `contactsByPhone` và `contactsByEmail`
- **Ưu điểm**: Cân bằng tự động, đảm bảo độ cao O(log n)
- **Ứng dụng**: Quản lý số điện thoại và email với hiệu suất cao

## 🔍 Tính năng chính

1. **Quản lý liên hệ**
   - Thêm, sửa, xóa liên hệ
   - Validation số điện thoại (tối đa 11 số)
   - Kiểm tra trùng lặp email và số điện thoại

2. **Tìm kiếm thông minh**
   - Tìm kiếm theo tên (không phân biệt hoa thường)
   - Tìm kiếm theo số điện thoại (hỗ trợ tìm kiếm một phần)
   - Tìm kiếm theo email (không phân biệt hoa thường)

3. **Hiển thị cấu trúc dữ liệu**
   - Xem cấu trúc BST và RBT
   - Debug và phân tích hiệu suất

## 📊 Hiệu suất

- **Thêm liên hệ**: O(log n)
- **Tìm kiếm**: O(log n)
- **Xóa liên hệ**: O(log n)
- **Duyệt tất cả**: O(n)

## 🛠️ Yêu cầu hệ thống

- **Compiler**: GCC 7+ hoặc Clang 5+
- **C++ Standard**: C++17
- **OS**: Linux, Windows, macOS

## 🔧 Debug và Monitoring

Sử dụng tùy chọn "🔍 Hiển thị cấu trúc cây dữ liệu" trong menu để:
- Xem cấu trúc BST theo tên
- Xem cấu trúc RBT theo số điện thoại
- Xem cấu trúc RBT theo email
- Xem cấu trúc BST theo ID

## 📝 Ghi chú

- Dự án sử dụng **Singleton Pattern** cho ContactManager
- **Template Classes** cho BST và RBT để tái sử dụng
- **Exception Handling** cho validation và error management
- **Memory Management** với smart pointers và proper cleanup
