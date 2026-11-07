include config.mk

.PHONY: all tools lib app clean compdb test

all: tools lib app
	$(MAKE) -C tools
	$(MAKE) -C lib
	$(MAKE) -C app

test: tools lib tests
	$(MAKE) -C tools
	$(MAKE) -C lib
	$(MAKE) -C tests test

clean:
	rm -rf $(BUILD_DIR)

compdb:
	$(MAKE) clean
	@mkdir -p $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- $(MAKE) all