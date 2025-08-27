# Ứng Dụng Danh Bạ Điện Thoại

## Mô tả
Ứng dụng danh bạ điện thoại được viết bằng C++ với giao diện dòng lệnh (CLI) tương tác. Ứng dụng sử dụng cây tìm kiếm nhị phân (BST) để lưu trữ liên hệ và std::set để đảm bảo không có số điện thoại trùng lặp.

## Tính năng chính

### 1. Thêm liên hệ
- Nhập tên, số điện thoại và email (tùy chọn)
- Kiểm tra tính hợp lệ của dữ liệu đầu vào
- Ngăn chặn số điện thoại trùng lặp
- Hiển thị thông báo thành công/lỗi với màu sắc

### 2. Xóa liên hệ
- Tìm kiếm liên hệ theo tên
- Xóa liên hệ khỏi danh bạ
- Hiển thị thông báo xác nhận

### 3. Tìm kiếm liên hệ
- Tìm kiếm nhanh theo tên với độ phức tạp O(log n)
- Hiển thị thông tin chi tiết của liên hệ

### 4. Hiển thị tất cả liên hệ
- Duyệt cây theo thứ tự in-order
- Hiển thị danh sách theo thứ tự bảng chữ cái
- Hiển thị tổng số liên hệ

## Cấu trúc dự án

```
phonebook/
├── Contact.h              # Định nghĩa struct Contact và Factory Pattern
├── BSTNode.h              # Định nghĩa node cho BST
├── BinarySearchTree.h     # Triển khai cây tìm kiếm nhị phân
├── PhoneBook.h            # Lớp quản lý danh bạ với Singleton Pattern
├── UI.h                   # Xử lý giao diện người dùng
├── main.cpp               # Chương trình chính
├── Makefile               # File biên dịch
└── README.md              # Tài liệu hướng dẫn
```

## Design Patterns được sử dụng

### 1. Singleton Pattern
- **Lớp**: `PhoneBook`
- **Mục đích**: Đảm bảo chỉ có một instance duy nhất của danh bạ
- **Lợi ích**: Tiết kiệm bộ nhớ, quản lý trạng thái tập trung

### 2. Factory Pattern
- **Lớp**: `ContactFactory`
- **Mục đích**: Tạo các đối tượng Contact với validation
- **Lợi ích**: Tăng tính mở rộng, dễ bảo trì

## Cấu trúc dữ liệu

### 1. Binary Search Tree (BST)
- **Mục đích**: Lưu trữ liên hệ theo thứ tự tên
- **Độ phức tạp**: 
  - Tìm kiếm: O(log n) trung bình
  - Chèn: O(log n) trung bình
  - Xóa: O(log n) trung bình
- **Duyệt in-order**: Hiển thị theo thứ tự bảng chữ cái

### 2. std::set
- **Mục đích**: Kiểm tra trùng lặp số điện thoại
- **Độ phức tạp**: O(log n) cho kiểm tra và chèn
- **Lợi ích**: Đảm bảo tính duy nhất

## Giao diện người dùng

### Windows API
- **Xóa màn hình**: `system("cls")`
- **Màu sắc**: `SetConsoleTextAttribute()`
  - Đỏ: Thông báo lỗi
  - Xanh lá: Thông báo thành công
  - Vàng: Thông tin liên hệ
  - Xanh dương: Menu

### Tính năng tương tác
- Menu trực quan với số thứ tự
- Thông báo phản hồi tức thời
- Xử lý đầu vào không hợp lệ
- Giao diện thân thiện với người dùng

## Cách biên dịch và chạy

### Yêu cầu hệ thống
- Windows OS (vì sử dụng Windows API)
- GCC/G++ compiler
- Make (tùy chọn)

### Biên dịch
```bash
# Sử dụng Makefile (khuyến nghị)
make

# Hoặc biên dịch trực tiếp
g++ -std=c++11 -Wall -Wextra -pedantic -o phonebook main.cpp
```

### Chạy chương trình
```bash
# Sử dụng Makefile
make run

# Hoặc chạy trực tiếp
./phonebook.exe
```

## Xử lý ngoại lệ

### 1. Đầu vào không hợp lệ
- Tên trống hoặc chứa ký tự đặc biệt
- Số điện thoại không đúng định dạng
- Lựa chọn menu sai

### 2. Lỗi hệ thống
- Lỗi bộ nhớ
- Lỗi Windows API
- Exception chung

### 3. Trường hợp đặc biệt
- Danh bạ rỗng
- Số điện thoại trùng lặp
- Liên hệ không tồn tại

## Lý do sử dụng BST và std::set

### Binary Search Tree
- **Hiệu quả**: Tìm kiếm/chèn/xóa O(log n) trong trường hợp trung bình
- **Sắp xếp tự động**: Duyệt in-order cho thứ tự bảng chữ cái
- **Cân bằng**: Phù hợp cho ứng dụng nhỏ và vừa

### std::set
- **Tính duy nhất**: Tự động đảm bảo không trùng lặp
- **Hiệu quả**: Kiểm tra trùng lặp nhanh O(log n)
- **Đơn giản**: API dễ sử dụng và bảo trì

## Mở rộng tương lai

1. **Lưu trữ file**: Thêm tính năng lưu/đọc từ file
2. **Tìm kiếm nâng cao**: Tìm kiếm theo số điện thoại, email
3. **Phân loại liên hệ**: Nhóm liên hệ theo danh mục
4. **Giao diện đồ họa**: Chuyển sang GUI
5. **Cơ sở dữ liệu**: Sử dụng SQLite hoặc MySQL

## Tác giả
Ứng dụng được phát triển theo yêu cầu chi tiết trong file `promt` với việc áp dụng các design patterns và cấu trúc dữ liệu phù hợp.
