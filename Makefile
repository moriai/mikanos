TARGETS = kernel $(dir $(wildcard apps/*/Makefile))

.PHONY: all clean distclean run $(TARGETS)

all: ACTION = all

clean: ACTION = clean

distclean: ACTION = distclean

all clean distclean: $(TARGETS)

$(TARGETS):
	$(MAKE) -C $@ $(ACTION)

run: all
	-@MIKANOS_DIR=$$PWD $$HOME/osbook/devenv/run_mikanos.sh

distclean:
	rm -fr disk.img mnt
