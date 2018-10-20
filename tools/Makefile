
FTHB_VERSION = 0.2.4

FT_VERSION ?= 2.9
HB_VERSION ?= 1.7.6

FT = freetype-$(FT_VERSION)
HB = harfbuzz-$(HB_VERSION)


.PHONY: all
all: $(FT)-patched.tar.gz $(HB)-patched.tar.gz


$(FT)-vanilla.tar.gz:
	./download.sh "https://github.com/lionel-/freetypeharfbuzz/raw/v$(FTHB_VERSION)/tools/$(FT)-vanilla.tar.gz" $(FT)-vanilla.tar.gz

$(FT)-patched.tar.gz:
	./download.sh "https://github.com/lionel-/freetypeharfbuzz/raw/v$(FTHB_VERSION)/tools/$(FT)-patched.tar.gz" $(FT)-patched.tar.gz

$(HB)-vanilla.tar.gz:
	./download.sh "https://github.com/lionel-/freetypeharfbuzz/raw/v$(FTHB_VERSION)/tools/$(HB)-vanilla.tar.gz" $(HB)-vanilla.tar.gz

$(HB)-patched.tar.gz:
	./download.sh "https://github.com/lionel-/freetypeharfbuzz/raw/v$(FTHB_VERSION)/tools/$(HB)-patched.tar.gz" $(HB)-patched.tar.gz


.PHONY: tarballs
tarballs: tarballs-freetype tarballs-harfbuzz

.PHONY: tarballs-freetype
tarballs-freetype:
	./download.sh "https://download.savannah.gnu.org/releases/freetype/$(FT).tar.gz" $(FT)-vanilla.tar.gz && \
	tar -xf $(FT)-vanilla.tar.gz $(FT) && \
	(cd $(FT) && \
		patch -p1 < ../diffs/freetype/0001-Remove-pragma-diagnostics.patch && \
		patch -p1 < ../diffs/freetype/0002-Remove-amiga-files.patch \
	) && \
	tar -zcf $(FT)-patched.tar.gz $(FT) && \
	$(MAKE) clean

.PHONY: tarballs-harfbuzz
tarballs-harfbuzz:
	./download.sh "https://github.com/harfbuzz/harfbuzz/releases/download/1.7.6/"$(HB).tar.bz2 $(HB).tar.bz2 && \
	tar -xf $(HB).tar.bz2 && \
	tar -zcf $(HB)-vanilla.tar.gz $(HB) && \
	(cd $(HB) && \
		patch < ../diffs/harfbuzz-flag.diff && \
		patch < ../diffs/harfbuzz-pkgconfig.diff && \
		patch -p1 < ../diffs/0001-Undefine-HB_PRINTF_FUNC.patch && \
		patch -p1 < ../diffs/0002-Remove-unnecessary-trailing-semi-colon.patch && \
		patch -p1 < ../diffs/0003-Initialise-offsets.patch && \
		patch -p1 < ../diffs/0004-Cast-to-void-before-memset.patch && \
		patch -p1 < ../diffs/0005-Silence-gcc-warning.patch \
	) && \
	tar -zcf $(HB)-patched.tar.gz $(HB) && \
	$(MAKE) clean


.PHONY: clean
clean:
	rm -rf $(FT) $(HB) $(HB).tar.bz2

.PHONY: distclean
distclean: clean
	rm -rf \
		$(FT)-vanilla.tar.gz \
		$(FT)-patched.tar.gz \
		$(HB)-vanilla.tar.gz \
		$(HB)-patched.tar.gz


# Use this to print an envvar:
# make print-ENVVAR
print-%: ; @echo $* = $($*)
