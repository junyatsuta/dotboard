include ../config.mk

SRCS = main.cpp
OBJS := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
DEPS := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.d))
TARGET := $(BIN_DIR)/app

CPPFLAGS += -I$(TOP_DIR)/lib/output/shell
CPPFLAGS += -I$(TOP_DIR)/lib/core
CPPFLAGS += -I$(TOP_DIR)/lib/input/text

LIB_OBJS := \
	$(wildcard $(OBJ_ROOT)/lib/core/*.o) \
	$(wildcard $(OBJ_ROOT)/lib/output/shell/*.o) \
	$(wildcard $(OBJ_ROOT)/lib/input/text/*.o)

.PHONY: all clean

# ターゲットとレシピ
all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_OBJS)
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIB_OBJS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)