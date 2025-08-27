#ifndef EXCEPTION_LOGGER_H
#define EXCEPTION_LOGGER_H

#include "Exceptions.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

/**
 * @brief Lớp quản lý logging exception với timestamp và stack trace
 */
class ExceptionLogger {
private:
    static ExceptionLogger* instance;
    ofstream logFile;
    vector<string> errorHistory;
    bool enableFileLogging;
    bool enableConsoleLogging;
    
    /**
     * @brief Tạo timestamp hiện tại
     * @return String timestamp
     */
    string getCurrentTimestamp() {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    /**
     * @brief Lấy thông tin về file và line number (simulated)
     * @return String thông tin vị trí
     */
    string getLocationInfo() {
        // Trong thực tế có thể sử dụng __FILE__, __LINE__, __FUNCTION__
        return "Location: Unknown (Debug info not available)";
    }

public:
    ExceptionLogger() : enableFileLogging(true), enableConsoleLogging(true) {
        logFile.open("phonebook_errors.log", ios::app);
        if (!logFile.is_open()) {
            enableFileLogging = false;
        }
    }
    
    ~ExceptionLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    static ExceptionLogger* getInstance() {
        if (instance == nullptr) {
            instance = new ExceptionLogger();
        }
        return instance;
    }
    
    /**
     * @brief Log exception với thông tin chi tiết
     * @param exception Exception cần log
     * @param context Context bổ sung
     */
    template<typename ExceptionType>
    void logException(const ExceptionType& exception, const string& context = "") {
        string timestamp = getCurrentTimestamp();
        string location = getLocationInfo();
        string errorMsg = string("EXCEPTION: ") + exception.what();
        
        // Tạo log entry
        stringstream logEntry;
        logEntry << "[" << timestamp << "] " << errorMsg << endl;
        logEntry << "  Context: " << (context.empty() ? "General" : context) << endl;
        logEntry << "  " << location << endl;
        logEntry << "  Exception Type: " << typeid(exception).name() << endl;
        
        // Log vào file
        if (enableFileLogging && logFile.is_open()) {
            logFile << logEntry.str() << "  " << string(50, '-') << endl;
            logFile.flush();
        }
        
        // Log vào console nếu được bật
        if (enableConsoleLogging) {
            cout << "\033[31m[ERROR LOG]\033[0m " << errorMsg << endl;
        }
        
        // Lưu vào history
        errorHistory.push_back(logEntry.str());
        
        // Giới hạn history size
        if (errorHistory.size() > 100) {
            errorHistory.erase(errorHistory.begin());
        }
    }
    
    /**
     * @brief Log warning message
     * @param message Warning message
     * @param context Context bổ sung
     */
    void logWarning(const string& message, const string& context = "") {
        string timestamp = getCurrentTimestamp();
        stringstream logEntry;
        logEntry << "[" << timestamp << "] WARNING: " << message << endl;
        if (!context.empty()) {
            logEntry << "  Context: " << context << endl;
        }
        
        if (enableFileLogging && logFile.is_open()) {
            logFile << logEntry.str();
            logFile.flush();
        }
        
        if (enableConsoleLogging) {
            cout << "\033[33m[WARNING]\033[0m " << message << endl;
        }
    }
    
    /**
     * @brief Log info message
     * @param message Info message
     * @param context Context bổ sung
     */
    void logInfo(const string& message, const string& context = "") {
        string timestamp = getCurrentTimestamp();
        stringstream logEntry;
        logEntry << "[" << timestamp << "] INFO: " << message << endl;
        if (!context.empty()) {
            logEntry << "  Context: " << context << endl;
        }
        
        if (enableFileLogging && logFile.is_open()) {
            logFile << logEntry.str();
            logFile.flush();
        }
        
        if (enableConsoleLogging) {
            cout << "\033[32m[INFO]\033[0m " << message << endl;
        }
    }
    
    /**
     * @brief Hiển thị error history
     */
    void showErrorHistory() {
        if (errorHistory.empty()) {
            cout << "No error history available." << endl;
            return;
        }
        
        cout << "\n=== ERROR HISTORY (Last " << errorHistory.size() << " entries) ===" << endl;
        for (const string& entry : errorHistory) {
            cout << entry << endl;
        }
    }
    
    /**
     * @brief Lấy timestamp hiện tại (public method)
     */
    string getCurrentTimestamp() {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    /**
     * @brief Xóa error history
     */
    void clearErrorHistory() {
        errorHistory.clear();
        cout << "Error history cleared." << endl;
    }
    
    /**
     * @brief Bật/tắt file logging
     */
    void setFileLogging(bool enable) {
        enableFileLogging = enable;
    }
    
    /**
     * @brief Bật/tắt console logging
     */
    void setConsoleLogging(bool enable) {
        enableConsoleLogging = enable;
    }
    
    /**
     * @brief Kiểm tra xem có lỗi nào trong history không
     */
    bool hasErrors() const {
        return !errorHistory.empty();
    }
    
    /**
     * @brief Lấy số lượng lỗi trong history
     */
    size_t getErrorCount() const {
        return errorHistory.size();
    }
};

// Khởi tạo static member
ExceptionLogger* ExceptionLogger::instance = nullptr;

#endif // EXCEPTION_LOGGER_H
