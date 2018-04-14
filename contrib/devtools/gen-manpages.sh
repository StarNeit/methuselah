#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

METHUSELAHD=${METHUSELAHD:-$SRCDIR/methuselahd}
METHUSELAHCLI=${METHUSELAHCLI:-$SRCDIR/methuselah-cli}
METHUSELAHTX=${METHUSELAHTX:-$SRCDIR/methuselah-tx}
METHUSELAHQT=${METHUSELAHQT:-$SRCDIR/qt/methuselah-qt}

[ ! -x $METHUSELAHD ] && echo "$METHUSELAHD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
SAPVER=($($METHUSELAHCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for methuselahd if --version-string is not set,
# but has different outcomes for methuselah-qt and methuselah-cli.
echo "[COPYRIGHT]" > footer.h2m
$METHUSELAHD --version | sed -n '1!p' >> footer.h2m

for cmd in $METHUSELAHD $METHUSELAHCLI $METHUSELAHTX $METHUSELAHQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SAPVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SAPVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
