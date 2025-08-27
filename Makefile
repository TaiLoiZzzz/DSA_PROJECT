# Main Makefile - Sử dụng để build từ thư mục gốc
.PHONY: all clean run build

all: build

build:
	@echo "🔨 Building project with new directory structure..."
	@cd build && make

clean:
	@echo "🧹 Cleaning build files..."
	@cd build && make clean
	@rm -rf build/*.o build/smart_contact_cli*

run: build
	@echo "🚀 Running application..."
	@cd build && make run

# Tạo thư mục build nếu chưa có
setup:
	@echo "📁 Setting up build directory..."
	@mkdir -p build
	@echo "✅ Build directory ready!"

# Install dependencies (nếu cần)
install:
	@echo "📦 No external dependencies required for this project"

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  build   - Build the project"
	@echo "  clean   - Clean build files"
	@echo "  run     - Build and run the application"
	@echo "  setup   - Setup build directory"
	@echo "  install - Install dependencies"
	@echo "  help    - Show this help message"
