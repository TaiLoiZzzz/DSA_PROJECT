#ifndef ADVANCED_VALIDATOR_H
#define ADVANCED_VALIDATOR_H

#include "Exceptions.h"
#include <regex>
#include <vector>
#include <map>
#include <functional>

using namespace std;

/**
 * @brief Lớp validation nâng cao với multiple rules và intelligent suggestions
 */
class AdvancedValidator {
private:
    static AdvancedValidator* instance;
    map<string, vector<function<bool(const string&)>>> validationRules;
    map<string, vector<string>> fieldSuggestions;
    
    /**
     * @brief Constructor riêng tư (Singleton)
     */
    AdvancedValidator() {
        setupValidationRules();
        setupSuggestions();
    }
    
    /**
     * @brief Thiết lập các rule validation mặc định
     */
    void setupValidationRules() {
        // Rules cho tên
        validationRules["name"] = {
            [](const string& name) { return !name.empty(); },
            [](const string& name) { return name.length() <= 50; },
            [](const string& name) { 
                return regex_match(name, regex("^[a-zA-Z0-9\\s\\u00C0-\\u017F]+$")); 
            },
            [](const string& name) {
                // Kiểm tra không có khoảng trắng liên tiếp
                return !regex_search(name, regex("\\s{2,}"));
            }
        };
        
        // Rules cho số điện thoại
        validationRules["phone"] = {
            [](const string& phone) { return !phone.empty(); },
            [](const string& phone) { 
                return phone.length() >= 10 && phone.length() <= 15; 
            },
            [](const string& phone) { 
                return regex_match(phone, regex("^[0-9]+$")); 
            },
            [](const string& phone) {
                // Kiểm tra format số điện thoại Việt Nam
                return regex_match(phone, regex("^(0|84|\\+84)[0-9]{9,10}$"));
            }
        };
        
        // Rules cho email
        validationRules["email"] = {
            [](const string& email) { 
                if (email.empty()) return true; // Email có thể rỗng
                return regex_match(email, regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$")); 
            },
            [](const string& email) { 
                if (email.empty()) return true;
                return email.length() <= 100; 
            },
            [](const string& email) {
                if (email.empty()) return true;
                // Kiểm tra domain hợp lệ
                size_t atPos = email.find('@');
                if (atPos == string::npos) return false;
                string domain = email.substr(atPos + 1);
                return domain.find('.') != string::npos && domain.find('.') < domain.length() - 1;
            }
        };
    }
    
    /**
     * @brief Thiết lập suggestions cho từng field
     */
    void setupSuggestions() {
        fieldSuggestions["name"] = {
            "Tên không được để trống",
            "Tên chỉ chứa chữ cái, số và khoảng trắng",
            "Tên không được quá 50 ký tự",
            "Không sử dụng ký tự đặc biệt",
            "Không có khoảng trắng liên tiếp"
        };
        
        fieldSuggestions["phone"] = {
            "Số điện thoại không được để trống",
            "Số điện thoại phải có 10-15 chữ số",
            "Số điện thoại phải bắt đầu bằng 0, 84 hoặc +84",
            "Không chứa ký tự đặc biệt hoặc chữ cái",
            "Ví dụ: 0123456789, 84987654321, +84123456789"
        };
        
        fieldSuggestions["email"] = {
            "Email phải có định dạng: user@domain.com",
            "Email không được quá 100 ký tự",
            "Domain phải hợp lệ (có dấu chấm)",
            "Email có thể để trống nếu không cần thiết",
            "Ví dụ: user@example.com, test.email@gmail.com"
        };
    }

public:
    static AdvancedValidator* getInstance() {
        if (instance == nullptr) {
            instance = new AdvancedValidator();
        }
        return instance;
    }
    
    /**
     * @brief Validate một field với tất cả rules
     * @param field Tên field
     * @param value Giá trị cần validate
     * @return Pair với kết quả validation và suggestions
     */
    pair<bool, vector<string>> validateField(const string& field, const string& value) {
        auto rules = validationRules.find(field);
        if (rules == validationRules.end()) {
            return {false, {"Unknown field: " + field}};
        }
        
        vector<string> failedSuggestions;
        
        for (size_t i = 0; i < rules->second.size(); i++) {
            if (!rules->second[i](value)) {
                auto suggestions = fieldSuggestions.find(field);
                if (suggestions != fieldSuggestions.end() && i < suggestions->second.size()) {
                    failedSuggestions.push_back(suggestions->second[i]);
                }
            }
        }
        
        return {failedSuggestions.empty(), failedSuggestions};
    }
    
    /**
     * @brief Validate và tạo suggestions thông minh
     * @param field Tên field
     * @param value Giá trị cần validate
     * @return Vector suggestions thông minh
     */
    vector<string> getIntelligentSuggestions(const string& field, const string& value) {
        vector<string> suggestions;
        
        if (field == "name") {
            if (value.empty()) {
                suggestions.push_back("Hãy nhập tên liên hệ");
                suggestions.push_back("Ví dụ: Nguyen Van A");
            } else if (value.length() > 50) {
                suggestions.push_back("Tên quá dài, hãy rút gọn");
                suggestions.push_back("Sử dụng tên gọi thay vì họ đầy đủ");
            } else if (regex_search(value, regex("[^a-zA-Z0-9\\s\\u00C0-\\u017F]"))) {
                suggestions.push_back("Loại bỏ ký tự đặc biệt như @, #, $, ...");
                suggestions.push_back("Sử dụng dấu tiếng Việt có dấu thay vì ký tự đặc biệt");
            }
        } else if (field == "phone") {
            if (value.empty()) {
                suggestions.push_back("Hãy nhập số điện thoại");
                suggestions.push_back("Ví dụ: 0123456789");
            } else if (value.length() < 10) {
                suggestions.push_back("Số điện thoại quá ngắn");
                suggestions.push_back("Số điện thoại Việt Nam phải có ít nhất 10 chữ số");
            } else if (value.length() > 15) {
                suggestions.push_back("Số điện thoại quá dài");
                suggestions.push_back("Kiểm tra lại số điện thoại");
            } else if (regex_search(value, regex("[^0-9]"))) {
                suggestions.push_back("Loại bỏ ký tự không phải số");
                suggestions.push_back("Chỉ sử dụng các chữ số từ 0-9");
            } else if (!regex_match(value, regex("^(0|84|\\+84)"))) {
                suggestions.push_back("Số điện thoại phải bắt đầu bằng 0, 84 hoặc +84");
                suggestions.push_back("Ví dụ: 0123456789, 84987654321, +84123456789");
            }
        } else if (field == "email") {
            if (!value.empty()) {
                if (!regex_search(value, regex("@.*\\."))) {
                    suggestions.push_back("Email phải có @ và domain với dấu chấm");
                    suggestions.push_back("Ví dụ: user@example.com");
                } else if (value.length() > 100) {
                    suggestions.push_back("Email quá dài");
                    suggestions.push_back("Sử dụng email ngắn gọn hơn");
                }
            }
        }
        
        return suggestions;
    }
    
    /**
     * @brief Validate contact với detailed feedback
     * @param contact Contact cần validate
     * @return Map với kết quả validation cho từng field
     */
    map<string, pair<bool, vector<string>>> validateContact(const Contact& contact) {
        map<string, pair<bool, vector<string>>> results;
        
        results["name"] = validateField("name", contact.name);
        results["phone"] = validateField("phone", contact.phoneNumber);
        results["email"] = validateField("email", contact.email);
        
        return results;
    }
    
    /**
     * @brief Tạo comprehensive validation report
     * @param contact Contact cần validate
     * @return String report chi tiết
     */
    string generateValidationReport(const Contact& contact) {
        auto results = validateContact(contact);
        stringstream report;
        
        report << "\n=== VALIDATION REPORT ===" << endl;
        
        for (const auto& result : results) {
            report << "Field: " << result.first << endl;
            report << "Value: " << (result.first == "name" ? contact.name : 
                                  result.first == "phone" ? contact.phoneNumber : 
                                  contact.email) << endl;
            report << "Status: " << (result.second.first ? "✓ VALID" : "✗ INVALID") << endl;
            
            if (!result.second.first) {
                report << "Issues:" << endl;
                for (const string& issue : result.second.second) {
                    report << "  - " << issue << endl;
                }
                
                auto intelligentSuggestions = getIntelligentSuggestions(result.first, 
                    result.first == "name" ? contact.name : 
                    result.first == "phone" ? contact.phoneNumber : contact.email);
                
                if (!intelligentSuggestions.empty()) {
                    report << "Suggestions:" << endl;
                    for (const string& suggestion : intelligentSuggestions) {
                        report << "  • " << suggestion << endl;
                    }
                }
            }
            report << endl;
        }
        
        report << "========================\n" << endl;
        return report.str();
    }
    
    /**
     * @brief Thêm custom validation rule
     * @param field Tên field
     * @param rule Function validation rule
     * @param suggestion Suggestion khi rule fail
     */
    void addCustomRule(const string& field, function<bool(const string&)> rule, const string& suggestion) {
        validationRules[field].push_back(rule);
        fieldSuggestions[field].push_back(suggestion);
    }
    
    /**
     * @brief Reset về rules mặc định
     */
    void resetToDefaults() {
        validationRules.clear();
        fieldSuggestions.clear();
        setupValidationRules();
        setupSuggestions();
    }
};

// Khởi tạo static member
AdvancedValidator* AdvancedValidator::instance = nullptr;

#endif // ADVANCED_VALIDATOR_H
