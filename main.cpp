#include "ContactUI.h"
#include "ContactException.h"
#include <iostream>

using namespace std;

int main() {
    try {
        ContactUI app;
        app.run();
    } catch (const ContactException& e) {
        cout << "❌ Lỗi hệ thống: " << e.what() << endl;
        cout << "Vui lòng thử lại hoặc liên hệ hỗ trợ." << endl;
        return 1;
    } catch (const exception& e) {
        cout << "❌ Lỗi không xác định: " << e.what() << endl;
        cout << "Vui lòng khởi động lại ứng dụng." << endl;
        return 1;
    } catch (...) {
        cout << "❌ Lỗi nghiêm trọng không xác định!" << endl;
        cout << "Vui lòng khởi động lại ứng dụng hoặc liên hệ hỗ trợ." << endl;
        return 1;
    }
    
    return 0;
}
