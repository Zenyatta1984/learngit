INC_DIR :=  ./
SRC_DIR = ./
CC := g++
CPPFLAGS := -std=c++11 -g
LIBS := -lpthread
INC_FILE := $(addprefix -I, $(INC_DIR))
CPP_FILE :=  $(wildcard ./*.cc)
#OBJS_HPP :=$(wildcard  $(INC_DIR)/*.hpp) $(wildcard $(INC_DIR)/*.h)
OBJS:= $(patsubst %.cc, %.o, $(CPP_FILE))
TARGET := testThreadpool.exe
$(TARGET):$(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(INC_FILE) $(LIBS)

clean:
	rm -rf $(TARGET) $(OBJS)
