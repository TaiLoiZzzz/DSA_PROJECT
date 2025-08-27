CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = smart_contact_cli
SOURCES = main.cpp Contact.cpp ContactManager.cpp ContactUI.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

# Windows specific
ifeq ($(OS),Windows_NT)
clean:
	del /Q *.o $(TARGET).exe 2>nul || exit 0
run: $(TARGET)
	./$(TARGET).exe
endif
