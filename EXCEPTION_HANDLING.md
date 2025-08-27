# EXCEPTION HANDLING - HỆ THỐNG QUẢN LÝ DANH BẠ

## Tổng Quan

Tài liệu này mô tả chi tiết chiến lược xử lý exception trong hệ thống quản lý danh bạ, bao gồm custom exceptions, error handling patterns, và best practices để đảm bảo hệ thống hoạt động ổn định và graceful khi gặp lỗi.

## Kiến Trúc Exception Handling

### 🏗️ Exception Hierarchy

#### **Custom Exception Classes**
```cpp
// Base Exception Class
class ContactException : public std::exception {
private:
    string message;
    string errorCode;
    string module;
    int severity;
    
public:
    ContactException(const string& msg, const string& code = "UNKNOWN", 
                    const string& mod = "GENERAL", int sev = 1)
        : message(msg), errorCode(code), module(mod), severity(sev) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    
    string getErrorCode() const { return errorCode; }
    string getModule() const { return module; }
    int getSeverity() const { return severity; }
    
    virtual string getFullErrorInfo() const {
        return "[" + module + ":" + errorCode + "] " + message;
    }
};

// Specific Exception Types
class ValidationException : public ContactException {
public:
    ValidationException(const string& msg, const string& field = "")
        : ContactException(msg, "VALIDATION_ERROR", "VALIDATION", 2) {
        if (!field.empty()) {
            message = "Field '" + field + "': " + message;
        }
    }
};

class DataIntegrityException : public ContactException {
public:
    DataIntegrityException(const string& msg)
        : ContactException(msg, "DATA_INTEGRITY_ERROR", "DATABASE", 3) {}
};

class ResourceNotFoundException : public ContactException {
public:
    ResourceNotFoundException(const string& resource, const string& identifier = "")
        : ContactException("Resource '" + resource + "' not found" + 
                         (identifier.empty() ? "" : " with ID: " + identifier),
                         "RESOURCE_NOT_FOUND", "RESOURCE", 2) {}
};

class DuplicateResourceException : public ContactException {
public:
    DuplicateResourceException(const string& resource, const string& identifier = "")
        : ContactException("Resource '" + resource + "' already exists" +
                         (identifier.empty() ? "" : " with ID: " + identifier),
                         "DUPLICATE_RESOURCE", "RESOURCE", 2) {}
};

class SystemException : public ContactException {
public:
    SystemException(const string& msg)
        : ContactException(msg, "SYSTEM_ERROR", "SYSTEM", 4) {}
};
```

### 📊 Exception Categories

#### **Error Severity Levels**
```
Exception Severity Matrix:
┌─────────────────┬─────────────┬─────────────┬─────────────┬─────────────┐
│   Severity     │   Level     │   Impact    │   Action    │   Logging   │
├─────────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│       1        │    INFO     │    None     │   Log Only  │    DEBUG    │
│       2        │   WARNING   │    Minor    │   Continue  │     INFO    │
│       3        │    ERROR    │   Moderate  │   Retry     │    ERROR    │
│       4        │   CRITICAL  │    Major    │   Rollback  │   CRITICAL  │
│       5        │   FATAL     │   System    │   Shutdown  │   EMERGENCY │
└─────────────────┴─────────────┴─────────────┴─────────────┴─────────────┘
```

#### **Exception Types by Module**
```
Module Exception Mapping:
┌─────────────────┬─────────────────────────────────────────────────────────┐
│     Module     │                    Exception Types                      │
├─────────────────┼─────────────────────────────────────────────────────────┤
│   VALIDATION   │ ValidationException, FormatException, RangeException    │
│   DATABASE     │ DataIntegrityException, ConnectionException             │
│   RESOURCE     │ ResourceNotFoundException, DuplicateResourceException   │
│   SYSTEM       │ SystemException, MemoryException, NetworkException     │
│   UI           │ UserInputException, DisplayException                    │
│   EXTERNAL     │ APIException, ServiceUnavailableException              │
└─────────────────┴─────────────────────────────────────────────────────────┘
```

## Exception Handling Patterns

### 🔄 Try-Catch Patterns

#### **Basic Exception Handling**
```cpp
// Standard Exception Handling Pattern
class ContactManager {
public:
    bool addContact(const string& name) {
        try {
            // Validate input
            if (name.empty()) {
                throw ValidationException("Contact name cannot be empty", "name");
            }
            
            // Check for duplicates
            if (contactsByName.find(name) != contactsByName.end()) {
                throw DuplicateResourceException("Contact", name);
            }
            
            // Create contact
            Contact* contact = new Contact(name);
            
            // Add to indexes
            addToIndexes(contact);
            
            return true;
            
        } catch (const ValidationException& e) {
            logger.logWarning("Validation failed: " + e.what());
            throw; // Re-throw for UI handling
            
        } catch (const DuplicateResourceException& e) {
            logger.logWarning("Duplicate contact: " + e.what());
            throw;
            
        } catch (const exception& e) {
            logger.logError("Unexpected error in addContact: " + string(e.what()));
            throw SystemException("Failed to add contact: " + string(e.what()));
        }
    }
};
```

#### **Resource Management with RAII**
```cpp
// RAII Pattern for Resource Management
class ContactResourceManager {
private:
    Contact* contact;
    bool committed;
    
public:
    ContactResourceManager(Contact* c) : contact(c), committed(false) {}
    
    ~ContactResourceManager() {
        if (!committed && contact) {
            try {
                delete contact;
            } catch (...) {
                // Log but don't throw from destructor
                logger.logError("Failed to cleanup contact resource");
            }
        }
    }
    
    void commit() { committed = true; }
    Contact* get() { return contact; }
};

// Usage Example
bool addContactWithRAII(const string& name) {
    ContactResourceManager resourceManager(new Contact(name));
    
    try {
        // Validate and process
        if (name.empty()) {
            throw ValidationException("Name cannot be empty");
        }
        
        // Add to system
        addToIndexes(resourceManager.get());
        resourceManager.commit();
        
        return true;
        
    } catch (const exception& e) {
        // Resource automatically cleaned up
        throw;
    }
}
```

### 🛡️ Exception Safety Guarantees

#### **Exception Safety Levels**
```cpp
// Exception Safety Guarantees
class ContactManager {
public:
    // Basic Exception Safety - No resource leaks
    bool addContactBasic(const string& name) {
        Contact* contact = nullptr;
        try {
            contact = new Contact(name);
            addToIndexes(contact);
            return true;
        } catch (...) {
            delete contact; // Cleanup on failure
            throw;
        }
    }
    
    // Strong Exception Safety - All-or-nothing
    bool addContactStrong(const string& name) {
        // Create temporary state
        auto tempIndexes = createTemporaryIndexes();
        
        try {
            Contact* contact = new Contact(name);
            tempIndexes.addContact(contact);
            
            // Commit changes atomically
            commitIndexes(tempIndexes);
            return true;
            
        } catch (...) {
            // Rollback to previous state
            rollbackIndexes(tempIndexes);
            throw;
        }
    }
    
    // No-throw Guarantee - Never throws
    void cleanup() noexcept {
        try {
            clearAllContacts();
        } catch (...) {
            // Log but continue cleanup
            logger.logError("Cleanup error, continuing...");
        }
    }
};
```

## Error Recovery Strategies

### 🔄 Retry Mechanisms

#### **Exponential Backoff Retry**
```cpp
// Retry Strategy with Exponential Backoff
class RetryManager {
private:
    static const int MAX_RETRIES = 3;
    static const int BASE_DELAY_MS = 100;
    
public:
    template<typename Func>
    auto executeWithRetry(Func func, const string& operation) -> decltype(func()) {
        int retryCount = 0;
        int delayMs = BASE_DELAY_MS;
        
        while (retryCount < MAX_RETRIES) {
            try {
                return func();
                
            } catch (const DataIntegrityException& e) {
                retryCount++;
                if (retryCount >= MAX_RETRIES) {
                    throw SystemException("Operation '" + operation + 
                                        "' failed after " + to_string(MAX_RETRIES) + " retries");
                }
                
                // Wait before retry
                this_thread::sleep_for(chrono::milliseconds(delayMs));
                delayMs *= 2; // Exponential backoff
                
                logger.logInfo("Retrying operation '" + operation + 
                              "' (attempt " + to_string(retryCount) + ")");
            }
        }
        
        throw SystemException("Unexpected retry loop exit");
    }
};

// Usage Example
bool addContactWithRetry(const string& name) {
    RetryManager retryManager;
    
    return retryManager.executeWithRetry([&]() {
        return contactManager.addContact(name);
    }, "addContact");
}
```

#### **Circuit Breaker Pattern**
```cpp
// Circuit Breaker Implementation
class CircuitBreaker {
private:
    enum class State { CLOSED, OPEN, HALF_OPEN };
    
    State state;
    int failureCount;
    int threshold;
    chrono::steady_clock::time_point lastFailureTime;
    chrono::milliseconds timeout;
    
public:
    CircuitBreaker(int failThreshold = 5, int timeoutMs = 60000)
        : state(State::CLOSED), failureCount(0), threshold(failThreshold),
          timeout(timeoutMs) {}
    
    template<typename Func>
    auto execute(Func func) -> decltype(func()) {
        if (state == State::OPEN) {
            if (shouldAttemptReset()) {
                state = State::HALF_OPEN;
            } else {
                throw SystemException("Circuit breaker is OPEN");
            }
        }
        
        try {
            auto result = func();
            onSuccess();
            return result;
            
        } catch (const exception& e) {
            onFailure();
            throw;
        }
    }
    
private:
    void onSuccess() {
        failureCount = 0;
        state = State::CLOSED;
    }
    
    void onFailure() {
        failureCount++;
        lastFailureTime = chrono::steady_clock::now();
        
        if (failureCount >= threshold) {
            state = State::OPEN;
        }
    }
    
    bool shouldAttemptReset() {
        auto now = chrono::steady_clock::now();
        return (now - lastFailureTime) > timeout;
    }
};
```

## Logging và Monitoring

### 📝 Exception Logging

#### **Structured Exception Logging**
```cpp
// Exception Logger
class ExceptionLogger {
public:
    static void logException(const exception& e, const string& context = "") {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        
        LogEntry entry;
        entry.timestamp = ctime(&time_t);
        entry.exceptionType = typeid(e).name();
        entry.message = e.what();
        entry.context = context;
        entry.severity = getSeverityLevel(e);
        
        // Log to appropriate level
        switch (entry.severity) {
            case 1: logger.debug(entry.toString()); break;
            case 2: logger.info(entry.toString()); break;
            case 3: logger.warning(entry.toString()); break;
            case 4: logger.error(entry.toString()); break;
            case 5: logger.critical(entry.toString()); break;
        }
        
        // Store for analysis
        storeExceptionEntry(entry);
    }
    
private:
    static int getSeverityLevel(const exception& e) {
        if (dynamic_cast<const ValidationException*>(&e)) return 2;
        if (dynamic_cast<const ResourceNotFoundException*>(&e)) return 2;
        if (dynamic_cast<const DataIntegrityException*>(&e)) return 3;
        if (dynamic_cast<const SystemException*>(&e)) return 4;
        return 3; // Default
    }
};

// Log Entry Structure
struct LogEntry {
    string timestamp;
    string exceptionType;
    string message;
    string context;
    int severity;
    
    string toString() const {
        return "[" + timestamp + "] " + exceptionType + 
               " (Severity: " + to_string(severity) + "): " + message +
               (context.empty() ? "" : " [Context: " + context + "]");
    }
};
```

### 📊 Exception Analytics

#### **Exception Statistics**
```cpp
// Exception Analytics
class ExceptionAnalytics {
private:
    map<string, int> exceptionCounts;
    map<string, vector<LogEntry>> exceptionHistory;
    
public:
    void recordException(const LogEntry& entry) {
        exceptionCounts[entry.exceptionType]++;
        exceptionHistory[entry.exceptionType].push_back(entry);
    }
    
    void generateReport() {
        cout << "\n=== EXCEPTION ANALYTICS REPORT ===" << endl;
        
        for (const auto& [type, count] : exceptionCounts) {
            cout << type << ": " << count << " occurrences" << endl;
            
            // Show recent examples
            const auto& history = exceptionHistory[type];
            if (!history.empty()) {
                cout << "  Recent: " << history.back().message << endl;
            }
        }
        
        cout << "=================================" << endl;
    }
    
    void analyzeTrends() {
        // Analyze exception patterns over time
        // Identify recurring issues
        // Suggest preventive measures
    }
};
```

## Best Practices

### ✅ Exception Handling Guidelines

#### **Do's and Don'ts**
```
Exception Handling Best Practices:
┌─────────────────┬─────────────────────────────────────────────────────────┐
│      DO        │                        DON'T                            │
├─────────────────┼─────────────────────────────────────────────────────────┤
│ ✅ Use RAII    │ ❌ Catch and ignore exceptions                          │
│ ✅ Log errors  │ ❌ Throw from destructors                               │
│ ✅ Re-throw    │ ❌ Use exception specifications                         │
│ ✅ Clean up    │ ❌ Catch (...) without re-throwing                      │
│ ✅ Be specific │ ❌ Use exceptions for control flow                       │
└─────────────────┴─────────────────────────────────────────────────────────┘
```

#### **Exception Safety Checklist**
- [ ] **Resource Management**: Use RAII for all resources
- [ ] **Exception Specifications**: Avoid throw() specifications
- [ ] **Cleanup**: Ensure cleanup happens even with exceptions
- [ ] **Logging**: Log all exceptions with context
- [ ] **Recovery**: Implement appropriate recovery strategies
- [ ] **Testing**: Test exception scenarios thoroughly

### 🔧 Testing Exception Handling

#### **Exception Test Cases**
```cpp
// Exception Testing Framework
class ExceptionTestSuite {
public:
    void runAllTests() {
        testValidationExceptions();
        testResourceExceptions();
        testSystemExceptions();
        testExceptionRecovery();
        testExceptionSafety();
    }
    
private:
    void testValidationExceptions() {
        ContactManager manager;
        
        // Test empty name
        try {
            manager.addContact("");
            assert(false && "Should have thrown ValidationException");
        } catch (const ValidationException& e) {
            assert(e.getErrorCode() == "VALIDATION_ERROR");
            assert(e.getModule() == "VALIDATION");
        }
    }
    
    void testResourceExceptions() {
        ContactManager manager;
        
        // Test duplicate contact
        manager.addContact("John Doe");
        
        try {
            manager.addContact("John Doe");
            assert(false && "Should have thrown DuplicateResourceException");
        } catch (const DuplicateResourceException& e) {
            assert(e.getErrorCode() == "DUPLICATE_RESOURCE");
        }
    }
    
    void testExceptionRecovery() {
        // Test retry mechanism
        RetryManager retryManager;
        
        int attemptCount = 0;
        auto failingOperation = [&attemptCount]() -> bool {
            attemptCount++;
            if (attemptCount < 3) {
                throw DataIntegrityException("Temporary failure");
            }
            return true;
        };
        
        bool result = retryManager.executeWithRetry(failingOperation, "test");
        assert(result == true);
        assert(attemptCount == 3);
    }
};
```

## Kế Hoạch Cải Thiện

### 📋 Short-term Improvements (1-3 months)
- [ ] **Enhanced Logging**
  - Structured exception logging
  - Exception context capture
  - Performance impact monitoring

- [ ] **Better Error Messages**
  - User-friendly error descriptions
  - Actionable error suggestions
  - Localized error messages

### 📋 Medium-term Improvements (3-6 months)
- [ ] **Advanced Recovery**
  - Automatic retry mechanisms
  - Circuit breaker patterns
  - Graceful degradation

- [ ] **Exception Analytics**
  - Exception trend analysis
  - Predictive error detection
  - Performance impact analysis

### 📋 Long-term Improvements (6-12 months)
- [ ] **Intelligent Error Handling**
  - Machine learning for error prediction
  - Automated error resolution
  - Self-healing systems

- [ ] **Distributed Exception Handling**
  - Cross-service error propagation
  - Centralized error management
  - Global error recovery strategies

## Kết Luận

### 🎯 Tóm Tắt Exception Handling

Hệ thống quản lý danh bạ đã implement một **chiến lược exception handling toàn diện** với:

- **Custom exception hierarchy** cho các loại lỗi cụ thể
- **Exception safety guarantees** (Basic, Strong, No-throw)
- **Resource management** với RAII pattern
- **Recovery mechanisms** (retry, circuit breaker)
- **Comprehensive logging** và monitoring

### 🚀 Lợi Ích

1. **Stability**: Hệ thống không crash khi gặp lỗi
2. **Maintainability**: Dễ debug và troubleshoot
3. **User Experience**: Graceful error handling
4. **Monitoring**: Real-time error tracking
5. **Recovery**: Tự động khôi phục từ lỗi

### 💡 Khuyến Nghị

1. **Implement exception testing** trong CI/CD pipeline
2. **Monitor exception patterns** để phát hiện vấn đề sớm
3. **Train team** về exception handling best practices
4. **Regular review** exception handling strategy
5. **Document** tất cả custom exceptions và recovery procedures

---

*Tài liệu này sẽ được cập nhật định kỳ theo kinh nghiệm thực tế và feedback từ team.*
