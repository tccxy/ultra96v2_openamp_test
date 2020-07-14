#
# This file is the amptest recipe.
#

SUMMARY = "Simple amptest application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "\
	file://LICENSE \
	file://Makefile \
	file://amp_test.c \
	file://rpmsg_delay_test.c \
	"

S = "${WORKDIR}"

RDEPENDS_${PN} = "kernel-module-rpmsg-user"

FILES_${PN} = "\
	/usr/bin/amptest\
	/usr/bin/rpmsgdelaytest\
"

do_install () {
	install -d ${D}/usr/bin
	install -m 0755 amptest ${D}/usr/bin/amptest
	install -m 0755 rpmsgdelaytest ${D}/usr/bin/rpmsgdelaytest
}
