# 📊 TÀI LIỆU UML CHUẨN - HỆ THỐNG QUẢN LÝ DANH BẠ THÔNG MINH

## 🎯 TỔNG QUAN HỆ THỐNG

Hệ thống Quản lý Danh bạ Thông minh được thiết kế theo **Kiến trúc C++ Hiện đại** với việc áp dụng nhiều design patterns khác nhau. Tài liệu UML này tuân thủ chuẩn **UML 2.5** và cung cấp cái nhìn toàn diện về kiến trúc hệ thống.

---

## 🏗️ KIẾN TRÚC TỔNG THỂ (KIẾN TRÚC HỆ THỐNG)

### **1. 🎯 SƠ ĐỒ KIẾN TRÚC CẤP CAO**

```mermaid
graph TB
    subgraph "Tầng Ứng dụng"
        MAIN[main.cpp]
        UI[ContactUI]
    end
    
    subgraph "Tầng Logic Nghiệp vụ"
        CM[ContactManager<br/>Singleton]
    end
    
    subgraph "Tầng Cấu trúc Dữ liệu"
        BST[Cây Tìm kiếm Nhị phân]
        RBT[Cây Đỏ-Đen]
    end
    
    subgraph "Tầng Thực thể"
        CONTACT[Liên hệ]
    end
    
    subgraph "Tầng Xử lý Ngoại lệ"
        EX[ContactException]
    end
    
    MAIN --> UI
    UI --> CM
    CM --> BST
    CM --> RBT
    CM --> CONTACT
    CM --> EX
    UI --> EX
    
    style MAIN fill:#e1f5fe
    style UI fill:#f3e5f5
    style CM fill:#e8f5e8
    style BST fill:#fff3e0
    style RBT fill:#fff3e0
    style CONTACT fill:#fce4ec
    style EX fill:#ffebee
```

### **2. 📱 MA TRẬN TRÁCH NHIỆM CÁC TẦNG**

| Tầng | Thành phần | Trách nhiệm | Design Pattern |
|-------|------------|----------------|----------------|
| **Ứng dụng** | `main.cpp` | Điểm khởi đầu, Xử lý ngoại lệ toàn cục | Exception Handler |
| **Giao diện** | `ContactUI` | Giao diện người dùng, Kiểm tra đầu vào, Điều hướng | MVC (View+Controller) |
| **Logic Nghiệp vụ** | `ContactManager` | Quy tắc nghiệp vụ, Quản lý dữ liệu, Đồng bộ chỉ mục | Singleton, Factory, Observer |
| **Cấu trúc Dữ liệu** | `BST`, `RBT` | Lưu trữ dữ liệu, Tối ưu hóa tìm kiếm | Template Method, Strategy |
| **Thực thể** | `Contact` | Mô hình dữ liệu, Xác thực | Value Object |
| **Xử lý Ngoại lệ** | `ContactException` | Xử lý lỗi, Phản hồi người dùng | Exception Hierarchy |

---

## 📊 SƠ ĐỒ LỚP (CHUẨN UML 2.5)

### **1. 🏠 LỚP THỰC THỂ LIÊN HỆ**

```mermaid
classDiagram
    class Contact {
        <<Thực thể>>
        -string name
        -string phoneNumber
        -string email
        -string address
        -string notes
        -int id
        -static int nextId
        
        +Contact()
        +Contact(string name)
        +~Contact()
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
    
    note for Contact "Mẫu Value Object\n- ID không thay đổi\n- Quy tắc xác thực\n- Logic nghiệp vụ"
```

**Ký hiệu UML:**
- **<<Thực thể>>**: Stereotype cho lớp thực thể
- **-**: Thành viên riêng tư (encapsulation)
- **+**: Phương thức công khai (interface)
- **~**: Destructor
- **static**: Thành viên cấp lớp

### **2. 🎯 QUẢN LÝ LIÊN HỆ (SINGLETON)**

```mermaid
classDiagram
    class ContactManager {
        <<Singleton>>
        -static ContactManager* instance
        -BinarySearchTree<string, Contact*> contactsByName
        -RedBlackTree<string, Contact*> contactsByPhone
        -RedBlackTree<string, Contact*> contactsByEmail
        -BinarySearchTree<int, Contact*> contactsById
        
        -ContactManager()
        +static ContactManager* getInstance()
        +~ContactManager()
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
    
    note for ContactManager "Mẫu Singleton\n- Một thể hiện duy nhất\n- Truy cập toàn cục\n- Khởi tạo trễ"
```

### **3. 🖥️ GIAO DIỆN NGƯỜI DÙNG (MVC PATTERN)**

```mermaid
classDiagram
    class ContactUI {
        <<View+Controller>>
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
    
    note for ContactUI "Mẫu MVC\n- View: Các phương thức hiển thị\n- Controller: Xử lý đầu vào\n- Logic điều hướng"
```

### **4. 🌳 CÂY TÌM KIẾM NHỊ PHÂN (TEMPLATE CLASS)**

```mermaid
classDiagram
    class BinarySearchTree {
        <<Template>>
        <<DataStructure>>
        -Node* root
        -size_t size_
        
        +BinarySearchTree()
        +~BinarySearchTree()
        +void insert(K key, V value)
        +V* find(K key)
        +const V* find(K key) const
        +bool remove(K key)
        +bool contains(K key) const
        +size_t size() const
        +bool empty() const
        +void clear()
        +void print() const
        +void traverseInorder(function callback) const
        +void traversePreorder(function callback) const
        +void traversePostorder(function callback) const
        +void searchPartial(K partialKey, function matchFunc, function callback) const
        +void searchRange(K startKey, K endKey, function callback) const
        +void forEach(function callback) const
        +void forEachReverse(function callback) const
        +int getHeight() const
        +bool isBalanced() const
        -Node* insertRecursive(Node* node, K key, V value)
        -Node* findRecursive(Node* node, K key) const
        -Node* removeRecursive(Node* node, K key)
        -void clearRecursive(Node* node)
        -void inorderTraversalCallback(Node* node, function callback) const
        -void searchPartialCallback(Node* node, K partialKey, function matchFunc, function callback) const
    }
    
    class Node {
        <<Inner>>
        +K key
        +V value
        +Node* left
        +Node* right
        +Node* parent
        +Node(K k, V v)
    }
    
    BinarySearchTree --> Node : contains
    BinarySearchTree --> "0..*" Node : manages
    
    note for BinarySearchTree "Mẫu Template Method\n- Cấu trúc thuật toán\n- Biến đổi triển khai\n- Hỗ trợ callback"
```

### **5. 🔴⚫ CÂY ĐỎ-ĐEN (TEMPLATE CLASS)**

```mermaid
classDiagram
    class RedBlackTree {
        <<Template>>
        <<DataStructure>>
        -Node* root
        -Node* nil
        -size_t size_
        
        +RedBlackTree()
        +~RedBlackTree()
        +void insert(K key, V value)
        +V* find(K key)
        +const V* find(K key) const
        +bool remove(K key)
        +bool contains(K key) const
        +size_t size() const
        +bool empty() const
        +void clear()
        +void print() const
        +void traverseInorder(function callback) const
        +void traversePreorder(function callback) const
        +void traversePostorder(function callback) const
        +void searchPartial(K partialKey, function matchFunc, function callback) const
        +void searchRange(K startKey, K endKey, function callback) const
        +void forEach(function callback) const
        +void forEachReverse(function callback) const
        +int getHeight() const
        +bool isBalanced() const
        -void leftRotate(Node* x)
        -void rightRotate(Node* x)
        -void insertFixup(Node* z)
        -void deleteFixup(Node* x)
        -void transplant(Node* u, Node* v)
        -Node* findRecursive(Node* node, K key) const
        -void clearRecursive(Node* node)
        -void inorderTraversalCallback(Node* node, function callback) const
        -void searchPartialCallback(Node* node, K partialKey, function matchFunc, function callback) const
    }
    
    class RBTNode {
        <<Inner>>
        +K key
        +V value
        +Color color
        +Node* left
        +Node* right
        +Node* parent
        +RBTNode(K k, V v)
    }
    
    enum Color {
        RED
        BLACK
    }
    
    RedBlackTree --> RBTNode : contains
    RedBlackTree --> "0..*" RBTNode : manages
    RBTNode --> Color : has
    
    note for RedBlackTree "Cây tự cân bằng\n- Thuộc tính đỏ-đen\n- Đảm bảo O(log n)\n- Các phép quay"
```

### **6. ⚠️ TỔ HIỆP LỖI (HIERARCHY)**

```mermaid
classDiagram
    exception <|-- ContactException : extends
    ContactException <|-- ContactNotFound : extends
    ContactException <|-- ContactAlreadyExists : extends
    ContactException <|-- InvalidInput : extends
    ContactException <|-- EmptyInput : extends
    
    class exception {
        <<abstract>>
        +virtual const char* what() const noexcept
    }
    
    class ContactException {
        <<abstract>>
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
    
    note for ContactException "Tổ hiệp lỗi\n- Các loại ngoại lệ tùy chỉnh\n- Tin nhắn phản hồi người dùng\n- Xử lý lỗi đúng cách"
```

---

## 🔄 SƠ ĐỒ DỊCH CHUYỂN (CHUẨN UML 2.5)

### **1. ➕ DỊCH CHUYỂN THÊM LIÊN HỆ**

```mermaid
sequenceDiagram
    participant User
    participant ContactUI
    participant ContactManager
    participant Contact
    participant BST
    participant RBT
    participant ExceptionHandler
    
    User->>ContactUI: Chọn "Thêm liên hệ mới"
    ContactUI->>User: Yêu cầu nhập tên
    User->>ContactUI: Nhập tên liên hệ
    ContactUI->>ContactManager: getInstance()
    ContactManager-->>ContactUI: ContactManager* instance
    
    ContactUI->>ContactManager: addContact(name)
    
    alt Tên hợp lệ và không trùng lặp
        ContactManager->>Contact: new Contact(name)
        Contact-->>ContactManager: Contact* contact
        ContactManager->>ContactManager: addToIndexes(contact)
        
        ContactManager->>BST: insert(name, contact)
        BST-->>ContactManager: Thành công
        
        ContactManager->>BST: insert(id, contact)
        BST-->>ContactManager: Thành công
        
        alt Có số điện thoại
            ContactManager->>ContactManager: isPhoneNumberDuplicate(phone)
            ContactManager-->>ContactManager: false
            ContactManager->>RBT: insert(phone, contact)
            RBT-->>ContactManager: Thành công
        end
        
        alt Có email
            ContactManager->>ContactManager: isEmailDuplicate(email)
            ContactManager-->>ContactManager: false
            ContactManager->>RBT: insert(email, contact)
            RBT-->>ContactManager: Thành công
        end
        
        ContactManager-->>ContactUI: true
        ContactUI->>User: Hiển thị menu thêm chi tiết
        
    else Tên không hợp lệ hoặc trùng lặp
        ContactManager->>ExceptionHandler: Ném ngoại lệ
        ExceptionHandler-->>ContactUI: Tin nhắn ngoại lệ
        ContactUI-->>User: Hiển thị lỗi
    end
```

### **2. 🔍 DỊCH CHUYỂN TÌM KIẾM LIÊN HỆ**

```mermaid
sequenceDiagram
    participant User
    participant ContactUI
    participant ContactManager
    participant BST
    participant RBT
    participant Results
    
    User->>ContactUI: Chọn "Tìm kiếm liên hệ"
    ContactUI->>User: Hiển thị menu tìm kiếm
    User->>ContactUI: Chọn loại tìm kiếm
    ContactUI->>User: Yêu cầu nhập từ khóa
    
    alt Tìm kiếm theo tên
        User->>ContactUI: Nhập tên
        ContactUI->>ContactManager: searchByName(name)
        ContactManager->>BST: searchPartial(name, matchFunc, callback)
        
        loop Duyệt cây
            BST->>BST: searchPartialCallback(node)
            alt Node khớp
                BST->>Results: callback(key, value)
                Results->>Results: insert(contact)
            end
            BST->>BST: Duyệt cây con trái
            BST->>BST: Duyệt cây con phải
        end
        
        BST-->>ContactManager: Duyệt hoàn tất
        ContactManager-->>ContactUI: set<Contact*> results
        ContactUI->>User: Hiển thị kết quả
        
    else Tìm kiếm theo số điện thoại
        User->>ContactUI: Nhập số điện thoại
        ContactUI->>ContactManager: searchByPhone(phone)
        
        alt Trùng chính xác đầu tiên
            ContactManager->>RBT: find(phone)
            RBT-->>ContactManager: Contact* contact
            ContactManager->>Results: insert(contact)
            ContactManager-->>ContactUI: results
            ContactUI->>User: Hiển thị kết quả
        else Tìm kiếm từng phần
            ContactManager->>RBT: searchPartial(phone, matchFunc, callback)
            RBT-->>ContactManager: Duyệt hoàn tất
            ContactManager-->>ContactUI: set<Contact*> results
            ContactUI->>User: Hiển thị kết quả
        end
    end
```

---

## 🗂️ SƠ ĐỒ THÀNH PHẦN (CHUẨN UML 2.5)

```mermaid
graph TB
    subgraph "Hệ thống Quản lý Danh bạ"
        subgraph "Các thành phần ứng dụng"
            MAIN[main.cpp<br/>Điểm khởi đầu]
        end
        
        subgraph "Các thành phần giao diện"
            UI[ContactUI<br/>Giao diện người dùng]
        end
        
        subgraph "Các thành phần logic nghiệp vụ"
            CM[ContactManager<br/>Logic nghiệp vụ]
        end
        
        subgraph "Các thành phần cấu trúc dữ liệu"
            BST[BinarySearchTree<br/>Lưu trữ sắp xếp]
            RBT[RedBlackTree<br/>Lưu trữ cân bằng]
        end
        
        subgraph "Các thành phần thực thể"
            C[Contact<br/>Mô hình dữ liệu]
        end
        
        subgraph "Các thành phần xử lý ngoại lệ"
            EX[ContactException<br/>Xử lý lỗi]
        end
    end
    
    subgraph "Các phụ thuộc bên ngoài"
        STL[Standard Template Library]
        IO[iostream]
        STRING[string]
        FUNCTIONAL[functional]
        ALGORITHM[algorithm]
        REGEX[regex]
    end
    
    MAIN --> UI
    UI --> CM
    CM --> BST
    CM --> RBT
    CM --> C
    CM --> EX
    UI --> EX
    
    C --> STL
    CM --> STL
    UI --> IO
    CM --> IO
    CM --> STRING
    CM --> FUNCTIONAL
    CM --> ALGORITHM
    CM --> REGEX
    
    style MAIN fill:#e1f5fe
    style UI fill:#f3e5f5
    style CM fill:#e8f5e8
    style BST fill:#fff3e0
    style RBT fill:#fff3e0
    style C fill:#fce4ec
    style EX fill:#ffebee
```

---

## 🔄 SƠ ĐỒ HOẠT ĐỘNG (CHUẨN UML 2.5)

### **1. 🚀 DÒNG HOẠT ĐỘNG CHÍNH ỨNG DỤNG**

```mermaid
flowchart TD
    A[Khởi động ứng dụng] --> B[Khởi tạo ContactUI]
    B --> C[Hiển thị màn hình chào]
    C --> D[Hiển thị menu chính]
    D --> E{Lựa chọn của người dùng}
    
    E -->|1| F[Dòng thêm liên hệ]
    E -->|2| G[Dòng quản lý liên hệ]
    E -->|3| H[Dòng tìm kiếm liên hệ]
    E -->|4| I[Hiển thị tất cả liên hệ]
    E -->|5| J[Hiển thị thống kê]
    E -->|6| K[Kết thúc ứng dụng]
    
    F --> L[Nhập tên liên hệ]
    L --> M{Xác thực tên}
    M -->|Không hợp lệ| N[Hiển thị lỗi]
    M -->|Hợp lệ| O[Kiểm tra trùng lặp]
    O -->|Trùng lặp| P[Hiển thị lỗi]
    O -->|Độc lập| Q[Tạo liên hệ]
    Q --> R[Thêm vào chỉ mục]
    R --> S[Hiển thị thành công]
    
    G --> T[Tìm kiếm liên hệ]
    T --> U{Liên hệ tìm thấy?}
    U -->|Không| V[Hiển thị lỗi]
    U -->|Có| W[Hiển thị menu chỉnh sửa]
    
    H --> X[Chọn loại tìm kiếm]
    X --> Y[Nhập thuật ngữ tìm kiếm]
    Y --> Z[Thực thi tìm kiếm]
    Z --> AA[Hiển thị kết quả]
    
    I --> BB[Duyệt tất cả liên hệ]
    BB --> CC[Hiển thị kết quả]
    
    J --> DD[Tính toán thống kê]
    DD --> EE[Hiển thị thống kê]
    
    N --> D
    P --> D
    S --> D
    V --> D
    W --> D
    AA --> D
    CC --> D
    EE --> D
    
    K --> FF[Dọn dẹp tài nguyên]
    FF --> GG[Kết thúc ứng dụng]
```

### **2. 🔍 DỊCH CHUYỂN HOẠT ĐỘNG TÌM KIẾM**

```mermaid
flowchart TD
    A[Bắt đầu tìm kiếm] --> B[Chọn loại tìm kiếm]
    B --> C{Loại tìm kiếm}
    
    C -->|Tên| D[Nhập tên]
    C -->|Số điện thoại| E[Nhập số điện thoại]
    C -->|Email| F[Nhập email]
    
    D --> G[Chuyển thành chữ thường]
    G --> H[Định nghĩa chiến lược tìm kiếm]
    H --> I[Thực thi duyệt cây]
    
    E --> J[Kiểm tra khớp chính xác]
    J --> K{Khớp chính xác?}
    K -->|Có| L[Trả về kết quả]
    K -->|Không| M[Làm sạch số điện thoại]
    M --> N[Thực thi tìm kiếm từng phần]
    
    F --> O[Chuyển thành chữ thường]
    O --> P[Thực thi duyệt cây]
    
    I --> Q[Xử lý mỗi nút]
    Q --> R{Nút có khớp?}
    R -->|Có| S[Thêm vào kết quả]
    R -->|Không| T[Tiếp tục duyệt]
    
    N --> U[Xử lý mỗi nút]
    U --> V{Nút có khớp?}
    V -->|Có| W[Thêm vào kết quả]
    V -->|Không| X[Tiếp tục duyệt]
    
    P --> Y[Xử lý mỗi nút]
    Y --> Z{Nút có khớp?}
    Z -->|Có| AA[Thêm vào kết quả]
    Z -->|Không| BB[Tiếp tục duyệt]
    
    S --> CC[Kiểm tra nút tiếp theo]
    T --> CC
    W --> DD[Kiểm tra nút tiếp theo]
    X --> DD
    AA --> EE[Kiểm tra nút tiếp theo]
    BB --> EE
    
    CC --> FF{Có nút tiếp theo?}
    DD --> FF
    EE --> FF
    
    FF -->|Có| Q
    FF -->|Không| GG[Trả về kết quả]
    
    L --> GG
    GG --> HH[Hiển thị kết quả]
    HH --> II[Kết thúc tìm kiếm]
```

---

## 🎨 SƠ ĐỒ TRẠNG THÁI (CHUẨN UML 2.5)

### **1. 🔄 TRẠNG THÁI LIÊN HỆ**

```mermaid
stateDiagram-v2
    [*] --> Empty: Khởi tạo
    Empty --> Basic: Thêm tên
    Basic --> WithPhone: Thêm số điện thoại
    Basic --> WithEmail: Thêm email
    Basic --> WithAddress: Thêm địa chỉ
    Basic --> WithNotes: Thêm ghi chú
    Basic --> Complete: Thêm tất cả thông tin
    
    WithPhone --> WithPhone: Cập nhật số điện thoại
    WithPhone --> WithEmail: Thêm email
    WithPhone --> WithAddress: Thêm địa chỉ
    WithPhone --> WithNotes: Thêm ghi chú
    WithPhone --> Complete: Thêm tất cả thông tin
    
    WithEmail --> WithPhone: Thêm số điện thoại
    WithEmail --> WithEmail: Cập nhật email
    WithEmail --> WithAddress: Thêm địa chỉ
    WithEmail --> WithNotes: Thêm ghi chú
    WithEmail --> Complete: Thêm tất cả thông tin
    
    WithAddress --> WithPhone: Thêm số điện thoại
    WithAddress --> WithEmail: Thêm email
    WithAddress --> WithAddress: Cập nhật địa chỉ
    WithAddress --> WithNotes: Thêm ghi chú
    WithAddress --> Complete: Thêm tất cả thông tin
    
    WithNotes --> WithPhone: Thêm số điện thoại
    WithNotes --> WithEmail: Thêm email
    WithNotes --> WithAddress: Thêm địa chỉ
    WithNotes --> WithNotes: Cập nhật ghi chú
    WithNotes --> Complete: Thêm tất cả thông tin
    
    Complete --> Complete: Cập nhật bất kỳ thông tin
    Complete --> [*]: Xóa liên hệ
    
    note right of Empty : "Trạng thái tối thiểu\nChỉ tên"
    note right of Basic : "Liên hệ cơ bản\nTên + các trường tùy chọn"
    note right of Complete : "Liên hệ đầy đủ\nTất cả các trường được điền"
```

### **2. 🔄 TRẠNG THÁI ỨNG DỤNG**

```mermaid
stateDiagram-v2
    [*] --> Welcome: Khởi động ứng dụng
    Welcome --> MainMenu: Hiển thị menu chính
    MainMenu --> AddContact: Chọn thêm
    MainMenu --> ManageContact: Chọn quản lý
    MainMenu --> SearchContact: Chọn tìm kiếm
    MainMenu --> DisplayAll: Chọn hiển thị
    MainMenu --> Statistics: Chọn thống kê
    MainMenu --> Exit: Chọn thoát
    
    AddContact --> AddDetails: Tên đã thêm
    AddDetails --> AddDetails: Thêm thông tin chi tiết
    AddDetails --> MainMenu: Hoàn tất
    
    ManageContact --> ManageMenu: Hiển thị menu quản lý
    ManageMenu --> EditContact: Chọn chỉnh sửa
    ManageMenu --> DeleteContact: Chọn xóa
    ManageMenu --> ViewContact: Chọn xem
    ManageMenu --> MainMenu: Quay lại menu chính
    
    EditContact --> EditMenu: Hiển thị menu chỉnh sửa
    EditMenu --> EditMenu: Chỉnh sửa thông tin
    EditMenu --> ManageMenu: Hoàn tất chỉnh sửa
    
    SearchContact --> SearchMenu: Hiển thị menu tìm kiếm
    SearchMenu --> SearchByName: Tìm kiếm theo tên
    SearchMenu --> SearchByPhone: Tìm kiếm theo số điện thoại
    SearchMenu --> SearchByEmail: Tìm kiếm theo email
    SearchMenu --> MainMenu: Quay lại menu chính
    
    DisplayAll --> MainMenu: Hiển thị hoàn tất
    Statistics --> MainMenu: Hoàn tất thống kê
    
    Exit --> [*]: Kết thúc ứng dụng
    
    note right of Welcome : "Khởi động ứng dụng"
    note right of MainMenu : "Trung tâm điều hướng chính"
    note right of AddContact : "Dòng tạo liên hệ"
    note right of ManageContact : "Dòng quản lý liên hệ"
    note right of SearchContact : "Dòng hoạt động tìm kiếm"
```

---

## 📊 SƠ ĐỒ ĐỐI TƯỢNG (CHUẬN UML 2.5)

### **1. 🔍 VÍ DỤ THỂ HIỆN HỆ THỐNG**

```mermaid
graph TB
    subgraph "Thể hiện hệ thống: Hệ thống Quản lý Danh bạ"
        subgraph "Thể hiện thể hiện ContactManager"
            CM[ContactManager<br/>thể hiện: 0x7fff1234]
        end
        
        subgraph "Các thể hiện liên hệ"
            C1[Contact<br/>id: 1<br/>tên: "Nguyễn Văn A"<br/>số điện thoại: "0123456789"<br/>email: "a@email.com"]
            C2[Contact<br/>id: 2<br/>tên: "Trần Thị B"<br/>số điện thoại: "0987654321"<br/>email: "b@email.com"]
            C3[Contact<br/>id: 3<br/>tên: "Lê Văn C"<br/>số điện thoại: "1122334455"<br/>email: "c@email.com"]
        end
        
        subgraph "Các thể hiện chỉ mục"
            BST1[BinarySearchTree<br/>gốc: Node*<br/>kích thước: 3]
            BST2[BinarySearchTree<br/>gốc: Node*<br/>kích thước: 3]
            RBT1[RedBlackTree<br/>gốc: Node*<br/>kích thước: 3]
            RBT2[RedBlackTree<br/>gốc: Node*<br/>kích thước: 3]
        end
        
        subgraph "Các thể hiện nút"
            N1[Node<br/>key: "Nguyễn Văn A"<br/>value: Contact*<br/>trái: nullptr<br/>phải: Node*]
            N2[Node<br/>key: "Trần Thị B"<br/>value: Contact*<br/>trái: Node*<br/>phải: Node*]
            N3[Node<br/>key: "Lê Văn C"<br/>value: Contact*<br/>trái: Node*<br/>phải: nullptr]
        end
    end
    
    CM --> BST1 : quản lý
    CM --> BST2 : quản lý
    CM --> RBT1 : quản lý
    CM --> RBT2 : quản lý
    
    BST1 --> N1 : chứa
    BST1 --> N2 : chứa
    BST1 --> N3 : chứa
    
    N1 --> C1 : tham chiếu
    N2 --> C2 : tham chiếu
    N3 --> C3 : tham chiếu
    
    style CM fill:#e8f5e8
    style C1 fill:#fce4ec
    style C2 fill:#fce4ec
    style C3 fill:#fce4ec
    style BST1 fill:#fff3e0
    style BST2 fill:#fff3e0
    style RBT1 fill:#fff3e0
    style RBT2 fill:#fff3e0
    style N1 fill:#e1f5fe
    style N2 fill:#e1f5fe
    style N3 fill:#e1f5fe
```

---

## 🔧 GHI CHÚ VỀ TRIỂN KHAI

### **1. 📋 BẢNG KIỂM TRA VIỆC TUÂN THỦ UML**

- ✅ **Sơ đồ lớp**: Stereotypes, độ truy cập, quan hệ
- ✅ **Sơ đồ dịch chuyển**: Lifelines, tin nhắn, thanh hoạt động
- ✅ **Sơ đồ thành phần**: Thành phần, giao diện, phụ thuộc
- ✅ **Sơ đồ hoạt động**: Hành động, quyết định, dòng, swimlanes
- ✅ **Sơ đồ trạng thái**: Trạng thái, chuyển tiếp, sự kiện, hành động
- ✅ **Sơ đồ đối tượng**: Ví dụ thể hiện, quan hệ đối tượng

### **2. 🎯 ÁNH XẠ CHIẾN LƯỢC PATTERN**

| Phần tử UML | Pattern thiết kế | Triển khai |
|-------------|----------------|----------------|
| **Singleton** | ContactManager | Thể hiện độc nhất + getInstance() |
| **Template Method** | BST/RBT | Cấu trúc thuật toán duyệt |
| **Strategy** | Hoạt động tìm kiếm | std::function callbacks |
| **Factory** | Tạo liên hệ | phương thức addContact() |
| **Observer** | Đồng bộ chỉ mục | phương thức addToIndexes() |
| **MVC** | ContactUI | Phân tách View + Controller |

### **3. 🔍 CÁC LOẠI QUAN HỆ**

- **Quan hệ kết nối**: ContactManager quản lý các đối tượng Contact
- **Quan hệ kết hợp**: ContactManager chứa các cấu trúc cây
- **Quan hệ tổng hợp**: Các cấu trúc cây chứa con trỏ Contact
- **Phụ thuộc**: UI phụ thuộc vào ContactManager
- **Kế thừa**: Tổ hiệp lỗi

---

## 📈 PHÂN TÍCH HIỆU SUẤT

### **1. ⏱️ ĐỘ PHỨC TẠP THỜI GIAN**

| Hoạt động | BST (Trung bình) | BST (Tệ nhất) | RBT (Đảm bảo) |
|-----------|---------------|-------------|------------------|
| **Chèn** | O(log n) | O(n) | O(log n) |
| **Tìm kiếm** | O(log n) | O(n) | O(log n) |
| **Xóa** | O(log n) | O(n) | O(log n) |
| **Duyệt** | O(n) | O(n) | O(n) |

### **2. 💾 ĐỘ PHỨC TẠP KHÔNG GIAN**

| Thành phần | Độ phức tạp không gian | Chi tiết |
|-----------|------------------|---------|
| **Đối tượng liên hệ** | O(n) | n liên hệ với dữ liệu không đổi |
| **Cấu trúc cây** | O(n) | n nút với chi phí cố định |
| **Quản lý chỉ mục** | O(n) | Nhiều chỉ mục, mỗi O(n) |
| **Hệ thống tổng thể** | O(n) | Tuyến tính với số lượng liên hệ |

---

## 🚀 KẾT LUẬN

Tài liệu UML này tuân thủ chuẩn **UML 2.5** và cung cấp cái nhìn toàn diện về kiến trúc hệ thống Quản lý Danh bạ Thông minh. Các biểu đồ được thiết kế để:

1. **🎯 Rõ ràng**: Hiểu rõ cấu trúc và quan hệ
2. **🔧 Triển khai**: Hướng dẫn phát triển
3. **📊 Tài liệu kỹ thuật**: Tài liệu kỹ thuật chuẩn
4. **🚀 Bảo trì**: Dễ dàng bảo trì và mở rộng

**Việc tuân thủ chuẩn UML:**
- ✅ **Sơ đồ lớp**: Ký hiệu và quan hệ
- ✅ **Sơ đồ dịch chuyển**: Luồng tin nhắn và thời gian
- ✅ **Sơ đồ thành phần**: Kiến trúc hệ thống
- ✅ **Sơ đồ hoạt động**: Luồng quy trình kinh doanh
- ✅ **Sơ đồ trạng thái**: Đời sống đối tượng
- ✅ **Sơ đồ đối tượng**: Ví dụ thể hiện

Tài liệu này có thể được sử dụng để:
- **Phát triển**: Hướng dẫn triển khai
- **Đánh giá code**: Kiểm tra việc tuân thủ thiết kế
- **Tài liệu kỹ thuật**: Tài liệu kỹ thuật
- **Đào tạo**: Hướng dẫn đào tạo nhân viên
- **Bảo trì**: Hiểu biết về hệ thống
