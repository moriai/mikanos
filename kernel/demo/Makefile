TARGET = memory_manager_demo
OBJS = main.o memory_manager.o observe.o

CXX = clang++
CPPFLAGS = -I. -I..
CXXFLAGS += -O2 -Wall -Wextra -g -std=c++17

vpath %.hpp ..

.PHONY: all clean run
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -fuse-ld=lld -o $@ $(OBJS)

$(OBJS): memory_manager.hpp error.hpp observe.hpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
