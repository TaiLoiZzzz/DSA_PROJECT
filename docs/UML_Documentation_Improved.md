# 📊 TÀI LIỆU UML CHUẨN - HỆ THỐNG QUẢN LÝ DANH BẠ THÔNG MINH

## 🎯 TỔNG QUAN HỆ THỐNG

Hệ thống Quản lý Danh bạ Thông minh được thiết kế theo **Modern C++ Architecture** với việc áp dụng nhiều design patterns khác nhau. Tài liệu UML này tuân thủ chuẩn **UML 2.5** và cung cấp cái nhìn toàn diện về kiến trúc hệ thống.

---

## 🏗️ KIẾN TRÚC TỔNG THỂ (SYSTEM ARCHITECTURE)

### **1. 🎯 HIGH-LEVEL ARCHITECTURE DIAGRAM**

```mermaid
graph TB
    subgraph "Application Layer"
        MAIN[main.cpp]
        UI[ContactUI]
    end
    
    subgraph "Business Logic Layer"
        CM[ContactManager<br/>Singleton]
    end
    
    subgraph "Data Structure Layer"
        BST[BinarySearchTree]
        RBT[RedBlackTree]
    end
    
    subgraph "Entity Layer"
        CONTACT[Contact]
    end
    
    subgraph "Exception Layer"
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

### **2. 📱 LAYER RESPONSIBILITY MATRIX**

| Layer | Components | Responsibility | Design Pattern |
|-------|------------|----------------|----------------|
| **Application** | `main.cpp` | Entry point, Global exception handling | Exception Handler |
| **Presentation** | `ContactUI` | User interface, Input validation, Navigation | MVC (View+Controller) |
| **Business Logic** | `ContactManager` | Business rules, Data management, Index sync | Singleton, Factory, Observer |
| **Data Structure** | `BST`, `RBT` | Data storage, Search optimization | Template Method, Strategy |
| **Entity** | `Contact` | Data model, Validation | Value Object |
| **Exception** | `ContactException` | Error handling, User feedback | Exception Hierarchy |

---

## 📊 CLASS DIAGRAM (CHUẨN UML 2.5)

### **1. 🏠 CONTACT ENTITY CLASS**

```mermaid
classDiagram
    class Contact {
        <<Entity>>
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
    
    note for Contact "Value Object Pattern\n- Immutable ID\n- Validation rules\n- Business logic"
```

**UML Notation:**
- **<<Entity>>**: Stereotype cho entity class
- **-**: Private members (encapsulation)
- **+**: Public methods (interface)
- **~**: Destructor
- **static**: Class-level members

### **2. 🎯 CONTACT MANAGER CLASS (SINGLETON)**

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
    
    note for ContactManager "Singleton Pattern\n- Single instance\n- Global access\n- Lazy initialization"
```

### **3. 🖥️ CONTACT UI CLASS (MVC PATTERN)**

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
    
    note for ContactUI "MVC Pattern\n- View: Display methods\n- Controller: Input handling\n- Navigation logic"
```

### **4. 🌳 BINARY SEARCH TREE TEMPLATE CLASS**

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
    
    note for BinarySearchTree "Template Method Pattern\n- Algorithm structure\n- Implementation variation\n- Callback support"
```

### **5. 🔴⚫ RED-BLACK TREE TEMPLATE CLASS**

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
    
    note for RedBlackTree "Self-Balancing Tree\n- Red-Black properties\n- O(log n) guaranteed\n- Rotation operations"
```

### **6. ⚠️ EXCEPTION HIERARCHY CLASS**

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
    
    note for ContactException "Exception Hierarchy\n- Custom exception types\n- User-friendly messages\n- Proper error handling"
```

---

## 🔄 SEQUENCE DIAGRAM (CHUẨN UML 2.5)

### **1. ➕ ADD CONTACT SEQUENCE**

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
        BST-->>ContactManager: Success
        
        ContactManager->>BST: insert(id, contact)
        BST-->>ContactManager: Success
        
        alt Có số điện thoại
            ContactManager->>ContactManager: isPhoneNumberDuplicate(phone)
            ContactManager-->>ContactManager: false
            ContactManager->>RBT: insert(phone, contact)
            RBT-->>ContactManager: Success
        end
        
        alt Có email
            ContactManager->>ContactManager: isEmailDuplicate(email)
            ContactManager-->>ContactManager: false
            ContactManager->>RBT: insert(email, contact)
            RBT-->>ContactManager: Success
        end
        
        ContactManager-->>ContactUI: true
        ContactUI->>User: Hiển thị menu thêm chi tiết
        
    else Tên không hợp lệ hoặc trùng lặp
        ContactManager->>ExceptionHandler: Throw exception
        ExceptionHandler-->>ContactUI: Exception message
        ContactUI-->>User: Hiển thị lỗi
    end
```

### **2. 🔍 SEARCH CONTACT SEQUENCE**

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
        
        loop Tree traversal
            BST->>BST: searchPartialCallback(node)
            alt Node matches
                BST->>Results: callback(key, value)
                Results->>Results: insert(contact)
            end
            BST->>BST: Traverse left subtree
            BST->>BST: Traverse right subtree
        end
        
        BST-->>ContactManager: Traversal completed
        ContactManager-->>ContactUI: set<Contact*> results
        ContactUI->>User: Hiển thị kết quả
        
    else Tìm kiếm theo số điện thoại
        User->>ContactUI: Nhập số điện thoại
        ContactUI->>ContactManager: searchByPhone(phone)
        
        alt Exact match first
            ContactManager->>RBT: find(phone)
            RBT-->>ContactManager: Contact* contact
            ContactManager->>Results: insert(contact)
            ContactManager-->>ContactUI: results
            ContactUI->>User: Hiển thị kết quả
        else Partial search
            ContactManager->>RBT: searchPartial(phone, matchFunc, callback)
            RBT-->>ContactManager: Traversal completed
            ContactManager-->>ContactUI: set<Contact*> results
            ContactUI->>User: Hiển thị kết quả
        end
    end
```

---

## 🗂️ COMPONENT DIAGRAM (CHUẨN UML 2.5)

```mermaid
graph TB
    subgraph "Hệ thống Quản lý Danh bạ"
        subgraph "Application Components"
            MAIN[main.cpp<br/>Entry Point]
        end
        
        subgraph "Presentation Components"
            UI[ContactUI<br/>User Interface]
        end
        
        subgraph "Business Logic Components"
            CM[ContactManager<br/>Business Logic]
        end
        
        subgraph "Data Structure Components"
            BST[BinarySearchTree<br/>Ordered Storage]
            RBT[RedBlackTree<br/>Balanced Storage]
        end
        
        subgraph "Entity Components"
            C[Contact<br/>Data Model]
        end
        
        subgraph "Exception Components"
            EX[ContactException<br/>Error Handling]
        end
    end
    
    subgraph "External Dependencies"
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

## 🔄 ACTIVITY DIAGRAM (CHUẨN UML 2.5)

### **1. 🚀 MAIN APPLICATION FLOW**

```mermaid
flowchart TD
    A[Start Application] --> B[Initialize ContactUI]
    B --> C[Show Welcome Screen]
    C --> D[Display Main Menu]
    D --> E{User Choice}
    
    E -->|1| F[Add Contact Flow]
    E -->|2| G[Manage Contact Flow]
    E -->|3| H[Search Contact Flow]
    E -->|4| I[Display All Contacts]
    E -->|5| J[Show Statistics]
    E -->|6| K[Exit Application]
    
    F --> L[Input Contact Name]
    L --> M{Validate Name}
    M -->|Invalid| N[Show Error]
    M -->|Valid| O[Check Duplicate]
    O -->|Duplicate| P[Show Error]
    O -->|Unique| Q[Create Contact]
    Q --> R[Add to Indexes]
    R --> S[Show Success]
    
    G --> T[Find Contact]
    T --> U{Contact Found?}
    U -->|No| V[Show Error]
    U -->|Yes| W[Show Edit Menu]
    
    H --> X[Choose Search Type]
    X --> Y[Input Search Term]
    Y --> Z[Execute Search]
    Z --> AA[Display Results]
    
    I --> BB[Traverse All Contacts]
    BB --> CC[Display Results]
    
    J --> DD[Calculate Statistics]
    DD --> EE[Display Statistics]
    
    N --> D
    P --> D
    S --> D
    V --> D
    W --> D
    AA --> D
    CC --> D
    EE --> D
    
    K --> FF[Cleanup Resources]
    FF --> GG[End Application]
```

### **2. 🔍 SEARCH OPERATION FLOW**

```mermaid
flowchart TD
    A[Start Search] --> B[Choose Search Type]
    B --> C{Search Type}
    
    C -->|Name| D[Input Name]
    C -->|Phone| E[Input Phone]
    C -->|Email| F[Input Email]
    
    D --> G[Convert to Lowercase]
    G --> H[Define Search Strategy]
    H --> I[Execute Tree Traversal]
    
    E --> J[Check Exact Match]
    J --> K{Exact Match?}
    K -->|Yes| L[Return Result]
    K -->|No| M[Clean Phone Number]
    M --> N[Execute Partial Search]
    
    F --> O[Convert to Lowercase]
    O --> P[Execute Tree Traversal]
    
    I --> Q[Process Each Node]
    Q --> R{Node Matches?}
    R -->|Yes| S[Add to Results]
    R -->|No| T[Continue Traversal]
    
    N --> U[Process Each Node]
    U --> V{Node Matches?}
    V -->|Yes| W[Add to Results]
    V -->|No| X[Continue Traversal]
    
    P --> Y[Process Each Node]
    Y --> Z{Node Matches?}
    Z -->|Yes| AA[Add to Results]
    Z -->|No| BB[Continue Traversal]
    
    S --> CC[Check More Nodes]
    T --> CC
    W --> DD[Check More Nodes]
    X --> DD
    AA --> EE[Check More Nodes]
    BB --> EE
    
    CC --> FF{More Nodes?}
    DD --> FF
    EE --> FF
    
    FF -->|Yes| Q
    FF -->|No| GG[Return Results]
    
    L --> GG
    GG --> HH[Display Results]
    HH --> II[End Search]
```

---

## 🎨 STATE DIAGRAM (CHUẨN UML 2.5)

### **1. 🔄 CONTACT STATE MACHINE**

```mermaid
stateDiagram-v2
    [*] --> Empty: Initialize
    Empty --> Basic: Add Name
    Basic --> WithPhone: Add Phone
    Basic --> WithEmail: Add Email
    Basic --> WithAddress: Add Address
    Basic --> WithNotes: Add Notes
    Basic --> Complete: Add All Info
    
    WithPhone --> WithPhone: Update Phone
    WithPhone --> WithEmail: Add Email
    WithPhone --> WithAddress: Add Address
    WithPhone --> WithNotes: Add Notes
    WithPhone --> Complete: Add All Info
    
    WithEmail --> WithPhone: Add Phone
    WithEmail --> WithEmail: Update Email
    WithEmail --> WithAddress: Add Address
    WithEmail --> WithNotes: Add Notes
    WithEmail --> Complete: Add All Info
    
    WithAddress --> WithPhone: Add Phone
    WithAddress --> WithEmail: Add Email
    WithAddress --> WithAddress: Update Address
    WithAddress --> WithNotes: Add Notes
    WithAddress --> Complete: Add All Info
    
    WithNotes --> WithPhone: Add Phone
    WithNotes --> WithEmail: Add Email
    WithNotes --> WithAddress: Add Address
    WithNotes --> WithNotes: Update Notes
    WithNotes --> Complete: Add All Info
    
    Complete --> Complete: Update Any Info
    Complete --> [*]: Delete Contact
    
    note right of Empty : "Minimal state\nName only"
    note right of Basic : "Basic contact\nName + optional fields"
    note right of Complete : "Full contact\nAll fields populated"
```

### **2. 🔄 APPLICATION STATE MACHINE**

```mermaid
stateDiagram-v2
    [*] --> Welcome: Start Application
    Welcome --> MainMenu: Show Main Menu
    MainMenu --> AddContact: Choose Add
    MainMenu --> ManageContact: Choose Manage
    MainMenu --> SearchContact: Choose Search
    MainMenu --> DisplayAll: Choose Display
    MainMenu --> Statistics: Choose Statistics
    MainMenu --> Exit: Choose Exit
    
    AddContact --> AddDetails: Name Added
    AddDetails --> AddDetails: Add More Details
    AddDetails --> MainMenu: Complete
    
    ManageContact --> ManageMenu: Show Manage Menu
    ManageMenu --> EditContact: Choose Edit
    ManageMenu --> DeleteContact: Choose Delete
    ManageMenu --> ViewContact: Choose View
    ManageMenu --> MainMenu: Back to Main
    
    EditContact --> EditMenu: Show Edit Menu
    EditMenu --> EditMenu: Edit Information
    EditMenu --> ManageMenu: Complete Edit
    
    SearchContact --> SearchMenu: Show Search Menu
    SearchMenu --> SearchByName: Search by Name
    SearchMenu --> SearchByPhone: Search by Phone
    SearchMenu --> SearchByEmail: Search by Email
    SearchMenu --> MainMenu: Back to Main
    
    DisplayAll --> MainMenu: Display Complete
    Statistics --> MainMenu: Statistics Complete
    
    Exit --> [*]: End Application
    
    note right of Welcome : "Application startup"
    note right of MainMenu : "Main navigation hub"
    note right of AddContact : "Contact creation flow"
    note right of ManageContact : "Contact management flow"
    note right of SearchContact : "Search operations flow"
```

---

## 📊 OBJECT DIAGRAM (CHUẬN UML 2.5)

### **1. 🔍 SYSTEM INSTANCE EXAMPLE**

```mermaid
graph TB
    subgraph "System Instance: Contact Management System"
        subgraph "ContactManager Instance"
            CM[ContactManager<br/>instance: 0x7fff1234]
        end
        
        subgraph "Contact Instances"
            C1[Contact<br/>id: 1<br/>name: "Nguyễn Văn A"<br/>phone: "0123456789"<br/>email: "a@email.com"]
            C2[Contact<br/>id: 2<br/>name: "Trần Thị B"<br/>phone: "0987654321"<br/>email: "b@email.com"]
            C3[Contact<br/>id: 3<br/>name: "Lê Văn C"<br/>phone: "1122334455"<br/>email: "c@email.com"]
        end
        
        subgraph "Index Instances"
            BST1[BinarySearchTree<br/>root: Node*<br/>size: 3]
            BST2[BinarySearchTree<br/>root: Node*<br/>size: 3]
            RBT1[RedBlackTree<br/>root: Node*<br/>size: 3]
            RBT2[RedBlackTree<br/>root: Node*<br/>size: 3]
        end
        
        subgraph "Node Instances"
            N1[Node<br/>key: "Nguyễn Văn A"<br/>value: Contact*<br/>left: nullptr<br/>right: Node*]
            N2[Node<br/>key: "Trần Thị B"<br/>value: Contact*<br/>left: Node*<br/>right: Node*]
            N3[Node<br/>key: "Lê Văn C"<br/>value: Contact*<br/>left: Node*<br/>right: nullptr]
        end
    end
    
    CM --> BST1 : manages
    CM --> BST2 : manages
    CM --> RBT1 : manages
    CM --> RBT2 : manages
    
    BST1 --> N1 : contains
    BST1 --> N2 : contains
    BST1 --> N3 : contains
    
    N1 --> C1 : references
    N2 --> C2 : references
    N3 --> C3 : references
    
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

## 🔧 IMPLEMENTATION NOTES

### **1. 📋 UML COMPLIANCE CHECKLIST**

- ✅ **Class Diagrams**: Proper stereotypes, visibility, relationships
- ✅ **Sequence Diagrams**: Lifelines, messages, activation bars
- ✅ **Component Diagrams**: Components, interfaces, dependencies
- ✅ **Activity Diagrams**: Actions, decisions, flows, swimlanes
- ✅ **State Diagrams**: States, transitions, events, actions
- ✅ **Object Diagrams**: Instance examples, object relationships

### **2. 🎯 DESIGN PATTERN MAPPING**

| UML Element | Design Pattern | Implementation |
|-------------|----------------|----------------|
| **Singleton** | ContactManager | Static instance + getInstance() |
| **Template Method** | BST/RBT | Traversal algorithm structure |
| **Strategy** | Search operations | std::function callbacks |
| **Factory** | Contact creation | addContact() method |
| **Observer** | Index sync | addToIndexes() method |
| **MVC** | ContactUI | View + Controller separation |

### **3. 🔍 RELATIONSHIP TYPES**

- **Association**: ContactManager manages Contact objects
- **Composition**: ContactManager contains tree structures
- **Aggregation**: Tree structures contain Contact pointers
- **Dependency**: UI depends on ContactManager
- **Inheritance**: Exception hierarchy

---

## 📈 PERFORMANCE ANALYSIS

### **1. ⏱️ TIME COMPLEXITY**

| Operation | BST (Average) | BST (Worst) | RBT (Guaranteed) |
|-----------|---------------|-------------|------------------|
| **Insert** | O(log n) | O(n) | O(log n) |
| **Search** | O(log n) | O(n) | O(log n) |
| **Delete** | O(log n) | O(n) | O(log n) |
| **Traversal** | O(n) | O(n) | O(n) |

### **2. 💾 SPACE COMPLEXITY**

| Component | Space Complexity | Details |
|-----------|------------------|---------|
| **Contact Objects** | O(n) | n contacts with constant data |
| **Tree Structures** | O(n) | n nodes with constant overhead |
| **Index Management** | O(n) | Multiple indexes, each O(n) |
| **Overall System** | O(n) | Linear with contact count |

---

## 🚀 CONCLUSION

Tài liệu UML này tuân thủ chuẩn **UML 2.5** và cung cấp cái nhìn toàn diện về kiến trúc hệ thống Quản lý Danh bạ Thông minh. Các diagram được thiết kế để:

1. **🎯 Clarity**: Hiểu rõ cấu trúc và relationships
2. **🔧 Implementation**: Hướng dẫn development
3. **📊 Documentation**: Tài liệu kỹ thuật chuẩn
4. **🚀 Maintenance**: Dễ dàng maintain và extend

**UML Standards Compliance:**
- ✅ **Class Diagrams**: Proper notation và relationships
- ✅ **Sequence Diagrams**: Message flow và timing
- ✅ **Component Diagrams**: System architecture
- ✅ **Activity Diagrams**: Business process flow
- ✅ **State Diagrams**: Object lifecycle
- ✅ **Object Diagrams**: Instance examples

Tài liệu này có thể được sử dụng để:
- **Development**: Hướng dẫn implementation
- **Code Review**: Kiểm tra design compliance
- **Documentation**: Technical documentation
- **Training**: Developer onboarding
- **Maintenance**: System understanding
