# 📋 TÀI LIỆU THIẾT KẾ UML - HỆ THỐNG QUẢN LÝ DANH BẠ THÔNG MINH

## 🎯 TỔNG QUAN HỆ THỐNG

Hệ thống Quản lý Danh bạ Thông minh là một ứng dụng C++ được thiết kế theo mô hình **Singleton Pattern** và **MVC (Model-View-Controller)** với giao diện dòng lệnh (CLI). Hệ thống sử dụng các cấu trúc dữ liệu tối ưu để đảm bảo hiệu suất cao trong các thao tác tìm kiếm và quản lý liên hệ.

---

## 🏗️ KIẾN TRÚC TỔNG THỂ

```
┌─────────────────────────────────────────────────────────────┐
│                    MAIN APPLICATION                        │
├─────────────────────────────────────────────────────────────┤
│  main.cpp                                                  │
│  └── Khởi tạo ContactUI và xử lý exception toàn cục      │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    PRESENTATION LAYER                      │
├─────────────────────────────────────────────────────────────┤
│  ContactUI (View + Controller)                            │
│  ├── Giao diện người dùng                                 │
│  ├── Xử lý input/output                                   │
│  ├── Validation dữ liệu                                   │
│  └── Điều hướng người dùng                               │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                     BUSINESS LOGIC LAYER                   │
├─────────────────────────────────────────────────────────────┤
│  ContactManager (Singleton)                                │
│  ├── Quản lý dữ liệu liên hệ                              │
│  ├── Xử lý business logic                                 │
│  ├── Validation và kiểm tra trùng lặp                     │
│  └── Quản lý các index tìm kiếm                          │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                      DATA LAYER                           │
├─────────────────────────────────────────────────────────────┤
│  Contact (Model)                                           │
│  ├── Đại diện cho một liên hệ                             │
│  ├── Quản lý thông tin cá nhân                            │
│  └── Validation dữ liệu cơ bản                            │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   EXCEPTION HANDLING                      │
├─────────────────────────────────────────────────────────────┤
│  ContactException (Exception Hierarchy)                   │
│  ├── Xử lý lỗi chung                                      │
│  ├── Xử lý lỗi cụ thể                                     │
│  └── Thông báo lỗi thân thiện                             │
└─────────────────────────────────────────────────────────────┘
```

---

## 📊 SƠ ĐỒ LỚP (CLASS DIAGRAM)

### 1. LỚP CONTACT (MODEL)

```mermaid
classDiagram
    class Contact {
        -string name
        -string phoneNumber
        -string email
        -string address
        -string notes
        -int id
        -static int nextId
        
        +Contact()
        +Contact(string name)
        +int getId() const
        +string getName() const
        +string getPhoneNumber() const
        +string getEmail() const
        +string getAddress() const
        +string getNotes() const
        +void setName(string name)
        +void setPhoneNumber(string phone)
        +void setEmail(string email)
        +void setAddress(string address)
        +void setNotes(string notes)
        +bool hasPhoneNumber() const
        +bool hasEmail() const
        +void display() const
        +string toString() const
    }
```

**Mô tả chi tiết:**
- **Thuộc tính:**
  - `name`: Tên liên hệ (bắt buộc, duy nhất)
  - `phoneNumber`: Số điện thoại (tối đa 11 số, duy nhất)
  - `email`: Địa chỉ email (duy nhất, format chuẩn)
  - `address`: Địa chỉ (tùy chọn)
  - `notes`: Ghi chú (tùy chọn)
  - `id`: ID tự động tăng (duy nhất)
  - `nextId`: Biến static để quản lý ID

- **Phương thức chính:**
  - **Constructors**: Tạo liên hệ mới với ID tự động
  - **Getters/Setters**: Truy cập và cập nhật thông tin
  - **Validation**: Kiểm tra có số điện thoại/email không
  - **Display**: Hiển thị thông tin liên hệ
  - **toString**: Chuyển đổi thành chuỗi

### 2. LỚP CONTACTMANAGER (SINGLETON)

```mermaid
classDiagram
    class ContactManager {
        -static ContactManager* instance
        -map<string, Contact*> contactsByName
        -map<string, Contact*> contactsByPhone
        -map<string, Contact*> contactsByEmail
        -map<int, Contact*> contactsById
        
        -ContactManager()
        +static ContactManager* getInstance()
        +bool addContact(string name)
        +bool removeContact(int id)
        +bool removeContact(string name)
        +Contact* findContact(int id)
        +Contact* findContact(string name)
        +set<Contact*> searchByName(string name)
        +set<Contact*> searchByPhone(string phone)
        +set<Contact*> searchByEmail(string email)
        +void displayAllContacts() const
        +int getTotalContacts() const
        +bool isEmpty() const
        +void clearAll()
        +bool canAddPhoneNumber(string phone, Contact* exclude)
        +bool canAddEmail(string email, Contact* exclude)
        +bool isPhoneNumberDuplicate(string phone, Contact* exclude)
        +bool isEmailDuplicate(string email, Contact* exclude)
        +bool isValidPhone(string phone)
        +bool isValidEmail(string email)
        -void removeFromIndexes(Contact* contact)
        -void addToIndexes(Contact* contact)
        -void updatePhoneIndex(Contact* contact, string oldPhone, string newPhone)
        -void updateEmailIndex(Contact* contact, string oldEmail, string newEmail)
        -void syncAllIndexes(Contact* contact)
    }
```

**Mô tả chi tiết:**
- **Design Pattern:** Singleton - Đảm bảo chỉ có một instance duy nhất
- **Cấu trúc dữ liệu:**
  - `contactsByName`: Map tên → Contact (O(log n) tìm kiếm)
  - `contactsByPhone`: Map số điện thoại → Contact (O(log n) tìm kiếm)
  - `contactsByEmail`: Map email → Contact (O(log n) tìm kiếm)
  - `contactsById`: Map ID → Contact (O(log n) tìm kiếm)

- **Chức năng chính:**
  - **CRUD Operations**: Thêm, xóa, tìm kiếm, hiển thị liên hệ
  - **Index Management**: Quản lý các index để tối ưu tìm kiếm
  - **Validation**: Kiểm tra tính hợp lệ và trùng lặp
  - **Search**: Tìm kiếm theo nhiều tiêu chí khác nhau

### 3. LỚP CONTACTUI (VIEW + CONTROLLER)

```mermaid
classDiagram
    class ContactUI {
        -ContactManager* manager
        
        +ContactUI()
        +~ContactUI()
        +void run()
        +void showWelcome() const
        +void showGoodbye() const
        -void showMainMenu() const
        -void showContactMenu() const
        -void showSearchMenu() const
        -void addContact() const
        -void editContact() const
        -void deleteContact() const
        -void viewContact() const
        -void searchContacts() const
        -void displayAllContacts() const
        -string getStringInput(string prompt) const
        -int getIntInput(string prompt) const
        -void clearScreen() const
        -void pause() const
        -bool isValidPhoneNumber(string phone) const
        -bool isValidEmail(string email) const
    }
```

**Mô tả chi tiết:**
- **Vai trò:** Kết hợp View và Controller trong mô hình MVC
- **Chức năng:**
  - **User Interface**: Hiển thị menu và nhận input từ người dùng
  - **Input Validation**: Kiểm tra tính hợp lệ của dữ liệu đầu vào
  - **Navigation**: Điều hướng giữa các menu và chức năng
  - **Display**: Hiển thị kết quả và thông báo cho người dùng

### 4. LỚP CONTACTEXCEPTION (EXCEPTION HIERARCHY)

```mermaid
classDiagram
    exception <|-- ContactException
    ContactException <|-- ContactNotFound
    ContactException <|-- ContactAlreadyExists
    ContactException <|-- InvalidInput
    ContactException <|-- EmptyInput
    
    class exception {
        <<abstract>>
        +virtual const char* what() const noexcept
    }
    
    class ContactException {
        -string message
        +ContactException(string msg)
        +virtual const char* what() const noexcept override
    }
    
    class ContactNotFound {
        +ContactNotFound(string name)
    }
    
    class ContactAlreadyExists {
        +ContactAlreadyExists(string name)
    }
    
    class InvalidInput {
        +InvalidInput(string field)
    }
    
    class EmptyInput {
        +EmptyInput(string field)
    }
```

**Mô tả chi tiết:**
- **Kế thừa từ:** `std::exception` (C++ standard library)
- **Các loại exception:**
  - `ContactNotFound`: Liên hệ không tồn tại
  - `ContactAlreadyExists`: Liên hệ đã tồn tại
  - `InvalidInput`: Dữ liệu đầu vào không hợp lệ
  - `EmptyInput`: Trường dữ liệu bị để trống

---

## 🔄 SƠ ĐỒ TUẦN TỰ (SEQUENCE DIAGRAM)

### 1. LUỒNG THÊM LIÊN HỆ MỚI

```mermaid
sequenceDiagram
    participant User
    participant ContactUI
    participant ContactManager
    participant Contact
    participant ExceptionHandler
    
    User->>ContactUI: Chọn "Thêm liên hệ mới"
    ContactUI->>User: Yêu cầu nhập tên
    User->>ContactUI: Nhập tên liên hệ
    ContactUI->>ContactManager: addContact(name)
    
    alt Tên hợp lệ và không trùng lặp
        ContactManager->>Contact: new Contact(name)
        Contact-->>ContactManager: Contact* contact
        ContactManager->>ContactManager: addToIndexes(contact)
        ContactManager-->>ContactUI: true
        ContactUI->>User: Hiển thị menu thêm chi tiết
        User->>ContactUI: Chọn thêm số điện thoại
        ContactUI->>User: Yêu cầu nhập số điện thoại
        User->>ContactUI: Nhập số điện thoại
        ContactUI->>ContactManager: canAddPhoneNumber(phone)
        ContactManager-->>ContactUI: true
        ContactUI->>Contact: setPhoneNumber(phone)
        ContactUI->>ContactManager: syncAllIndexes(contact)
        ContactUI-->>User: Thông báo thành công
    else Tên không hợp lệ hoặc trùng lặp
        ContactManager->>ExceptionHandler: Throw exception
        ExceptionHandler-->>ContactUI: Exception message
        ContactUI-->>User: Hiển thị lỗi
    end
```

### 2. LUỒNG TÌM KIẾM LIÊN HỆ

```mermaid
sequenceDiagram
    participant User
    participant ContactUI
    participant ContactManager
    participant SearchIndexes
    
    User->>ContactUI: Chọn "Tìm kiếm liên hệ"
    ContactUI->>User: Hiển thị menu tìm kiếm
    User->>ContactUI: Chọn loại tìm kiếm
    ContactUI->>User: Yêu cầu nhập từ khóa
    
    alt Tìm kiếm theo tên
        User->>ContactUI: Nhập tên
        ContactUI->>ContactManager: searchByName(name)
        ContactManager->>SearchIndexes: Tìm trong contactsByName
        SearchIndexes-->>ContactManager: set<Contact*> results
        ContactManager-->>ContactUI: results
        ContactUI->>User: Hiển thị kết quả
    else Tìm kiếm theo số điện thoại
        User->>ContactUI: Nhập số điện thoại
        ContactUI->>ContactManager: searchByPhone(phone)
        ContactManager->>SearchIndexes: Tìm trong contactsByPhone
        SearchIndexes-->>ContactManager: set<Contact*> results
        ContactManager-->>ContactUI: results
        ContactUI->>User: Hiển thị kết quả
    else Tìm kiếm theo email
        User->>ContactUI: Nhập email
        ContactUI->>ContactManager: searchByEmail(email)
        ContactManager->>SearchIndexes: Tìm trong contactsByEmail
        SearchIndexes-->>ContactManager: set<Contact*> results
        ContactManager-->>ContactUI: results
        ContactUI->>User: Hiển thị kết quả
    end
```

---

## 🗂️ SƠ ĐỒ CẤU TRÚC DỮ LIỆU (DATA STRUCTURE DIAGRAM)

### 1. CẤU TRÚC INDEX TỐI ƯU

```
┌─────────────────────────────────────────────────────────────┐
│                    CONTACT MANAGER                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────────┐    ┌─────────────────┐               │
│  │ contactsByName  │    │ contactsById    │               │
│  │ (map<string,    │    │ (map<int,       │               │
│  │  Contact*>)     │    │  Contact*>)     │               │
│  │                 │    │                 │               │
│  │ "Nguyễn Văn A" │    │ 1 → Contact*    │               │
│  │ "Trần Thị B"   │    │ 2 → Contact*    │               │
│  │ "Lê Văn C"     │    │ 3 → Contact*    │               │
│  └─────────────────┘    └─────────────────┘               │
│           │                       │                       │
│           ▼                       ▼                       │
│  ┌─────────────────┐    ┌─────────────────┐               │
│  │ contactsByPhone │    │ contactsByEmail │               │
│  │ (map<string,    │    │ (map<string,    │               │
│  │  Contact*>)     │    │  Contact*>)     │               │
│  │                 │    │                 │               │
│  │ "0123456789"    │    │ "a@email.com"   │               │
│  │ "0987654321"    │    │ "b@email.com"   │               │
│  │ "1122334455"    │    │ "c@email.com"   │               │
│  └─────────────────┘    └─────────────────┘               │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

**Ưu điểm của cấu trúc index:**
- **Tìm kiếm theo tên:** O(log n) thay vì O(n)
- **Tìm kiếm theo số điện thoại:** O(log n) thay vì O(n)
- **Tìm kiếm theo email:** O(log n) thay vì O(n)
- **Tìm kiếm theo ID:** O(log n) thay vì O(n)
- **Đảm bảo tính duy nhất:** Không có số điện thoại/email trùng lặp

### 2. CẤU TRÚC DỮ LIỆU LIÊN HỆ

```
┌─────────────────────────────────────────────────────────────┐
│                        CONTACT                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐        │
│  │     ID      │  │    Name     │  │   Phone     │        │
│  │   (int)     │  │  (string)   │  │  (string)   │        │
│  │   Auto      │  │  Required   │  │ Max 11      │        │
│  │  Increment  │  │  Unique     │  │  Unique     │        │
│  └─────────────┘  └─────────────┘  └─────────────┘        │
│                                                             │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐        │
│  │    Email    │  │   Address   │  │    Notes    │        │
│  │  (string)   │  │  (string)   │  │  (string)   │        │
│  │   Unique    │  │  Optional   │  │  Optional   │        │
│  │   Format    │  │             │  │             │        │
│  └─────────────┘  └─────────────┘  └─────────────┘        │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## 🔍 SƠ ĐỒ LUỒNG XỬ LÝ (FLOWCHART)

### 1. LUỒNG XỬ LÝ CHÍNH

```mermaid
flowchart TD
    A[Khởi động ứng dụng] --> B[Hiển thị màn hình chào]
    B --> C[Hiển thị menu chính]
    C --> D{Chọn chức năng}
    
    D -->|1| E[Thêm liên hệ mới]
    D -->|2| F[Quản lý liên hệ]
    D -->|3| G[Tìm kiếm liên hệ]
    D -->|4| H[Hiển thị tất cả]
    D -->|5| I[Thống kê]
    D -->|6| J[Thoát]
    
    E --> K[Kiểm tra tên hợp lệ]
    K -->|Không| L[Hiển thị lỗi]
    K -->|Có| M[Kiểm tra trùng lặp]
    M -->|Trùng| N[Hiển thị lỗi]
    M -->|Không| O[Tạo liên hệ mới]
    O --> P[Hiển thị menu thêm chi tiết]
    
    F --> Q[Hiển thị menu quản lý]
    Q --> R{Chọn thao tác}
    R -->|1| S[Chỉnh sửa]
    R -->|2| T[Xóa]
    R -->|3| U[Xem chi tiết]
    
    G --> V[Hiển thị menu tìm kiếm]
    V --> W{Chọn loại tìm kiếm}
    W -->|1| X[Tìm theo tên]
    W -->|2| Y[Tìm theo số điện thoại]
    W -->|3| Z[Tìm theo email]
    
    L --> C
    N --> C
    P --> C
    S --> C
    T --> C
    U --> C
    X --> C
    Y --> C
    Z --> C
    H --> C
    I --> C
    J --> AA[Kết thúc]
```

### 2. LUỒNG VALIDATION DỮ LIỆU

```mermaid
flowchart TD
    A[Nhập dữ liệu] --> B{Kiểm tra rỗng}
    B --> C[Hiển thị lỗi "Không được để trống"]
    B --> D{Kiểm tra loại dữ liệu}
    
    D --> E{Độ dài >= 2 ký tự}
    D --> F{Độ dài <= 11 và chỉ chứa số}
    D --> G{Kiểm tra format email}
    D --> H{Độ dài >= 5 ký tự}
    
    E --> I[Hiển thị lỗi "Tên phải >= 2 ký tự"]
    E --> J[Kiểm tra trùng lặp]
    
    F --> K[Hiển thị lỗi "Số điện thoại không hợp lệ"]
    F --> L[Kiểm tra trùng lặp]
    
    G --> M[Hiển thị lỗi "Email không hợp lệ"]
    G --> N[Kiểm tra trùng lặp]
    
    H --> O[Hiển thị lỗi "Địa chỉ phải >= 5 ký tự"]
    H --> P[Dữ liệu hợp lệ]
    
    J --> Q[Hiển thị lỗi "Đã tồn tại"]
    J --> P
    
    L --> R[Hiển thị lỗi "Số điện thoại đã tồn tại"]
    L --> P
    
    N --> S[Hiển thị lỗi "Email đã tồn tại"]
    N --> P
    
    C --> T[Yêu cầu nhập lại]
    I --> T
    K --> T
    M --> T
    O --> T
    Q --> T
    R --> T
    S --> T
    
    P --> U[Lưu dữ liệu]
    T --> A
```

---

## 🎨 SƠ ĐỒ TRẠNG THÁI (STATE DIAGRAM)

### 1. TRẠNG THÁI LIÊN HỆ

```mermaid
stateDiagram-v2
    [*] --> Empty: Khởi tạo
    Empty --> Basic: Thêm tên
    Basic --> WithPhone: Thêm số điện thoại
    Basic --> WithEmail: Thêm email
    Basic --> WithAddress: Thêm địa chỉ
    Basic --> WithNotes: Thêm ghi chú
    Basic --> Complete: Thêm đầy đủ thông tin
    
    WithPhone --> WithPhone: Cập nhật số điện thoại
    WithPhone --> WithEmail: Thêm email
    WithPhone --> WithAddress: Thêm địa chỉ
    WithPhone --> WithNotes: Thêm ghi chú
    WithPhone --> Complete: Thêm đầy đủ thông tin
    
    WithEmail --> WithPhone: Thêm số điện thoại
    WithEmail --> WithEmail: Cập nhật email
    WithEmail --> WithAddress: Thêm địa chỉ
    WithEmail --> WithNotes: Thêm ghi chú
    WithEmail --> Complete: Thêm đầy đủ thông tin
    
    WithAddress --> WithPhone: Thêm số điện thoại
    WithAddress --> WithEmail: Thêm email
    WithAddress --> WithAddress: Cập nhật địa chỉ
    WithAddress --> WithNotes: Thêm ghi chú
    WithAddress --> Complete: Thêm đầy đủ thông tin
    
    WithNotes --> WithPhone: Thêm số điện thoại
    WithNotes --> WithEmail: Thêm email
    WithNotes --> WithAddress: Thêm địa chỉ
    WithNotes --> WithNotes: Cập nhật ghi chú
    WithNotes --> Complete: Thêm đầy đủ thông tin
    
    Complete --> Complete: Cập nhật bất kỳ thông tin
    Complete --> [*]: Xóa liên hệ
```

### 2. TRẠNG THÁI ỨNG DỤNG

```mermaid
stateDiagram-v2
    [*] --> Welcome: Khởi động
    Welcome --> MainMenu: Hiển thị menu chính
    MainMenu --> AddContact: Chọn thêm liên hệ
    MainMenu --> ManageContact: Chọn quản lý
    MainMenu --> SearchContact: Chọn tìm kiếm
    MainMenu --> DisplayAll: Chọn hiển thị tất cả
    MainMenu --> Statistics: Chọn thống kê
    MainMenu --> Exit: Chọn thoát
    
    AddContact --> AddDetails: Thêm tên thành công
    AddDetails --> AddDetails: Thêm thông tin chi tiết
    AddDetails --> MainMenu: Hoàn tất
    
    ManageContact --> ManageMenu: Hiển thị menu quản lý
    ManageMenu --> EditContact: Chọn chỉnh sửa
    ManageMenu --> DeleteContact: Chọn xóa
    ManageMenu --> ViewContact: Chọn xem chi tiết
    ManageMenu --> MainMenu: Quay lại
    
    EditContact --> EditMenu: Hiển thị menu chỉnh sửa
    EditMenu --> EditMenu: Chỉnh sửa thông tin
    EditMenu --> ManageMenu: Hoàn tất
    
    SearchContact --> SearchMenu: Hiển thị menu tìm kiếm
    SearchMenu --> SearchByName: Tìm theo tên
    SearchMenu --> SearchByPhone: Tìm theo số điện thoại
    SearchMenu --> SearchByEmail: Tìm theo email
    SearchMenu --> MainMenu: Quay lại
    
    DisplayAll --> MainMenu: Hiển thị xong
    Statistics --> MainMenu: Hiển thị xong
    
    Exit --> [*]: Kết thúc ứng dụng
```

---

## 🔧 SƠ ĐỒ COMPONENT (COMPONENT DIAGRAM)

```mermaid
graph TB
    subgraph "Hệ thống Quản lý Danh bạ"
        subgraph "Presentation Layer"
            UI[ContactUI]
        end
        
        subgraph "Business Logic Layer"
            CM[ContactManager]
        end
        
        subgraph "Data Layer"
            C[Contact]
        end
        
        subgraph "Exception Handling"
            EX[ContactException]
        end
        
        subgraph "Main Application"
            MAIN[main.cpp]
        end
    end
    
    subgraph "External Dependencies"
        STL[Standard Template Library]
        IO[iostream]
        STRING[string]
        MAP[map]
        SET[set]
        REGEX[regex]
    end
    
    MAIN --> UI
    UI --> CM
    CM --> C
    CM --> EX
    UI --> EX
    
    C --> STL
    CM --> STL
    UI --> IO
    CM --> IO
    CM --> STRING
    CM --> MAP
    CM --> SET
    CM --> REGEX
```

---

## 📈 SƠ ĐỒ HOẠT ĐỘNG (ACTIVITY DIAGRAM)

### 1. HOẠT ĐỘNG THÊM LIÊN HỆ

```mermaid
graph TD
    A[Bắt đầu] --> B[Nhập tên liên hệ]
    B --> C{Kiểm tra tên rỗng?}
    C -->|Có| D[Hiển thị lỗi]
    C -->|Không| E{Kiểm tra độ dài tên}
    E -->|Không đủ| F[Hiển thị lỗi]
    E -->|Đủ| G{Kiểm tra trùng lặp}
    G -->|Trùng| H[Hiển thị lỗi]
    G -->|Không| I[Tạo liên hệ mới]
    I --> J[Thêm vào index]
    J --> K[Hiển thị menu thêm chi tiết]
    K --> L{Chọn thêm thông tin?}
    L -->|Có| M[Thêm thông tin]
    L -->|Không| N[Hoàn tất]
    M --> L
    N --> O[Kết thúc]
    D --> B
    F --> B
    H --> B
```

### 2. HOẠT ĐỘNG TÌM KIẾM

```mermaid
graph TD
    A[Bắt đầu tìm kiếm] --> B{Chọn loại tìm kiếm}
    B -->|Theo tên| C[Nhập tên cần tìm]
    B -->|Theo số điện thoại| D[Nhập số điện thoại]
    B -->|Theo email| E[Nhập email]
    
    C --> F[Tìm kiếm trong index tên]
    D --> G[Tìm kiếm trong index số điện thoại]
    E --> H[Tìm kiếm trong index email]
    
    F --> I{Đã tìm thấy?}
    G --> I
    H --> I
    
    I -->|Có| J[Hiển thị kết quả]
    I -->|Không| K[Hiển thị "Không tìm thấy"]
    
    J --> L[Kết thúc]
    K --> L
```

---

## 🚀 TÍNH NĂNG VÀ ƯU ĐIỂM

### 1. **TÍNH NĂNG CHÍNH**
- ✅ **Quản lý liên hệ hoàn chỉnh**: Thêm, sửa, xóa, xem liên hệ
- ✅ **Tìm kiếm đa tiêu chí**: Theo tên, số điện thoại, email
- ✅ **Validation dữ liệu**: Kiểm tra tính hợp lệ và trùng lặp
- ✅ **Giao diện thân thiện**: Menu rõ ràng, thông báo chi tiết
- ✅ **Xử lý lỗi tốt**: Exception handling toàn diện

### 2. **ƯU ĐIỂM THIẾT KẾ**
- 🚀 **Hiệu suất cao**: Sử dụng map/set cho O(log n) operations
- 🏗️ **Kiến trúc rõ ràng**: Tách biệt các layer rõ ràng
- 🔒 **An toàn dữ liệu**: Kiểm tra trùng lặp và validation
- 📱 **Dễ mở rộng**: Có thể thêm tính năng mới dễ dàng
- 🧪 **Dễ test**: Các class độc lập, dễ viết unit test

### 3. **TỐI ƯU HÓA**
- **Index Management**: Quản lý index thông minh để tìm kiếm nhanh
- **Memory Management**: Sử dụng con trỏ và quản lý bộ nhớ hiệu quả
- **Exception Safety**: Xử lý exception an toàn, không bị crash
- **User Experience**: Giao diện thân thiện, thông báo rõ ràng

---

## 🔍 PHÂN TÍCH ĐỘ PHỨC TẠP

### 1. **TIME COMPLEXITY**
- **Thêm liên hệ**: O(log n) - do insert vào map
- **Xóa liên hệ**: O(log n) - do delete từ map
- **Tìm kiếm theo ID**: O(log n) - do search trong map
- **Tìm kiếm theo tên**: O(log n) - do search trong map
- **Tìm kiếm theo số điện thoại**: O(log n) - do search trong map
- **Tìm kiếm theo email**: O(log n) - do search trong map
- **Hiển thị tất cả**: O(n) - do phải duyệt qua tất cả

### 2. **SPACE COMPLEXITY**
- **Lưu trữ liên hệ**: O(n) - n là số lượng liên hệ
- **Index structures**: O(n) - mỗi index chứa n phần tử
- **Tổng bộ nhớ**: O(n) - tuyến tính với số lượng liên hệ

---

## 🛠️ HƯỚNG DẪN SỬ DỤNG

### 1. **BIÊN DỊCH VÀ CHẠY**
```bash
# Biên dịch
make

# Chạy ứng dụng
make run

# Dọn dẹp
make clean
```

### 2. **CÁC LỆNH CHÍNH**
- **1**: Thêm liên hệ mới
- **2**: Quản lý liên hệ (sửa, xóa, xem)
- **3**: Tìm kiếm liên hệ
- **4**: Hiển thị tất cả liên hệ
- **5**: Thống kê
- **6**: Thoát

### 3. **QUY TẮC SỬ DỤNG**
- **Tên liên hệ**: Bắt buộc, duy nhất, tối thiểu 2 ký tự
- **Số điện thoại**: Tối đa 11 số, duy nhất, chỉ chứa số
- **Email**: Format chuẩn, duy nhất
- **Địa chỉ**: Tối thiểu 5 ký tự
- **Ghi chú**: Tùy chọn

---

## 🔮 HƯỚNG PHÁT TRIỂN TƯƠNG LAI

### 1. **TÍNH NĂNG MỚI**
- 📁 **Lưu trữ file**: Import/export CSV, JSON
- 🔐 **Mã hóa dữ liệu**: Bảo mật thông tin liên hệ
- 🌐 **Giao diện web**: Web interface cho ứng dụng
- 📱 **Mobile app**: Ứng dụng di động
- ☁️ **Cloud sync**: Đồng bộ đa thiết bị

### 2. **CẢI TIẾN KỸ THUẬT**
- 🗄️ **Database**: Sử dụng SQLite hoặc PostgreSQL
- 🔍 **Full-text search**: Tìm kiếm nâng cao
- 📊 **Analytics**: Thống kê và báo cáo chi tiết
- 🔄 **API**: RESTful API cho tích hợp
- 🧪 **Testing**: Unit tests và integration tests

---

## 📝 KẾT LUẬN

Hệ thống Quản lý Danh bạ Thông minh được thiết kế với kiến trúc rõ ràng, hiệu suất cao và dễ sử dụng. Sử dụng các design pattern phù hợp và cấu trúc dữ liệu tối ưu, hệ thống có thể xử lý số lượng lớn liên hệ một cách hiệu quả.

**Điểm mạnh:**
- ✅ Kiến trúc rõ ràng, dễ bảo trì
- ✅ Hiệu suất cao với index tối ưu
- ✅ Xử lý lỗi toàn diện
- ✅ Giao diện thân thiện người dùng
- ✅ Dễ mở rộng và phát triển

**Hướng phát triển:**
- 🚀 Tích hợp database
- 🌐 Phát triển giao diện web
- 📱 Xây dựng mobile app
- 🔐 Bảo mật dữ liệu
- 📊 Báo cáo và thống kê nâng cao

Hệ thống này là một nền tảng vững chắc để xây dựng các ứng dụng quản lý liên hệ chuyên nghiệp trong tương lai.
