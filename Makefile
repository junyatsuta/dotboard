include config.mk

.PHONY: all tools lib app clean compdb

all: tools lib app
	$(MAKE) -C tools
	$(MAKE) -C lib
	$(MAKE) -C app

clean:
	rm -rf $(BUILD_DIR)

compdb:
	$(MAKE) clean
	@mkdir -p $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- $(MAKE) all