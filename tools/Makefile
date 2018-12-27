
FTHB_VERSION = `cat version`

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
	./download.sh "https://github.com/lionel-/harfbuzz/archive/$(HB_VERSION)-CRAN.tar.gz" $(HB)-patched.tar.gz


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
	test -e $(HB).tar.bz2 || wget "https://github.com/harfbuzz/harfbuzz/releases/download/1.7.6/"$(HB).tar.bz2 && \
	rm -rf $(HB) && \
	tar -xf $(HB).tar.bz2 $(HB) && \
	(cd $(HB) && \
		patch -p1 < ../diffs/harfbuzz/0001-Undefine-HB_PRINTF_FUNC.patch && \
		patch -p1 < ../diffs/harfbuzz/0002-Remove-unnecessary-trailing-semi-colon.patch && \
		patch -p1 < ../diffs/harfbuzz/0003-Initialise-offsets.patch && \
		patch -p1 < ../diffs/harfbuzz/0004-Cast-to-void-before-memset.patch && \
		patch -p1 < ../diffs/harfbuzz/0005-Silence-gcc-warning.patch && \
		patch -p1 < ../diffs/harfbuzz/0006-Remove-flags-causing-warnings-on-Solaris.patch && \
		patch -p1 < ../diffs/harfbuzz/0007-Silence-Solaris-warnings-about-symbol-hiding.patch && \
		patch -p1 < ../diffs/harfbuzz/0008-Reenable-CXX11.patch && \
		cp ../m4/ax_cxx_compile_stdcxx.m4 ./m4 && \
		NOCONFIGURE=true ./autogen.sh && \
		patch < ../diffs/harfbuzz/harfbuzz-flag.diff && \
		patch < ../diffs/harfbuzz/harfbuzz-pkgconfig.diff \
	) && \
	tar -zcf $(HB)-patched.tar.gz $(HB)


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
