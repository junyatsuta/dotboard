include ../../config.mk

SRCS   := bdfParser.cpp
OBJS   := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
DEPS   := $(OBJS:.o=.d)
TARGET := $(TOOL_BIN_DIR)/bdfParser

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)