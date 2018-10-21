AC_INIT
AC_CONFIG_FILES([Makefile])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi
CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`


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
