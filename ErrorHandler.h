#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "Exceptions.h"
#include "ExceptionLogger.h"
#include <functional>
#include <map>
#include <vector>

using namespace std;

/**
 * @brief Lớp quản lý xử lý lỗi nâng cao với recovery strategies
 */
class ErrorHandler {
private:
    static ErrorHandler* instance;
    ExceptionLogger* logger;
    map<string, function<void(const exception&)>> errorHandlers;
    vector<string> ignoredErrors;
    bool enableAutoRecovery;
    int maxRetryAttempts;
    
    /**
     * @brief Constructor riêng tư (Singleton)
     */
    ErrorHandler() : enableAutoRecovery(true), maxRetryAttempts(3) {
        logger = ExceptionLogger::getInstance();
        setupDefaultHandlers();
    }

    /**
     * @brief Thiết lập các handler mặc định
     */
    void setupDefaultHandlers() {
        // Handler cho validation errors
        errorHandlers["ContactValidationException"] = [this](const exception& e) {
            logger->logException(e, "Contact Validation");
            logger->logWarning("Attempting to recover from validation error");
        };
        
        // Handler cho UI errors
        errorHandlers["UIException"] = [this](const exception& e) {
            logger->logException(e, "User Interface");
            logger->logInfo("UI error detected, continuing operation");
        };
        
        // Handler cho system errors
        errorHandlers["SystemException"] = [this](const exception& e) {
            logger->logException(e, "System Error");
            logger->logWarning("System error detected, attempting recovery");
        };
    }

public:
    static ErrorHandler* getInstance() {
        if (instance == nullptr) {
            instance = new ErrorHandler();
        }
        return instance;
    }
    
    /**
     * @brief Xử lý exception với strategy pattern
     * @param exception Exception cần xử lý
     * @param context Context của lỗi
     * @param retryFunction Function để retry (optional)
     */
    template<typename ExceptionType>
    bool handleException(const ExceptionType& exception, 
                        const string& context = "",
                        function<void()> retryFunction = nullptr) {
        
        // Log exception
        logger->logException(exception, context);
        
        // Kiểm tra xem có phải ignored error không
        string exceptionType = typeid(exception).name();
        if (isIgnoredError(exceptionType)) {
            logger->logInfo("Ignored error: " + exceptionType);
            return true; // Continue execution
        }
        
        // Tìm handler tương ứng
        auto handler = errorHandlers.find(exceptionType);
        if (handler != errorHandlers.end()) {
            handler->second(exception);
        }
        
        // Thực hiện auto recovery nếu được bật
        if (enableAutoRecovery && retryFunction) {
            return performAutoRecovery(retryFunction);
        }
        
        return false; // Không thể recover
    }
    
    /**
     * @brief Thực hiện auto recovery với retry logic
     * @param retryFunction Function để retry
     * @return true nếu recovery thành công
     */
    bool performAutoRecovery(function<void()> retryFunction) {
        logger->logInfo("Starting auto recovery process");
        
        for (int attempt = 1; attempt <= maxRetryAttempts; attempt++) {
            try {
                logger->logInfo("Recovery attempt " + to_string(attempt) + "/" + to_string(maxRetryAttempts));
                retryFunction();
                logger->logInfo("Recovery successful on attempt " + to_string(attempt));
                return true;
            } catch (const exception& e) {
                logger->logException(e, "Recovery Attempt " + to_string(attempt));
                
                if (attempt == maxRetryAttempts) {
                    logger->logWarning("Auto recovery failed after " + to_string(maxRetryAttempts) + " attempts");
                    return false;
                }
                
                // Wait before retry (simulated)
                this_thread::sleep_for(chrono::milliseconds(100 * attempt));
            }
        }
        
        return false;
    }
    
    /**
     * @brief Thêm custom error handler
     * @param exceptionType Tên loại exception
     * @param handler Function handler
     */
    void addErrorHandler(const string& exceptionType, function<void(const exception&)> handler) {
        errorHandlers[exceptionType] = handler;
        logger->logInfo("Added custom handler for: " + exceptionType);
    }
    
    /**
     * @brief Thêm error vào danh sách ignore
     * @param errorType Loại error cần ignore
     */
    void addIgnoredError(const string& errorType) {
        ignoredErrors.push_back(errorType);
        logger->logInfo("Added ignored error: " + errorType);
    }
    
    /**
     * @brief Kiểm tra xem error có bị ignore không
     * @param errorType Loại error
     * @return true nếu bị ignore
     */
    bool isIgnoredError(const string& errorType) const {
        return find(ignoredErrors.begin(), ignoredErrors.end(), errorType) != ignoredErrors.end();
    }
    
    /**
     * @brief Bật/tắt auto recovery
     * @param enable true để bật
     */
    void setAutoRecovery(bool enable) {
        enableAutoRecovery = enable;
        logger->logInfo("Auto recovery " + string(enable ? "enabled" : "disabled"));
    }
    
    /**
     * @brief Thiết lập số lần retry tối đa
     * @param attempts Số lần retry
     */
    void setMaxRetryAttempts(int attempts) {
        maxRetryAttempts = attempts;
        logger->logInfo("Max retry attempts set to: " + to_string(attempts));
    }
    
    /**
     * @brief Xử lý validation error với suggestions
     * @param field Tên field bị lỗi
     * @param value Giá trị không hợp lệ
     * @param suggestions Gợi ý sửa lỗi
     */
    void handleValidationError(const string& field, const string& value, const vector<string>& suggestions) {
        logger->logWarning("Validation error for field '" + field + "' with value '" + value + "'");
        
        cout << "\n\033[33m=== VALIDATION ERROR ===\033[0m" << endl;
        cout << "Field: " << field << endl;
        cout << "Invalid Value: " << value << endl;
        
        if (!suggestions.empty()) {
            cout << "Suggestions:" << endl;
            for (size_t i = 0; i < suggestions.size(); i++) {
                cout << "  " << (i + 1) << ". " << suggestions[i] << endl;
            }
        }
        
        cout << "\033[33m=======================\033[0m\n" << endl;
    }
    
    /**
     * @brief Xử lý system error với diagnostic info
     * @param error Exception
     * @param component Component bị lỗi
     */
    void handleSystemError(const exception& error, const string& component) {
        logger->logException(error, component);
        
        cout << "\n\033[31m=== SYSTEM ERROR ===\033[0m" << endl;
        cout << "Component: " << component << endl;
        cout << "Error: " << error.what() << endl;
        cout << "Time: " << logger->getCurrentTimestamp() << endl;
        cout << "\033[31m====================\033[0m\n" << endl;
    }
    
    /**
     * @brief Hiển thị error statistics
     */
    void showErrorStatistics() {
        cout << "\n=== ERROR STATISTICS ===" << endl;
        cout << "Total Errors: " << logger->getErrorCount() << endl;
        cout << "Auto Recovery: " << (enableAutoRecovery ? "Enabled" : "Disabled") << endl;
        cout << "Max Retry Attempts: " << maxRetryAttempts << endl;
        cout << "Custom Handlers: " << errorHandlers.size() << endl;
        cout << "Ignored Errors: " << ignoredErrors.size() << endl;
        cout << "========================\n" << endl;
    }
    
    /**
     * @brief Reset error handler state
     */
    void reset() {
        logger->clearErrorHistory();
        errorHandlers.clear();
        ignoredErrors.clear();
        setupDefaultHandlers();
        logger->logInfo("Error handler reset completed");
    }
};

// Khởi tạo static member
ErrorHandler* ErrorHandler::instance = nullptr;

#endif // ERROR_HANDLER_H
