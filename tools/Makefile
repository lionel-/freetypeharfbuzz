
HB_VERSION ?= 1.7.6

HB = harfbuzz-$(HB_VERSION)


.PHONY: all
all: $(HB)-vanilla.zip $(HB)-patched.zip


$(HB)-vanilla.zip: $(HB)
	zip -r $(HB)-vanilla.zip $(HB)

$(HB)-patched.zip: $(HB)
	(cd $(HB) && patch < ../diffs/harfbuzz-pkgconfig.diff) && \
	zip -r $(HB)-patched.zip $(HB)

$(HB):
	./download.sh "https://github.com/harfbuzz/harfbuzz/releases/download/1.7.6/"$(HB).tar.bz2 $(HB).tar.bz2 && \
	tar xf $(HB).tar.bz2


.PHONY: clean
clean:
	rm -rf $(HB).tar.bz2 $(HB)

.PHONY: distclean
distclean: clean
	rm -rf $(HB).zip


# Use this to print an envvar:
# make print-ENVVAR
print-%: ; @echo $* = $($*)
