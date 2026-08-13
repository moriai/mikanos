APPDIRS = $(subst /Makefile,,$(wildcard apps/*/Makefile))
SUBDIRS = kernel apps $(APPDIRS)
KERNEL = kernel/kernel.elf
LIBRARY = apps/library
APPS = $(join $(APPDIRS),$(subst apps,,$(APPDIRS)))
TARGETS = $(KERNEL) $(LIBRARY) $(APPS)

.PHONY: all clean distclean image run $(SUBDIRS)

all: $(TARGETS)

$(KERNEL): FORCE
	@$(MAKE) --no-print-directory -C $(dir $@) all

$(LIBRARY): FORCE
	@$(MAKE) --no-print-directory -C $(dir $@) all

$(APPS): $(KERNEL) $(LIBRARY)
	@$(MAKE) --no-print-directory -C $(dir $@) all

FORCE: ;

disk.img: $(TARGETS)
	APPS_DIR=./apps RESOURCE_DIR=./resource DISK_IMG=./disk.img MIKANOS_DIR=$$PWD \
	$$HOME/osbook/devenv/make_mikanos_image.sh

image: disk.img

run: disk.img
	$$HOME/osbook/devenv/run_image.sh ./disk.img

clean: ACTION = clean

distclean: ACTION = distclean

clean distclean: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@ $(ACTION)

distclean:
	rm -fr disk.img mnt
