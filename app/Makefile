include ../config.mk

SRCS = main.cpp
OBJS := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
DEPS := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.d))
TARGET := $(BIN_DIR)/app

CPPFLAGS += -I$(TOP_DIR)/lib/output/shell
CPPFLAGS += -I$(TOP_DIR)/lib/core
CPPFLAGS += -I$(TOP_DIR)/lib/input/text

LIBS := $(LIB_DIR)/libdotboard_output_shell.a $(LIB_DIR)/libdotboard_input_text.a $(LIB_DIR)/libdotboard_core.a

.PHONY: all clean

# ターゲットとレシピ
all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS) $(LIBS)