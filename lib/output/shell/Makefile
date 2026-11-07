include ../../../config.mk

SRCS   := output_shell.cpp
OBJS   := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
DEPS   := $(OBJS:.o=.d)
TARGET := $(LIB_DIR)/libdotboard_output_shell.a

CPPFLAGS += -I$(TOP_DIR)/lib/core

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)