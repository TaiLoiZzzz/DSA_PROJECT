#ifndef UI_LINUX_H
#define UI_LINUX_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

/**
 * @brief Lớp xử lý giao diện người dùng tương thích với Linux
 * Sử dụng ANSI escape codes để hiển thị màu sắc và xóa màn hình console
 */
class UI {
private:
    // ANSI escape codes cho màu sắc
    static const string RESET_COLOR;
    static const string RED_COLOR;
    static const string GREEN_COLOR;
    static const string YELLOW_COLOR;
    static const string BLUE_COLOR;
    static const string CLEAR_SCREEN;

public:
    /**
     * @brief Constructor
     */
    UI() {
        // Không cần khởi tạo gì đặc biệt trên Linux
    }

    /**
     * @brief Xóa màn hình console
     */
    void clearScreen() {
        cout << CLEAR_SCREEN << flush;
    }

    /**
     * @brief Thiết lập màu chữ cho console
     * @param color Màu sắc cần thiết lập
     */
    void setTextColor(int color) {
        // Trên Linux, chúng ta sử dụng ANSI escape codes
        // Hàm này được giữ lại để tương thích với code cũ
        switch(color) {
            case 1: // Đỏ
                cout << RED_COLOR;
                break;
            case 2: // Xanh lá
                cout << GREEN_COLOR;
                break;
            case 3: // Vàng
                cout << YELLOW_COLOR;
                break;
            case 4: // Xanh dương
                cout << BLUE_COLOR;
                break;
            default:
                cout << RESET_COLOR;
                break;
        }
    }

    /**
     * @brief Thiết lập màu mặc định (trắng)
     */
    void resetColor() {
        cout << RESET_COLOR;
    }

    /**
     * @brief Hiển thị thông báo lỗi với màu đỏ
     * @param message Thông báo cần hiển thị
     */
    void showError(const string& message) {
        cout << RED_COLOR << "[LỖI] " << message << RESET_COLOR << endl;
    }

    /**
     * @brief Hiển thị thông báo thành công với màu xanh lá
     * @param message Thông báo cần hiển thị
     */
    void showSuccess(const string& message) {
        cout << GREEN_COLOR << "[THÀNH CÔNG] " << message << RESET_COLOR << endl;
    }

    /**
     * @brief Hiển thị thông báo thông tin với màu vàng
     * @param message Thông báo cần hiển thị
     */
    void showInfo(const string& message) {
        cout << YELLOW_COLOR << "[THÔNG TIN] " << message << RESET_COLOR << endl;
    }

    /**
     * @brief Hiển thị liên hệ với màu vàng
     * @param message Thông tin liên hệ
     */
    void showContact(const string& message) {
        cout << YELLOW_COLOR << message << RESET_COLOR << endl;
    }

    /**
     * @brief Hiển thị menu với màu xanh dương
     * @param message Nội dung menu
     */
    void showMenu(const string& message) {
        cout << BLUE_COLOR << message << RESET_COLOR << endl;
    }

    /**
     * @brief Hiển thị header của ứng dụng
     */
    void showHeader() {
        clearScreen();
        cout << BLUE_COLOR;
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    DANH BẠ ĐIỆN THOẠI                     ║" << endl;
        cout << "║                     PHIÊN BẢN LINUX                       ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        cout << RESET_COLOR << endl;
    }

    /**
     * @brief Hiển thị thông báo chào mừng
     */
    void showWelcome() {
        cout << GREEN_COLOR << "Chào mừng bạn đến với ứng dụng Danh Bạ Điện Thoại!" << RESET_COLOR << endl;
        cout << "Phiên bản tương thích với Linux" << endl << endl;
    }

    /**
     * @brief Hiển thị thông báo tạm biệt
     */
    void showGoodbye() {
        cout << YELLOW_COLOR << "Cảm ơn bạn đã sử dụng ứng dụng!" << RESET_COLOR << endl;
        cout << "Hẹn gặp lại!" << endl;
    }

    /**
     * @brief Hiển thị thông báo chờ nhập
     */
    void showPrompt(const string& message) {
        cout << BLUE_COLOR << message << RESET_COLOR;
    }

    /**
     * @brief Hiển thị thông báo chờ Enter
     */
    void waitForEnter() {
        cout << YELLOW_COLOR << "Nhấn Enter để tiếp tục..." << RESET_COLOR;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    /**
     * @brief Hiển thị dòng phân cách
     */
    void showSeparator() {
        cout << "────────────────────────────────────────────────────────────────" << endl;
    }

    /**
     * @brief Hiển thị thông báo danh bạ trống
     */
    void showEmptyMessage() {
        cout << YELLOW_COLOR << "[THÔNG BÁO] Danh bạ hiện tại không có liên hệ nào!" << RESET_COLOR << endl;
    }

    /**
     * @brief Hiển thị menu chính
     */
    void showMainMenu() {
        clearScreen();
        showHeader();
        showWelcome();
        cout << BLUE_COLOR;
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                        MENU CHÍNH                          ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║  1. Thêm liên hệ mới                                       ║" << endl;
        cout << "║  2. Xóa liên hệ                                            ║" << endl;
        cout << "║  3. Tìm kiếm liên hệ                                       ║" << endl;
        cout << "║  4. Hiển thị tất cả liên hệ                                ║" << endl;
        cout << "║  5. Thoát                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        cout << RESET_COLOR;
        cout << YELLOW_COLOR << "Nhập lựa chọn của bạn (1-5): " << RESET_COLOR;
    }
};

// Định nghĩa các hằng số ANSI escape codes
const string UI::RESET_COLOR = "\033[0m";
const string UI::RED_COLOR = "\033[31m";
const string UI::GREEN_COLOR = "\033[32m";
const string UI::YELLOW_COLOR = "\033[33m";
const string UI::BLUE_COLOR = "\033[34m";
const string UI::CLEAR_SCREEN = "\033[2J\033[H";

#endif // UI_LINUX_H
