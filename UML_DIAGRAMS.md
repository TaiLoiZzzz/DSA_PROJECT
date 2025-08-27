# SƠ ĐỒ UML - HỆ THỐNG QUẢN LÝ DANH BẠ

## Tổng Quan

Tài liệu này cung cấp các sơ đồ UML chi tiết cho hệ thống quản lý danh bạ, bao gồm Class Diagram, Sequence Diagram, Use Case Diagram và các diagram khác để mô tả kiến trúc và luồng hoạt động của hệ thống.

## 1. Class Diagram

### 🏗️ Class Diagram Chính

```mermaid
classDiagram
    class Contact {
        -string name
        -set<string> phoneNumbers
        -set<string> emails
        -string address
        -string notes
        -int id
        -static int nextId
        
        +Contact()
        +Contact(string name)
        +int getId()
        +string getName()
        +set<string> getPhoneNumbers()
        +set<string> getEmails()
        +string getAddress()
        +string getNotes()
        +void setName(string)
        +void setAddress(string)
        +void setNotes(string)
        +void addPhoneNumber(string)
        +void removePhoneNumber(string)
        +void addEmail(string)
        +void removeEmail(string)
        +bool hasPhoneNumber(string)
        +bool hasEmail(string)
        +void display()
        +string toString()
    }
    
    class ContactManager {
        -static ContactManager* instance
        -map<string, Contact*> contactsByName
        -map<string, Contact*> contactsByPhone
        -map<string, Contact*> contactsByEmail
        -map<int, Contact*> contactsById
        
        +static ContactManager* getInstance()
        +bool addContact(string)
        +bool removeContact(int)
        +bool removeContact(string)
        +Contact* findContact(int)
        +Contact* findContact(string)
        +set<Contact*> searchByName(string)
        +set<Contact*> searchByPhone(string)
        +set<Contact*> searchByEmail(string)
        +void displayAllContacts()
        +void displayContact(int)
        +void displayContact(string)
        +int getTotalContacts()
        +bool isEmpty()
        +void clearAll()
        -void removeFromIndexes(Contact*)
        -void addToIndexes(Contact*)
        -bool isValidPhone(string)
        -bool isValidEmail(string)
    }
    
    class ContactUI {
        -ContactManager* manager
        
        +ContactUI()
        +~ContactUI()
        +void run()
        +void showWelcome()
        +void showGoodbye()
        -void showMainMenu()
        -void showContactMenu()
        -void showSearchMenu()
        -string getStringInput(string)
        -int getIntInput(string)
        -void clearScreen()
        -void pause()
        -bool isValidPhoneNumber(string)
        -bool isValidEmail(string)
        -void addContact()
        -void editContact()
        -void deleteContact()
        -void viewContact()
        -void searchContacts()
        -void displayAllContacts()
    }
    
    class ContactException {
        -string message
        -string errorCode
        -string module
        -int severity
        
        +ContactException(string, string, string, int)
        +virtual const char* what()
        +string getErrorCode()
        +string getModule()
        +int getSeverity()
        +virtual string getFullErrorInfo()
    }
    
    class ValidationException {
        +ValidationException(string, string)
    }
    
    class ResourceNotFoundException {
        +ResourceNotFoundException(string, string)
    }
    
    class DuplicateResourceException {
        +DuplicateResourceException(string, string)
    }
    
    class SystemException {
        +SystemException(string)
    }
    
    ContactManager ||--o{ Contact : manages
    ContactUI --> ContactManager : uses
    ContactException <|-- ValidationException
    ContactException <|-- ResourceNotFoundException
    ContactException <|-- DuplicateResourceException
    ContactException <|-- SystemException
    ContactManager --> ContactException : throws
```

### 📊 Detailed Class Relationships

```mermaid
classDiagram
    class Contact {
        <<Entity>>
        -string name
        -set<string> phoneNumbers
        -set<string> emails
        -string address
        -string notes
        -int id
        -static int nextId
    }
    
    class ContactManager {
        <<Singleton>>
        -static ContactManager* instance
        -map<string, Contact*> contactsByName
        -map<string, Contact*> contactsByPhone
        -map<string, Contact*> contactsByEmail
        -map<int, Contact*> contactsById
    }
    
    class ContactUI {
        <<Controller>>
        -ContactManager* manager
    }
    
    class ContactException {
        <<Exception>>
        -string message
        -string errorCode
        -string module
        -int severity
    }
    
    ContactManager "1" ||--o{ "0..*" Contact : manages
    ContactUI "1" --> "1" ContactManager : uses
    ContactException <|-- ValidationException : inheritance
    ContactException <|-- ResourceNotFoundException : inheritance
    ContactException <|-- DuplicateResourceException : inheritance
    ContactException <|-- SystemException : inheritance
    ContactManager --> ContactException : throws
```

## 2. Sequence Diagram

### 🔄 Main Application Flow

```mermaid
sequenceDiagram
    participant User
    participant ContactUI
    participant ContactManager
    participant Contact
    participant ExceptionHandler
    
    User->>ContactUI: Start Application
    ContactUI->>ContactUI: showWelcome()
    ContactUI->>ContactUI: showMainMenu()
    
    loop Main Menu Loop
        User->>ContactUI: Select Option
        ContactUI->>ContactUI: Process Choice
        
        alt Add Contact
            ContactUI->>ContactUI: addContact()
            ContactUI->>ContactUI: getStringInput("Name")
            User->>ContactUI: Enter Name
            ContactUI->>ContactManager: addContact(name)
            ContactManager->>ContactManager: Validate Input
            ContactManager->>Contact: new Contact(name)
            ContactManager->>ContactManager: addToIndexes(contact)
            ContactManager-->>ContactUI: Success Response
            ContactUI-->>User: Contact Added Successfully
        else Edit Contact
            ContactUI->>ContactUI: editContact()
            ContactUI->>ContactManager: findContact(name)
            ContactManager-->>ContactUI: Contact Object
            ContactUI->>ContactUI: showEditContactMenu()
            User->>ContactUI: Select Edit Option
            ContactUI->>Contact: Update Properties
            ContactUI-->>User: Contact Updated
        else Search Contact
            ContactUI->>ContactUI: searchContacts()
            ContactUI->>ContactUI: showSearchMenu()
            User->>ContactUI: Select Search Type
            ContactUI->>ContactManager: searchByType(query)
            ContactManager-->>ContactUI: Search Results
            ContactUI-->>User: Display Results
        else Delete Contact
            ContactUI->>ContactUI: deleteContact()
            ContactUI->>ContactManager: removeContact(name)
            ContactManager->>ContactManager: removeFromIndexes()
            ContactManager->>Contact: Delete Object
            ContactManager-->>ContactUI: Success Response
            ContactUI-->>User: Contact Deleted
        end
        
        ContactUI->>ContactUI: pause()
        ContactUI->>ContactUI: clearScreen()
    end
    
    User->>ContactUI: Exit
    ContactUI->>ContactUI: showGoodbye()
    ContactUI->>User: Application Closed
```

### 🔍 Search Operation Flow

```mermaid
sequenceDiagram
    participant User
    participant ContactUI
    participant ContactManager
    participant Contact
    participant ExceptionHandler
    
    User->>ContactUI: Select Search
    ContactUI->>ContactUI: showSearchMenu()
    User->>ContactUI: Choose Search Type
    ContactUI->>ContactUI: getStringInput("Query")
    User->>ContactUI: Enter Search Query
    
    alt Search by Name
        ContactUI->>ContactManager: searchByName(query)
        ContactManager->>ContactManager: contactsByName.find(query)
        ContactManager-->>ContactUI: Set of Contacts
    else Search by Phone
        ContactUI->>ContactManager: searchByPhone(query)
        ContactManager->>ContactManager: contactsByPhone.find(query)
        ContactManager-->>ContactUI: Set of Contacts
    else Search by Email
        ContactUI->>ContactUI: searchByEmail(query)
        ContactManager->>ContactManager: contactsByEmail.find(query)
        ContactManager-->>ContactUI: Set of Contacts
    end
    
    ContactUI->>ContactUI: displaySearchResults(results)
    ContactUI-->>User: Show Results
```

### ➕ Add Contact Flow

```mermaid
sequenceDiagram
    participant User
    participant ContactUI
    participant ContactManager
    participant Contact
    participant ExceptionHandler
    
    User->>ContactUI: Select Add Contact
    ContactUI->>ContactUI: getStringInput("Name")
    User->>ContactUI: Enter Contact Name
    
    ContactUI->>ContactManager: addContact(name)
    
    alt Validation Error
        ContactManager->>ExceptionHandler: throw ValidationException
        ExceptionHandler-->>ContactUI: Validation Error
        ContactUI-->>User: Show Error Message
    else Duplicate Error
        ContactManager->>ContactManager: Check Duplicate
        ContactManager->>ExceptionHandler: throw DuplicateResourceException
        ExceptionHandler-->>ContactUI: Duplicate Error
        ContactUI-->>User: Show Error Message
    else Success
        ContactManager->>Contact: new Contact(name)
        ContactManager->>ContactManager: addToIndexes(contact)
        ContactManager-->>ContactUI: Success
        ContactUI->>ContactUI: showAddDetailsMenu()
        
        loop Add Details
            User->>ContactUI: Choose Detail Type
            alt Add Phone
                ContactUI->>Contact: addPhoneNumber(phone)
            else Add Email
                ContactUI->>Contact: addEmail(email)
            else Add Address
                ContactUI->>Contact: setAddress(address)
            else Add Notes
                ContactUI->>Contact: setNotes(notes)
            end
        end
        
        ContactUI-->>User: Contact Created Successfully
    end
```

## 3. Use Case Diagram

### 👥 Use Case Overview

```mermaid
graph TB
    subgraph "Contact Management System"
        subgraph "Actors"
            User[👤 User]
            Admin[👨‍💼 Administrator]
            System[🖥️ System]
        end
        
        subgraph "Core Use Cases"
            UC1[➕ Add Contact]
            UC2[✏️ Edit Contact]
            UC3[🗑️ Delete Contact]
            UC4[🔍 Search Contact]
            UC5[📋 View All Contacts]
            UC6[📊 View Statistics]
        end
        
        subgraph "Advanced Use Cases"
            UC7[📱 Manage Phone Numbers]
            UC8[📧 Manage Emails]
            UC9[📍 Manage Address]
            UC10[📝 Manage Notes]
            UC11[💾 Backup Data]
            UC12[📥 Import/Export]
        end
        
        subgraph "System Use Cases"
            UC13[🔐 Authentication]
            UC14[📝 Logging]
            UC15[⚙️ Configuration]
            UC16[🔄 Data Sync]
        end
    end
    
    User --> UC1
    User --> UC2
    User --> UC3
    User --> UC4
    User --> UC5
    User --> UC6
    User --> UC7
    User --> UC8
    User --> UC9
    User --> UC10
    
    Admin --> UC11
    Admin --> UC12
    Admin --> UC13
    Admin --> UC15
    
    System --> UC14
    System --> UC16
    
    UC1 --> UC7
    UC1 --> UC8
    UC1 --> UC9
    UC1 --> UC10
    UC2 --> UC7
    UC2 --> UC8
    UC2 --> UC9
    UC2 --> UC10
```

## 4. Component Diagram

### 🧩 System Components

```mermaid
graph TB
    subgraph "User Interface Layer"
        UI[ContactUI]
        Menu[Menu System]
        Input[Input Handler]
        Display[Display Manager]
    end
    
    subgraph "Business Logic Layer"
        Manager[ContactManager]
        Validator[Validation Engine]
        Search[Search Engine]
        Index[Index Manager]
    end
    
    subgraph "Data Layer"
        Contact[Contact Entity]
        Storage[Data Storage]
        Cache[Memory Cache]
    end
    
    subgraph "Exception Handling"
        Exception[Exception Handler]
        Logger[Logging System]
        Recovery[Recovery Manager]
    end
    
    UI --> Manager
    UI --> Exception
    Manager --> Contact
    Manager --> Validator
    Manager --> Search
    Manager --> Index
    Manager --> Exception
    Contact --> Storage
    Contact --> Cache
    Exception --> Logger
    Exception --> Recovery
```

## 5. State Diagram

### 🔄 Contact Lifecycle

```mermaid
stateDiagram-v2
    [*] --> Empty
    Empty --> Creating : Start Creation
    Creating --> Validating : Input Name
    
    Validating --> Valid : Validation Pass
    Validating --> Invalid : Validation Fail
    Invalid --> Creating : Retry
    
    Valid --> Adding : Add to System
    Adding --> Active : Successfully Added
    Adding --> Error : Add Failed
    Error --> Creating : Retry
    
    Active --> Editing : Start Edit
    Editing --> Updating : Save Changes
    Updating --> Active : Update Success
    Updating --> Error : Update Failed
    
    Active --> Deleting : Start Delete
    Deleting --> Removed : Delete Success
    Deleting --> Error : Delete Failed
    
    Active --> Searching : Search Request
    Searching --> Active : Return to Active
    
    Error --> Recovery : Start Recovery
    Recovery --> Active : Recovery Success
    Recovery --> Error : Recovery Failed
    
    Removed --> [*]
```

## 6. Activity Diagram

### 🔄 Main Application Flow

```mermaid
flowchart TD
    Start([Start Application]) --> Init[Initialize System]
    Init --> Welcome[Show Welcome Screen]
    Welcome --> MainMenu[Display Main Menu]
    
    MainMenu --> Choice{User Choice}
    
    Choice -->|1| Add[Add Contact]
    Choice -->|2| Manage[Manage Contact]
    Choice -->|3| Search[Search Contact]
    Choice -->|4| View[View All Contacts]
    Choice -->|5| Stats[View Statistics]
    Choice -->|6| Exit[Exit Application]
    
    Add --> Validate[Validate Input]
    Validate --> Valid{Valid?}
    Valid -->|No| Error[Show Error]
    Valid -->|Yes| Create[Create Contact]
    Create --> Success[Show Success]
    
    Manage --> ManageMenu[Show Manage Menu]
    ManageMenu --> Edit[Edit Contact]
    ManageMenu --> Delete[Delete Contact]
    ManageMenu --> ViewDetail[View Details]
    
    Search --> SearchMenu[Show Search Menu]
    SearchMenu --> SearchByName[Search by Name]
    SearchMenu --> SearchByPhone[Search by Phone]
    SearchMenu --> SearchByEmail[Search by Email]
    
    View --> DisplayAll[Display All Contacts]
    Stats --> ShowStats[Show Statistics]
    
    Error --> MainMenu
    Success --> MainMenu
    Edit --> MainMenu
    Delete --> MainMenu
    ViewDetail --> MainMenu
    SearchByName --> MainMenu
    SearchByPhone --> MainMenu
    SearchByEmail --> MainMenu
    DisplayAll --> MainMenu
    ShowStats --> MainMenu
    
    Exit --> End([End Application])
```

## 7. Package Diagram

### 📦 System Architecture

```mermaid
graph TB
    subgraph "Contact Management System"
        subgraph "UI Package"
            ContactUI
            MenuSystem
            InputHandler
            DisplayManager
        end
        
        subgraph "Core Package"
            ContactManager
            Contact
            ContactException
        end
        
        subgraph "Exception Package"
            ValidationException
            ResourceNotFoundException
            DuplicateResourceException
            SystemException
        end
        
        subgraph "Utility Package"
            Logger
            Validator
            IndexManager
        end
    end
    
    UI Package --> Core Package
    Core Package --> Exception Package
    Core Package --> Utility Package
    Exception Package --> Utility Package
```

## 8. Object Diagram

### 🎯 System State Example

```mermaid
graph TB
    subgraph "ContactManager Instance"
        CM[ContactManager: instance]
        CM_ByName[contactsByName: map]
        CM_ByPhone[contactsByPhone: map]
        CM_ByEmail[contactsByEmail: map]
        CM_ById[contactsById: map]
    end
    
    subgraph "Contact Objects"
        C1[Contact: id=1, name="John Doe"]
        C2[Contact: id=2, name="Jane Smith"]
        C3[Contact: id=3, name="Bob Johnson"]
    end
    
    subgraph "Index Mappings"
        CM_ByName --> C1
        CM_ByName --> C2
        CM_ByName --> C3
        
        CM_ByPhone --> C1
        CM_ByPhone --> C2
        CM_ByPhone --> C3
        
        CM_ByEmail --> C1
        CM_ByEmail --> C2
        CM_ByEmail --> C3
        
        CM_ById --> C1
        CM_ById --> C2
        CM_ById --> C3
    end
```

## 9. Deployment Diagram

### 🚀 System Deployment

```mermaid
graph TB
    subgraph "Development Environment"
        Dev[Development Machine]
        Dev --> DevUI[ContactUI.exe]
        Dev --> DevData[Local Data]
    end
    
    subgraph "Production Environment"
        Prod[Production Server]
        Prod --> ProdUI[ContactUI.exe]
        Prod --> ProdData[Persistent Storage]
        Prod --> ProdLog[Log Files]
    end
    
    subgraph "User Machines"
        User1[User 1 PC]
        User2[User 2 PC]
        User3[User 3 PC]
    end
    
    DevUI --> DevData
    ProdUI --> ProdData
    ProdUI --> ProdLog
    
    User1 --> Prod
    User2 --> Prod
    User3 --> Prod
```

## 10. Timing Diagram

### ⏱️ Operation Timing

```mermaid
sequenceDiagram
    participant User
    participant UI
    participant Manager
    participant Contact
    
    Note over User,Contact: Add Contact Operation Timeline
    
    User->>UI: Input Name (0ms)
    UI->>Manager: addContact() (5ms)
    Manager->>Manager: Validate (10ms)
    Manager->>Contact: Create Object (15ms)
    Manager->>Manager: Add to Indexes (20ms)
    Manager-->>UI: Success Response (25ms)
    UI-->>User: Display Success (30ms)
    
    Note over User,Contact: Total Time: 30ms
```

## Kết Luận

### 🎯 Tóm Tắt UML Diagrams

Các sơ đồ UML trên cung cấp cái nhìn toàn diện về:

1. **Class Structure**: Kiến trúc classes và relationships
2. **System Flow**: Luồng hoạt động của hệ thống
3. **User Interactions**: Cách users tương tác với system
4. **Component Architecture**: Cấu trúc components
5. **State Management**: Quản lý trạng thái của objects
6. **System Deployment**: Cách hệ thống được triển khai

### 🚀 Lợi Ích

- **Documentation**: Tài liệu kỹ thuật chi tiết
- **Communication**: Giao tiếp hiệu quả giữa team members
- **Design Review**: Review và validate thiết kế
- **Implementation Guide**: Hướng dẫn implement
- **Maintenance**: Dễ dàng maintain và extend system

### 💡 Sử Dụng

1. **Development**: Hướng dẫn implement cho developers
2. **Testing**: Thiết kế test cases
3. **Documentation**: Tài liệu kỹ thuật
4. **Training**: Training cho team members mới
5. **Architecture Review**: Review kiến trúc hệ thống

---

*Các sơ đồ UML này sẽ được cập nhật khi có thay đổi trong kiến trúc hệ thống.*
