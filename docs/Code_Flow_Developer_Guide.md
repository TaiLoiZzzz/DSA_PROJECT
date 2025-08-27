# 🚀 HƯỚNG DẪN LUỒNG HOẠT ĐỘNG CODE - DÀNH CHO DEVELOPER

## 📋 TỔNG QUAN

Tài liệu này giải thích chi tiết **luồng hoạt động của code** trong hệ thống Quản lý Danh bạ Thông minh, giúp các developer mới hiểu rõ cách code hoạt động và dễ dàng maintain/extend hệ thống.

## 🏗️ KIẾN TRÚC TỔNG THỂ

```
┌─────────────────────────────────────────────────────────────┐
│                    MAIN APPLICATION                        │
│                     (main.cpp)                            │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    PRESENTATION LAYER                      │
│                    (ContactUI.cpp)                         │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                     BUSINESS LOGIC LAYER                   │
│                   (ContactManager.cpp)                     │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   DATA STRUCTURES LAYER                    │
│              (BinarySearchTree.h, RedBlackTree.h)         │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                      ENTITY LAYER                          │
│                      (Contact.cpp)                         │
└─────────────────────────────────────────────────────────────┘
```

## 🔄 LUỒNG HOẠT ĐỘNG CHI TIẾT

### **1. 🚀 KHỞI ĐỘNG ỨNG DỤNG (STARTUP FLOW)**

#### **📍 File: `main.cpp`**
```cpp
int main() {
    try {
        ContactUI ui;        // 🏗️ Tạo UI instance
        ui.run();            // 🚀 Chạy ứng dụng
    } catch (const std::exception& e) {
        // 🛡️ Global exception handling
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

#### **🔄 Luồng hoạt động:**
1. **Khởi tạo ContactUI**: Tạo instance của ContactUI
2. **Gọi ui.run()**: Bắt đầu vòng lặp chính của ứng dụng
3. **Exception handling**: Xử lý lỗi toàn cục nếu có

---

### **2. 🖥️ VÒNG LẶP CHÍNH CỦA ỨNG DỤNG (MAIN LOOP)**

#### **📍 File: `ContactUI.cpp` - Method `run()`**
```cpp
void ContactUI::run() {
    showWelcome();           // 🎉 Hiển thị màn hình chào
    
    while (true) {           // 🔄 Vòng lặp vô hạn
        try {
            showMainMenu();   // 📋 Hiển thị menu chính
            int choice = getIntInput("Chọn chức năng: ");
            
            switch (choice) { // 🎯 Xử lý lựa chọn
                case 1: addContact(); break;      // ➕ Thêm liên hệ
                case 2: manageContact(); break;   // ✏️ Quản lý liên hệ
                case 3: searchContacts(); break;  // 🔍 Tìm kiếm
                case 4: displayAllContacts(); break; // 📋 Hiển thị tất cả
                case 5: showStatistics(); break;  // 📊 Thống kê
                case 6: 
                    showGoodbye();                // 👋 Tạm biệt
                    return;                       // 🚪 Thoát
                default: 
                    cout << "Lựa chọn không hợp lệ!" << endl;
            }
        } catch (const ContactException& e) {
            cout << "Lỗi: " << e.what() << endl;
        }
    }
}
```

#### **🔄 Luồng hoạt động:**
1. **Hiển thị welcome**: Chào mừng người dùng
2. **Vòng lặp chính**: Lặp vô hạn cho đến khi thoát
3. **Hiển thị menu**: Menu với 6 lựa chọn chính
4. **Xử lý input**: Nhận và validate lựa chọn
5. **Switch case**: Điều hướng đến chức năng tương ứng
6. **Exception handling**: Xử lý lỗi trong mỗi iteration

---

### **3. ➕ LUỒNG THÊM LIÊN HỆ MỚI (ADD CONTACT FLOW)**

#### **📍 File: `ContactUI.cpp` - Method `addContact()`**
```cpp
void ContactUI::addContact() const {
    cout << "\n=== THÊM LIÊN HỆ MỚI ===" << endl;
    
    // 🔍 Bước 1: Nhập và validate tên
    string name = getStringInput("Nhập tên liên hệ: ");
    if (name.empty() || name.length() < 2) {
        cout << "❌ Tên phải có ít nhất 2 ký tự!" << endl;
        return;
    }
    
    // 🏭 Bước 2: Tạo liên hệ thông qua ContactManager
    ContactManager* manager = ContactManager::getInstance();
    if (!manager->addContact(name)) {
        cout << "❌ Không thể thêm liên hệ!" << endl;
        return;
    }
    
    // 🎯 Bước 3: Hiển thị menu thêm chi tiết
    showAddDetailsMenu(name);
}
```

#### **📍 File: `ContactManager.cpp` - Method `addContact()`**
```cpp
bool ContactManager::addContact(const string& name) {
    try {
        // 🛡️ Validation 1: Kiểm tra tên rỗng
        if (name.empty()) {
            throw EmptyInput("tên");
        }
        
        // 🔍 Validation 2: Kiểm tra trùng lặp
        if (contactsByName.contains(name)) {
            throw ContactAlreadyExists(name);
        }
        
        // 🏭 Bước 3: Tạo Contact object mới
        Contact* newContact = new Contact(name);
        
        // 🔄 Bước 4: Thêm vào tất cả indexes
        addToIndexes(newContact);
        
        cout << "✅ Liên hệ '" << name << "' đã được thêm thành công!" << endl;
        return true;
        
    } catch (const ContactException& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
        return false;
    }
}
```

#### **📍 File: `ContactManager.cpp` - Method `addToIndexes()`**
```cpp
void ContactManager::addToIndexes(Contact* contact) {
    // 🌳 Bước 1: Thêm vào BST theo tên
    contactsByName.insert(contact->getName(), contact);
    
    // 🌳 Bước 2: Thêm vào BST theo ID
    contactsById.insert(contact->getId(), contact);
    
    // 🔴 Bước 3: Thêm vào RBT theo số điện thoại (nếu có)
    if (!contact->getPhoneNumber().empty()) {
        if (!isPhoneNumberDuplicate(contact->getPhoneNumber(), contact)) {
            contactsByPhone.insert(contact->getPhoneNumber(), contact);
        }
    }
    
    // 🔴 Bước 4: Thêm vào RBT theo email (nếu có)
    if (!contact->getEmail().empty()) {
        if (!isEmailDuplicate(contact->getEmail(), contact)) {
            contactsByEmail.insert(contact->getEmail(), contact);
        }
    }
}
```

#### **🔄 Luồng hoạt động chi tiết:**
1. **Input validation**: Kiểm tra tên không rỗng và đủ độ dài
2. **Duplicate check**: Kiểm tra tên không trùng lặp
3. **Object creation**: Tạo Contact object mới với ID tự động
4. **Index synchronization**: Thêm vào tất cả relevant indexes
5. **Success feedback**: Thông báo thành công cho user

---

### **4. 🔍 LUỒNG TÌM KIẾM LIÊN HỆ (SEARCH FLOW)**

#### **📍 File: `ContactUI.cpp` - Method `searchContacts()`**
```cpp
void ContactUI::searchContacts() const {
    cout << "\n=== TÌM KIẾM LIÊN HỆ ===" << endl;
    cout << "1. Tìm theo tên" << endl;
    cout << "2. Tìm theo số điện thoại" << endl;
    cout << "3. Tìm theo email" << endl;
    
    int choice = getIntInput("Chọn loại tìm kiếm: ");
    
    switch (choice) {
        case 1: searchByName(); break;      // 🔍 Tìm theo tên
        case 2: searchByPhone(); break;     // 📱 Tìm theo số điện thoại
        case 3: searchByEmail(); break;     // 📧 Tìm theo email
        default: cout << "Lựa chọn không hợp lệ!" << endl;
    }
}
```

#### **📍 File: `ContactManager.cpp` - Method `searchByName()`**
```cpp
set<Contact*> ContactManager::searchByName(const string& name) {
    set<Contact*> results;  // 🗂️ Container chứa kết quả
    
    // 🔄 Bước 1: Convert input sang lowercase
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    // 🎭 Bước 2: Định nghĩa search strategy
    auto searchCallback = [&results, &lowerName](const string& key, Contact* contact) {
        string contactName = key;
        string lowerContactName = contactName;
        transform(lowerContactName.begin(), lowerContactName.end(), lowerContactName.begin(), ::tolower);
        
        // 🔍 Kiểm tra partial match
        if (lowerContactName.find(lowerName) != string::npos) {
            results.insert(contact);
        }
    };
    
    // 🎭 Bước 3: Định nghĩa match function
    auto matchFunc = [](const string& partial, const string& full) {
        string lowerPartial = partial;
        string lowerFull = full;
        transform(lowerPartial.begin(), lowerPartial.end(), lowerPartial.begin(), ::tolower);
        transform(lowerFull.begin(), lowerFull.end(), lowerFull.begin(), ::tolower);
        return lowerFull.find(lowerPartial) != string::npos;
    };
    
    // 🚀 Bước 4: Thực hiện tìm kiếm với callback
    contactsByName.searchPartial(name, matchFunc, searchCallback);
    
    return results;
}
```

#### **📍 File: `BinarySearchTree.h` - Method `searchPartial()`**
```cpp
void searchPartial(const K& partialKey, 
                  const std::function<bool(const K&, const K&)>& matchFunc,
                  const std::function<void(const K&, const V&)>& callback) const {
    searchPartialCallback(root, partialKey, matchFunc, callback);
}

void searchPartialCallback(Node* node, const K& partialKey, 
                          const std::function<bool(const K&, const K&)>& matchFunc,
                          const std::function<void(const K&, const V&)>& callback) const {
    if (node == nullptr) return;
    
    // 🔍 Bước 1: Kiểm tra node hiện tại
    if (matchFunc(partialKey, node->key)) {
        callback(node->key, node->value);  // 🎯 Gọi callback nếu match
    }
    
    // 🔄 Bước 2: Đệ quy xuống cả 2 subtree
    searchPartialCallback(node->left, partialKey, matchFunc, callback);
    searchPartialCallback(node->right, partialKey, matchFunc, callback);
}
```

#### **🔄 Luồng hoạt động chi tiết:**
1. **Menu selection**: User chọn loại tìm kiếm
2. **Input collection**: Nhận từ khóa tìm kiếm
3. **Strategy definition**: Định nghĩa match function và callback
4. **Tree traversal**: Duyệt toàn bộ tree để tìm matches
5. **Result collection**: Thu thập kết quả vào set
6. **Display results**: Hiển thị kết quả cho user

---

### **5. ✏️ LUỒNG CHỈNH SỬA LIÊN HỆ (EDIT FLOW)**

#### **📍 File: `ContactUI.cpp` - Method `editContact()`**
```cpp
void ContactUI::editContact() const {
    cout << "\n=== CHỈNH SỬA LIÊN HỆ ===" << endl;
    
    // 🔍 Bước 1: Tìm liên hệ cần sửa
    string name = getStringInput("Nhập tên liên hệ cần sửa: ");
    ContactManager* manager = ContactManager::getInstance();
    Contact* contact = manager->findContact(name);
    
    if (!contact) {
        cout << "❌ Không tìm thấy liên hệ!" << endl;
        return;
    }
    
    // 📋 Bước 2: Hiển thị thông tin hiện tại
    contact->display();
    
    // 🎯 Bước 3: Hiển thị menu chỉnh sửa
    showEditMenu(contact);
}
```

#### **📍 File: `ContactUI.cpp` - Method `showEditMenu()`**
```cpp
void ContactUI::showEditMenu(Contact* contact) const {
    while (true) {
        cout << "\n=== MENU CHỈNH SỬA ===" << endl;
        cout << "1. Sửa số điện thoại" << endl;
        cout << "2. Sửa email" << endl;
        cout << "3. Sửa địa chỉ" << endl;
        cout << "4. Sửa ghi chú" << endl;
        cout << "5. Quay lại" << endl;
        
        int choice = getIntInput("Chọn thông tin cần sửa: ");
        
        switch (choice) {
            case 1: editPhoneNumber(contact); break;  // 📱 Sửa số điện thoại
            case 2: editEmail(contact); break;        // 📧 Sửa email
            case 3: editAddress(contact); break;      // 🏠 Sửa địa chỉ
            case 4: editNotes(contact); break;        // 📝 Sửa ghi chú
            case 5: return;                           // 🔙 Quay lại
            default: cout << "Lựa chọn không hợp lệ!" << endl;
        }
    }
}
```

#### **📍 File: `ContactUI.cpp` - Method `editPhoneNumber()`**
```cpp
void ContactUI::editPhoneNumber(Contact* contact) const {
    string oldPhone = contact->getPhoneNumber();
    string newPhone = getStringInput("Nhập số điện thoại mới: ");
    
    // 🛡️ Bước 1: Validation
    if (!isValidPhoneNumber(newPhone)) {
        cout << "❌ Số điện thoại không hợp lệ!" << endl;
        return;
    }
    
    // 🔍 Bước 2: Kiểm tra trùng lặp
    ContactManager* manager = ContactManager::getInstance();
    if (!manager->canAddPhoneNumber(newPhone, contact)) {
        cout << "❌ Số điện thoại đã tồn tại!" << endl;
        return;
    }
    
    // 🔄 Bước 3: Cập nhật indexes
    manager->updatePhoneIndex(contact, oldPhone, newPhone);
    
    // ✏️ Bước 4: Cập nhật contact
    contact->setPhoneNumber(newPhone);
    
    cout << "✅ Số điện thoại đã được cập nhật!" << endl;
}
```

#### **🔄 Luồng hoạt động chi tiết:**
1. **Contact lookup**: Tìm liên hệ cần sửa theo tên
2. **Current display**: Hiển thị thông tin hiện tại
3. **Edit menu**: Menu với các tùy chọn chỉnh sửa
4. **Input validation**: Kiểm tra dữ liệu mới hợp lệ
5. **Duplicate check**: Kiểm tra không trùng lặp
6. **Index update**: Cập nhật tất cả relevant indexes
7. **Contact update**: Cập nhật thông tin trong Contact object

---

### **6. 🗑️ LUỒNG XÓA LIÊN HỆ (DELETE FLOW)**

#### **📍 File: `ContactManager.cpp` - Method `removeContact()`**
```cpp
bool ContactManager::removeContact(const string& name) {
    try {
        // 🔍 Bước 1: Tìm liên hệ cần xóa
        Contact** contactPtr = contactsByName.find(name);
        if (contactPtr == nullptr) {
            throw ContactNotFound(name);
        }
        
        Contact* contact = *contactPtr;
        int id = contact->getId();
        
        // 🔄 Bước 2: Xóa khỏi tất cả indexes
        removeFromIndexes(contact);
        
        // 🗑️ Bước 3: Delete Contact object
        delete contact;
        
        cout << "✅ Liên hệ '" << name << "' đã được xóa thành công!" << endl;
        return true;
        
    } catch (const ContactException& e) {
        cout << "❌ Lỗi: " << e.what() << endl;
        return false;
    }
}
```

#### **📍 File: `ContactManager.cpp` - Method `removeFromIndexes()`**
```cpp
void ContactManager::removeFromIndexes(Contact* contact) {
    // 🌳 Bước 1: Xóa khỏi BST theo tên
    contactsByName.remove(contact->getName());
    
    // 🌳 Bước 2: Xóa khỏi BST theo ID
    contactsById.remove(contact->getId());
    
    // 🔴 Bước 3: Xóa khỏi RBT theo số điện thoại (nếu có)
    if (!contact->getPhoneNumber().empty()) {
        contactsByPhone.remove(contact->getPhoneNumber());
    }
    
    // 🔴 Bước 4: Xóa khỏi RBT theo email (nếu có)
    if (!contact->getEmail().empty()) {
        contactsByEmail.remove(contact->getEmail());
    }
}
```

#### **🔄 Luồng hoạt động chi tiết:**
1. **Contact lookup**: Tìm liên hệ cần xóa theo tên
2. **Index removal**: Xóa khỏi tất cả indexes
3. **Memory cleanup**: Delete Contact object
4. **Success feedback**: Thông báo thành công

---

### **7. 🧹 LUỒNG DỌN DẸP BỘ NHỚ (CLEANUP FLOW)**

#### **📍 File: `ContactManager.cpp` - Method `clearAll()`**
```cpp
void ContactManager::clearAll() {
    // 🔥 NEW: Sử dụng callback để delete contacts thay vì dùng vector
    auto deleteCallback = [](const int& key, Contact* contact) {
        delete contact;  // 🗑️ Delete từng contact
    };
    
    // 🔄 Bước 1: Delete tất cả Contact objects
    contactsById.forEach(deleteCallback);
    
    // 🧹 Bước 2: Clear tất cả indexes
    contactsByName.clear();
    contactsByPhone.clear();
    contactsByEmail.clear();
    contactsById.clear();
}
```

#### **🔄 Luồng hoạt động chi tiết:**
1. **Callback definition**: Định nghĩa delete callback function
2. **Contact deletion**: Delete tất cả Contact objects
3. **Index clearing**: Clear tất cả tree structures
4. **Memory cleanup**: Giải phóng bộ nhớ

---

## 🔍 CÁC ĐIỂM QUAN TRỌNG CẦN HIỂU

### **1. 🏭 Singleton Pattern Implementation**
```cpp
// 📍 Vị trí: ContactManager.cpp:11-17
ContactManager* ContactManager::instance = nullptr;

ContactManager* ContactManager::getInstance() {
    if (instance == nullptr) {
        instance = new ContactManager();  // 🏭 Lazy initialization
    }
    return instance;
}
```

**Lưu ý quan trọng:**
- **Lazy initialization**: Instance chỉ được tạo khi cần thiết
- **Global access**: Có thể truy cập từ mọi nơi trong ứng dụng
- **Single instance**: Đảm bảo chỉ có một instance duy nhất

### **2. 🎭 Callback Pattern với std::function**
```cpp
// 📍 Vị trí: BinarySearchTree.h:132-142
void searchPartial(const K& partialKey, 
                  const std::function<bool(const K&, const K&)>& matchFunc,      // 🎭 Strategy 1
                  const std::function<void(const K&, const V&)>& callback) const { // 🎭 Strategy 2
    searchPartialCallback(root, partialKey, matchFunc, callback);
}
```

**Lưu ý quan trọng:**
- **std::function**: Có thể chứa bất kỳ callable object nào
- **Lambda support**: Hỗ trợ lambda functions với captures
- **Strategy pattern**: Cho phép thay đổi algorithm trong runtime

### **3. 🔄 Index Synchronization**
```cpp
// 📍 Vị trí: ContactManager.cpp:280-300
void ContactManager::addToIndexes(Contact* contact) {
    contactsByName.insert(contact->getName(), contact);      // 🌳 BST insert
    contactsById.insert(contact->getId(), contact);          // 🌳 BST insert
    
    if (!contact->getPhoneNumber().empty()) {
        if (!isPhoneNumberDuplicate(contact->getPhoneNumber(), contact)) {
            contactsByPhone.insert(contact->getPhoneNumber(), contact);  // 🔴 RBT insert
        }
    }
    
    if (!contact->getEmail().empty()) {
        if (!isEmailDuplicate(contact->getEmail(), contact)) {
            contactsByEmail.insert(contact->getEmail(), contact);        // 🔴 RBT insert
        }
    }
}
```

**Lưu ý quan trọng:**
- **Multiple indexes**: Mỗi index được tối ưu cho một loại tìm kiếm
- **Duplicate prevention**: Kiểm tra trùng lặp trước khi insert
- **Consistent state**: Đảm bảo tất cả indexes đồng bộ

---

## 🚀 CÁCH DEBUG VÀ TROUBLESHOOTING

### **1. 🔍 Debug Search Operations**
```cpp
// Thêm debug output vào searchByName
set<Contact*> ContactManager::searchByName(const string& name) {
    set<Contact*> results;
    
    cout << "🔍 Debug: Searching for name: " << name << endl;
    cout << "🔍 Debug: Total contacts: " << contactsByName.size() << endl;
    
    // ... existing code ...
    
    cout << "🔍 Debug: Found " << results.size() << " results" << endl;
    return results;
}
```

### **2. 🔍 Debug Index Synchronization**
```cpp
// Thêm debug output vào addToIndexes
void ContactManager::addToIndexes(Contact* contact) {
    cout << "🔄 Debug: Adding contact to indexes" << endl;
    cout << "🔄 Debug: Contact name: " << contact->getName() << endl;
    cout << "🔄 Debug: Contact ID: " << contact->getId() << endl;
    
    // ... existing code ...
    
    cout << "🔄 Debug: Index sizes after add:" << endl;
    cout << "  - Names: " << contactsByName.size() << endl;
    cout << "  - IDs: " << contactsById.size() << endl;
    cout << "  - Phones: " << contactsByPhone.size() << endl;
    cout << "  - Emails: " << contactsByEmail.size() << endl;
}
```

### **3. 🔍 Debug Memory Issues**
```cpp
// Thêm debug output vào destructor
ContactManager::~ContactManager() {
    cout << "🧹 Debug: ContactManager destructor called" << endl;
    cout << "🧹 Debug: Total contacts before cleanup: " << contactsByName.size() << endl;
    
    clearAll();
    
    cout << "🧹 Debug: Cleanup completed" << endl;
}
```

---

## 📚 BEST PRACTICES CHO DEVELOPER

### **1. 🔧 Code Organization**
- **Single Responsibility**: Mỗi method chỉ làm một việc
- **Clear Naming**: Tên method và variable rõ ràng, dễ hiểu
- **Consistent Formatting**: Format code nhất quán

### **2. 🛡️ Error Handling**
- **Try-catch blocks**: Luôn wrap code trong try-catch
- **Specific exceptions**: Sử dụng exception types cụ thể
- **User-friendly messages**: Thông báo lỗi thân thiện với user

### **3. 🚀 Performance Optimization**
- **Early return**: Return sớm nếu có thể
- **Efficient algorithms**: Sử dụng algorithms hiệu quả
- **Memory management**: Quản lý bộ nhớ cẩn thận

### **4. 🧪 Testing**
- **Unit tests**: Viết test cho từng method
- **Integration tests**: Test interaction giữa các components
- **Edge cases**: Test các trường hợp đặc biệt

---

## 🔮 HƯỚNG PHÁT TRIỂN TƯƠNG LAI

### **1. 🗄️ Database Integration**
- **SQLite**: Local database cho persistence
- **Connection pooling**: Quản lý database connections
- **Transaction support**: ACID properties

### **2. 🌐 Web Interface**
- **REST API**: RESTful API endpoints
- **Web UI**: HTML/CSS/JavaScript interface
- **Real-time updates**: WebSocket cho real-time

### **3. 🔐 Security Features**
- **Data encryption**: Mã hóa dữ liệu nhạy cảm
- **User authentication**: Hệ thống xác thực user
- **Access control**: Phân quyền truy cập

### **4. 📊 Advanced Features**
- **Full-text search**: Tìm kiếm nâng cao
- **Data analytics**: Phân tích dữ liệu
- **Export/Import**: Xuất/nhập dữ liệu

---

## 📝 KẾT LUẬN

Tài liệu này cung cấp cái nhìn toàn diện về luồng hoạt động của code trong hệ thống Quản lý Danh bạ Thông minh. Hiểu rõ các luồng này sẽ giúp developer:

1. **🔍 Debug hiệu quả**: Biết chính xác code chạy như thế nào
2. **🔧 Maintain dễ dàng**: Hiểu rõ dependencies và relationships
3. **🚀 Extend nhanh chóng**: Biết nơi nào để thêm tính năng mới
4. **🧪 Test chính xác**: Test đúng các scenarios quan trọng

**Lưu ý quan trọng:**
- **Callback pattern**: Hiểu rõ cách std::function hoạt động
- **Index synchronization**: Đảm bảo tất cả indexes luôn đồng bộ
- **Exception handling**: Xử lý lỗi một cách graceful
- **Memory management**: Quản lý bộ nhớ cẩn thận

Hãy sử dụng tài liệu này như một roadmap để navigate qua codebase và hiểu rõ cách hệ thống hoạt động! 🎯
