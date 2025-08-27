# LUỒNG HOẠT ĐỘNG - HỆ THỐNG QUẢN LÝ DANH BẠ

## Tổng Quan Hệ Thống

Hệ thống Quản lý Danh bạ Thông minh được xây dựng theo kiến trúc **Singleton Pattern** với **3 lớp chính**:
- **ContactUI**: Giao diện người dùng và điều khiển luồng
- **ContactManager**: Quản lý dữ liệu và logic nghiệp vụ
- **Contact**: Đối tượng dữ liệu liên hệ

## Sơ Đồ Luồng Hoạt Động

```
┌─────────────────┐
│   Khởi động     │
│   main()        │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│  ContactUI      │
│  Constructor    │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ ContactManager  │
│ getInstance()   │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│   run()         │
│   Main Loop     │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│  Main Menu      │
└─────────┬───────┘
          │
          ▼
┌─────────────────────────────────────────────────────────┐
│                    LỰA CHỌN CHỨC NĂNG                  │
├─────────────────────────────────────────────────────────┤
│ 1. Thêm liên hệ    │ 2. Quản lý liên hệ               │
│ 3. Tìm kiếm        │ 4. Hiển thị tất cả               │
│ 5. Thống kê        │ 6. Thoát                          │
└─────────────────────────────────────────────────────────┘
```

## Chi Tiết Luồng Hoạt Động

### 1. Khởi Tạo Hệ Thống

```cpp
int main() {
    try {
        ContactUI app;        // Tạo UI instance
        app.run();            // Chạy vòng lặp chính
    } catch (...) {
        // Xử lý lỗi
    }
}
```

**Luồng khởi tạo:**
1. **ContactUI Constructor** → Tạo instance
2. **ContactManager::getInstance()** → Lấy singleton instance
3. **Khởi tạo các cấu trúc dữ liệu** (maps, sets)

### 2. Vòng Lặp Chính (Main Loop)

```cpp
void ContactUI::run() {
    showWelcome();
    
    do {
        showMainMenu();           // Hiển thị menu
        choice = getIntInput();   // Nhận input
        processChoice(choice);    // Xử lý lựa chọn
        pause();                  // Tạm dừng
        clearScreen();            // Xóa màn hình
    } while (choice != 6);       // Lặp cho đến khi thoát
}
```

### 3. Luồng Thêm Liên Hệ Mới

```
┌─────────────────┐
│  Chọn "Thêm"   │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Nhập tên liên hệ│
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ ContactManager  │
│ addContact()    │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Tạo Contact    │
│ object          │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Thêm vào các   │
│ indexes         │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Menu chi tiết   │
│ (SĐT, Email...)│
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Hoàn thành     │
└─────────────────┘
```

**Chi tiết:**
1. **Nhập tên liên hệ** → Validation
2. **ContactManager::addContact()** → Tạo Contact object
3. **Thêm vào indexes** → O(log n) insertion
4. **Menu chi tiết** → Thêm SĐT, Email, địa chỉ, ghi chú

### 4. Luồng Quản Lý Liên Hệ

```
┌─────────────────┐
│  Chọn "Quản lý"│
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Contact Menu    │
└─────────┬───────┘
          │
          ▼
┌─────────────────────────────────────────────────────────┐
│                    LỰA CHỌN QUẢN LÝ                    │
├─────────────────────────────────────────────────────────┤
│ 1. Chỉnh sửa    │ 2. Xóa liên hệ                      │
│ 3. Xem chi tiết │ 4. Thêm số điện thoại               │
│ 5. Thêm email   │ 6. Quay lại                          │
└─────────────────────────────────────────────────────────┘
```

**Các chức năng:**
- **Chỉnh sửa**: Sửa tên, địa chỉ, ghi chú
- **Xóa**: Xóa liên hệ và cập nhật indexes
- **Xem chi tiết**: Hiển thị đầy đủ thông tin
- **Thêm SĐT/Email**: Quản lý danh sách

### 5. Luồng Tìm Kiếm

```
┌─────────────────┐
│  Chọn "Tìm kiếm"│
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Search Menu     │
└─────────┬───────┘
          │
          ▼
┌─────────────────────────────────────────────────────────┐
│                    PHƯƠNG PHÁP TÌM KIẾM                │
├─────────────────────────────────────────────────────────┤
│ 1. Tìm theo tên │ 2. Tìm theo số điện thoại           │
│ 3. Tìm theo email│ 4. Quay lại                         │
└─────────────────────────────────────────────────────────┘
```

**Thuật toán tìm kiếm:**
- **Tìm theo tên**: O(log n) với map<string, Contact*>
- **Tìm theo SĐT**: O(log n) với map<string, Contact*>
- **Tìm theo Email**: O(log n) với map<string, Contact*>

### 6. Cấu Trúc Dữ Liệu và Hiệu Suất

```
ContactManager Data Structures:
├── contactsByName  : map<string, Contact*>  → O(log n) search
├── contactsByPhone : map<string, Contact*>  → O(log n) search  
├── contactsByEmail : map<string, Contact*>  → O(log n) search
└── contactsById    : map<int, Contact*>     → O(log n) search

Contact Object:
├── name           : string
├── phoneNumbers   : set<string>             → O(log n) operations
├── emails         : set<string>             → O(log n) operations
├── address        : string
├── notes          : string
└── id             : int (auto-increment)
```

**Độ phức tạp thời gian:**
- **Thêm liên hệ**: O(log n)
- **Tìm kiếm**: O(log n)
- **Xóa liên hệ**: O(log n)
- **Cập nhật**: O(log n)

### 7. Xử Lý Lỗi và Exception

```
Exception Handling Flow:
┌─────────────────┐
│   Operation     │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Validation      │
│ Check           │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Success Path    │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ ContactException│
│ (Custom Error)  │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Main Exception  │
│ Handler         │
└─────────────────┘
```

**Các loại exception:**
- **ContactException**: Lỗi nghiệp vụ (tên trống, SĐT không hợp lệ...)
- **Standard Exception**: Lỗi hệ thống
- **Unknown Exception**: Lỗi không xác định

### 8. Luồng Thoát và Dọn Dẹp

```
┌─────────────────┐
│  Chọn "Thoát"  │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ showGoodbye()   │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Destructor      │
│ ContactUI       │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Destructor      │
│ ContactManager  │
└─────────┬───────┘
          │
          ▼
┌─────────────────┐
│ Giải phóng      │
│ Memory          │
└─────────────────┘
```

## Đặc Điểm Kỹ Thuật

### 1. **Singleton Pattern**
- Đảm bảo chỉ có 1 instance của ContactManager
- Quản lý tài nguyên tập trung

### 2. **Multiple Indexes**
- Tối ưu tìm kiếm theo nhiều tiêu chí
- Cân bằng giữa tốc độ và bộ nhớ

### 3. **Exception Safety**
- Xử lý lỗi graceful
- Không crash hệ thống

### 4. **Memory Management**
- Tự động quản lý bộ nhớ
- Destructor cleanup

## Tối Ưu Hóa Hiệu Suất

1. **Cấu trúc dữ liệu**: Sử dụng map/set cho O(log n) operations
2. **Indexing**: Multiple indexes cho tìm kiếm nhanh
3. **Lazy loading**: Chỉ tải dữ liệu khi cần
4. **Batch operations**: Xử lý nhiều thao tác cùng lúc

## Kết Luận

Hệ thống được thiết kế với kiến trúc rõ ràng, luồng hoạt động logic và hiệu suất cao. Việc sử dụng các cấu trúc dữ liệu tối ưu và pattern thiết kế phù hợp giúp hệ thống có thể xử lý số lượng lớn liên hệ một cách hiệu quả.
