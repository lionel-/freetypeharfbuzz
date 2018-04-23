
HB_VERSION ?= 1.7.6

HB = harfbuzz-$(HB_VERSION)


.PHONY: all
all: harfbuzz-patched


.PHONY: harfbuzz-patched
harfbuzz-patched: $(HB).tar.bz2
	tar xf $(HB).tar.bz2 && \
	cd $(HB) && \
  patch < ../harfbuzz-pkgconfig.diff && \
	cd .. && \
	tar cvzf $(HB).tar.gz $(HB) && \
  cp -rf $(HB).tar.gz ../src && \
	$(MAKE) clean

.PHONY: harfbuzz-vanilla
harfbuzz-vanilla: $(HB).tar.bz2
	tar xf $(HB).tar.bz2 && \
	tar cvzf $(HB).tar.gz $(HB) && \
  cp -rf $(HB).tar.gz ../src && \
	$(MAKE) clean

$(HB).tar.bz2:
	wget "https://github.com/harfbuzz/harfbuzz/releases/download/1.7.6/harfbuzz-1.7.6.tar.bz2"


.PHONY: clean
clean:
	rm -rf $(HB) $(HB).tar.gz


# Use this to print an envvar:
# make print-ENVVAR
print-%: ; @echo $* = $($*)
