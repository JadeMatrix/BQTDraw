#!/bin/bash

PROGNAME=BQTDraw
ICONNAME=JadeMatrix-${PROGNAME}_icon

PROGDIR=`pwd`

TEMP_DIR=`mktemp -d`

DESKTOP_FILE="${TEMP_DIR}/JadeMatrix-${PROGNAME}.desktop"

cat << EOF > ${DESKTOP_FILE}
[Desktop Entry]
Version=1.0
Name=${PROGNAME}
GenericName=Bitmap Editor
Comment=Art program geared towards speed and illustration for print.
Exec="${PROGDIR}/Linux/${PROGNAME}" -l~/.BQTDraw_log.txt -d
Icon=${ICONNAME}
Terminal=false
Type=Application
Categories=Graphics;
EOF

xdg-desktop-menu install ${DESKTOP_FILE}
xdg-icon-resource install --size 16 "${PROGDIR}/resources/${PROGNAME}_app_16p.png" ${ICONNAME}
xdg-icon-resource install --size 32 "${PROGDIR}/resources/${PROGNAME}_app_32p.png" ${ICONNAME}
xdg-icon-resource install --size 128 "${PROGDIR}/resources/${PROGNAME}_app_128p.png" ${ICONNAME}
xdg-icon-resource install --size 256 "${PROGDIR}/resources/${PROGNAME}_app_256p.png" ${ICONNAME}
xdg-icon-resource install --size 512 "${PROGDIR}/resources/${PROGNAME}_app_512p.png" ${ICONNAME}

# TODO: icon sizes 22, 48 & 64

rm ${DESKTOP_FILE}
rm -R ${TEMP_DIR}