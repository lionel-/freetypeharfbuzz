AC_INIT
AC_CONFIG_FILES([Makefile])

AC_PROG_CC_C99

cat > conftest.c << EOF
int main() { return 0; }
EOF

if $CC $CFLAGS -xc99 -o conftest.o conftest.c > /dev/null 2>&1; then
  echo "Selecting -xc99 flag"
  C99_FLAG="-xc99"
elif $CC $CFLAGS -std=c99 -o conftest.o conftest.c > /dev/null 2>&1; then
  echo "Selecting -std=c99 flag"
  C99_FLAG="-std=c99"
else
  echo "Can't detect valid C99 flag"
fi

AC_SUBST(C99_FLAG)
rm conftest.c


AC_OUTPUT
