
HB_VERSION ?= 1.7.6

HB = harfbuzz-$(HB_VERSION)
HB_ARCHIVE = downloads/$(HB).tar.bz2


.PHONY: all
all: harfbuzz-patched


.PHONY: harfbuzz-patched
harfbuzz-patched: $(HB_ARCHIVE)
	bunzip2 < $(HB_ARCHIVE) | tar xf -
	cd $(HB) && \
	patch < ../harfbuzz-pkgconfig.diff && \
	cd .. && \
	tar cf - $(HB) | gzip -9 > $(HB).tar.gz
	$(MAKE) clean

$(HB_ARCHIVE):
	mkdir -p downloads && \
	cd downloads && \
	../download.sh "https://github.com/harfbuzz/harfbuzz/releases/download/1.7.6/"$(HB).tar.bz2 $(HB).tar.bz2


.PHONY: clean
clean:
	rm -rf downloads $(HB)

.PHONY: distclean
distclean: clean
	rm -rf $(HB).tar.gz


# Use this to print an envvar:
# make print-ENVVAR
print-%: ; @echo $* = $($*)
