
FT_VERSION ?= 2.9
HB_VERSION ?= 1.7.6

FT = freetype-$(FT_VERSION)
HB = harfbuzz-$(HB_VERSION)


.PHONY: all
all: $(FT)-vanilla.tar.gz $(HB)-vanilla.tar.gz $(HB)-patched.tar.gz


$(FT)-vanilla.tar.gz:
	./download.sh "https://download.savannah.gnu.org/releases/freetype/$(FT).tar.gz" $(FT)-vanilla.tar.gz


$(HB)-vanilla.tar.gz: $(HB)
	tar -zcf $(HB)-vanilla.tar.gz $(HB)

$(HB)-patched.tar.gz: $(HB)
	(cd $(HB) && patch < ../diffs/harfbuzz-pkgconfig.diff) && \
	tar -zcf $(HB)-patched.tar.gz $(HB)

$(HB):
	./download.sh "https://github.com/harfbuzz/harfbuzz/releases/download/1.7.6/"$(HB).tar.bz2 $(HB).tar.bz2 && \
	tar -xf $(HB).tar.bz2


.PHONY: clean
clean:
	rm -rf $(FT) $(HB) $(HB).tar.bz2

.PHONY: distclean
distclean: clean
	rm -rf $(HB).tar.gz


# Use this to print an envvar:
# make print-ENVVAR
print-%: ; @echo $* = $($*)
