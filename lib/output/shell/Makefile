include ../../../config.mk

SRCS   := output_shell.cpp
OBJS   := $(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))
DEPS   := $(OBJS:.o=.d)

CPPFLAGS += -I$(TOP_DIR)/lib/core

.PHONY: all clean

all: $(OBJS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)