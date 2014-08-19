################################################################################
# 
# Variables to configure:
# 
# CC 		C compiler with std flags (CC++ is C++ compiler)
# FFBUILD	Platform-specific, for example gcc40.mac.x64 for OS X
# 
################################################################################

# Making FastFormat assumes you have FASTFORMAT_ROOT and STLSOFT set as speci-
# fied in the FastFormat INSTALL.txt
ifndef STLSOFT
$(error STLSOFT must be defined)
endif
ifndef FASTFORMAT_ROOT
$(error FASTFORMAT_ROOT must be defined)
endif

# Compiler(s)
# CC = /usr/local/Cellar/llvm/3.4/bin/clang
CC = clang
CPPC = ${CC}++ -stdlib=libstdc++
OBJCC = ${CC}

# Directories
SOURCEDIR = src
RESOURCEDIR = resources
MAKEDIR = make
OBJDIR = ${MAKEDIR}/object
BUILDDIR = ${MAKEDIR}/build

# Fast format build version folder
# TODO: set using Autotools
# FFBUILD = gcc40.mac.x64
FFBUILD = gcc47.unix
FFOBJDIR = ${FASTFORMAT_ROOT}/build/${FFBUILD}

# Headers & librarires
INCLUDE = -I${FASTFORMAT_ROOT}/include -I${STLSOFT}/include
LINKS = -lGL -lGLEW -lpng
FRAMEWORKS = -framework Foundation -framework AppKit
DEFINES = -g -DDEBUG -DPLATFORM_XWS_GNUPOSIX

################################################################################

clean:
	rm -r ${MAKEDIR}

# TODO: Consider using a perl script for nicer output
#| awk -F: '{ print $$1":"$$2":\n    "; for(i=3;i<NF;i++){printf " %s", $$i} printf "\n" }'
todo:
	grep -nr --include \* --exclude-dir=make "TODO:[ ]\+" .  # Using '[ ]' so the grep line is ignored by grep

################################################################################

PROJNAME = BQTDraw

APPNAME = ${PROJNAME}.app
PKGINFOSTRING = APPL????

################################################################################

osx_install: osx
	cp -ar "${MAKEDIR}/${APPNAME}" "/Applications/${APPNAME}"

linux_install: linux
	cd "${MAKEDIR}/${PROJNAME}"; sudo ./install_linux.sh

################################################################################

# linux_profile: linux
# 	valgrind --tool=callgrind "${MAKEDIR}/${PROJNAME}/Linux/${PROJNAME}" -d

################################################################################

osx: build_osx
	mkdir -p "${MAKEDIR}/${APPNAME}/Contents/MacOS"
	mkdir -p "${MAKEDIR}/${APPNAME}/Contents/Resources"
	cp "${RESOURCEDIR}/Info.plist" "${MAKEDIR}/${APPNAME}/Contents/Info.plist"
	cp "${RESOURCEDIR}/launch_osx.sh" "${MAKEDIR}/${APPNAME}/Contents/MacOS/launch_osx.sh"
	cp "${BUILDDIR}/${PROJNAME}" "${MAKEDIR}/${APPNAME}/Contents/MacOS/${PROJNAME}"
	echo ${PKGINFOSTRING} > "${MAKEDIR}/${APPNAME}/Contents/PkgInfo"
	cp "${RESOURCEDIR}/${PROJNAME}_app.icns" "${MAKEDIR}/${APPNAME}/Contents/Resources/${PROJNAME}_app.icns"
	cp "${RESOURCEDIR}/gui_resources.png" "${MAKEDIR}/${APPNAME}/Contents/Resources/gui_resources.png"

linux: build_linux
	mkdir -p "${MAKEDIR}/${PROJNAME}/Linux"
	mkdir -p "${MAKEDIR}/${PROJNAME}/Resources"
	cp "${RESOURCEDIR}/install_linux.sh" "${MAKEDIR}/${PROJNAME}/install_linux.sh"
	cp "${BUILDDIR}/${PROJNAME}" "${MAKEDIR}/${PROJNAME}/Linux/${PROJNAME}"
	cp "${RESOURCEDIR}/${PROJNAME}_app_16p.png" "${MAKEDIR}/${PROJNAME}/Resources/${PROJNAME}_app_16p.png"
	cp "${RESOURCEDIR}/${PROJNAME}_app_32p.png" "${MAKEDIR}/${PROJNAME}/Resources/${PROJNAME}_app_32p.png"
	cp "${RESOURCEDIR}/${PROJNAME}_app_128p.png" "${MAKEDIR}/${PROJNAME}/Resources/${PROJNAME}_app_128p.png"
	cp "${RESOURCEDIR}/${PROJNAME}_app_256p.png" "${MAKEDIR}/${PROJNAME}/Resources/${PROJNAME}_app_256p.png"
	cp "${RESOURCEDIR}/${PROJNAME}_app_512p.png" "${MAKEDIR}/${PROJNAME}/Resources/${PROJNAME}_app_512p.png"
	cp "${RESOURCEDIR}/gui_resources.png" "${MAKEDIR}/${PROJNAME}/Resources/gui_resources.png"

windows:
	# Not supported yet

################################################################################

# TODO: consider using macro(s)
CORE_OBJECTS =	${OBJDIR}/bqt_events.o \
				${OBJDIR}/bqt_exception.o \
				${OBJDIR}/bqt_fileformat.o \
				${OBJDIR}/bqt_gl.o \
				${OBJDIR}/bqt_imagemode.o \
				${OBJDIR}/bqt_keycode.o \
				${OBJDIR}/bqt_launchargs.o \
				${OBJDIR}/bqt_main.o \
				${OBJDIR}/bqt_platform.c.o \
				${OBJDIR}/bqt_png.o \
				${OBJDIR}/bqt_preferences.o \
				${OBJDIR}/bqt_taskexec.o \
				${OBJDIR}/bqt_taskqueue.o \
				${OBJDIR}/bqt_timestamp.o \
				${OBJDIR}/bqt_trackable.o \
				${OBJDIR}/bqt_window.o \
				${OBJDIR}/bqt_windowevent.o \
				${OBJDIR}/bqt_windowmanagement.o \
				${OBJDIR}/threading.bqt_condition.o \
				${OBJDIR}/threading.bqt_mutex.o \
				${OBJDIR}/threading.bqt_rwlock.o \
				${OBJDIR}/threading.bqt_semaphore.o \
				${OBJDIR}/threading.bqt_threadutil.o \
				${OBJDIR}/threading.bqt_thread.o  \
				${OBJDIR}/gui.bqt_gui_button.o  \
				${OBJDIR}/gui.bqt_gui_element.o  \
				${OBJDIR}/gui.bqt_gui_resource.o

OSX_OBJECTS =	${OBJDIR}/cocoa_appdelegate.o \
				${OBJDIR}/cocoa_main.o

LINUX_OBJECTS = ${OBJDIR}/x_main.o

# FastFormat is statically linked due to the non-standard build methods the
# project uses.  Until it is updated to use Autotools it should remain statical-
# ly linked for ease of (precompiled binary) distribution.
# Not sure how many of these we need, so include all of them
FF_OBJECTS =	${FFOBJDIR}/core.api.o \
				${FFOBJDIR}/core.fmt_cache.o \
				${FFOBJDIR}/core.fmt_spec_defect_handlers.o \
				${FFOBJDIR}/core.init_code_strings.o \
				${FFOBJDIR}/core.mempool.o \
				${FFOBJDIR}/core.replacements.o \
				${FFOBJDIR}/core.snprintf.o

################################################################################

# ${OBJDIR}/bqt_.o

build_osx: ${CORE_OBJECTS} ${OSX_OBJECTS}
	make fastformat
	mkdir -p ${BUILDDIR}
	${CPPC} -o "${BUILDDIR}/${PROJNAME}" ${FRAMEWORKS} ${LINKS} -lobjc $? ${FF_OBJECTS}

build_linux: ${CORE_OBJECTS} ${LINUX_OBJECTS}
	make fastformat
	mkdir -p ${BUILDDIR}
	${CPPC} -o "${BUILDDIR}/${PROJNAME}" ${LINKS} -lpthread -lX11 -lXext -lXi $? ${FF_OBJECTS}

fastformat:
	cd ${FFOBJDIR}; make build.libs.core

################################################################################

${OBJDIR}/unix_%.o: ${SOURCEDIR}/unix_%.cpp
	mkdir -p ${OBJDIR}
	${CPPC} ${DEFINES} -c ${INCLUDE} $? -o ${OBJDIR}/unix_$*.o

${OBJDIR}/cocoa_%.o: ${SOURCEDIR}/cocoa_%.m
	mkdir -p ${OBJDIR}
	${OBJCC} ${DEFINES} -c ${INCLUDE} $? -o ${OBJDIR}/cocoa_$*.o

${OBJDIR}/bqt_%.c.o: ${SOURCEDIR}/bqt_%.c
	mkdir -p ${OBJDIR}
	${CPPC} ${DEFINES} -c ${INCLUDE} $? -o ${OBJDIR}/bqt_$*.c.o

${OBJDIR}/bqt_%.o: ${SOURCEDIR}/bqt_%.cpp
	mkdir -p ${OBJDIR}
	${CPPC} ${DEFINES} -c ${INCLUDE} $? -o ${OBJDIR}/bqt_$*.o

${OBJDIR}/gui.bqt_%.o: ${SOURCEDIR}/gui/bqt_%.cpp
	mkdir -p ${OBJDIR}
	${CPPC} ${DEFINES} -c ${INCLUDE} $? -o ${OBJDIR}/gui.bqt_$*.o

${OBJDIR}/threading.bqt_%.o: ${SOURCEDIR}/threading/bqt_%.cpp
	mkdir -p ${OBJDIR}
	${CPPC} ${DEFINES} -c ${INCLUDE} $? -o ${OBJDIR}/threading.bqt_$*.o

${OBJDIR}/x_%.o: ${SOURCEDIR}/x_%.cpp
	mkdir -p ${OBJDIR}
	${CPPC} ${DEFINES} -c ${INCLUDE} $? -o ${OBJDIR}/x_$*.o

################################################################################

.PHONY: fastformat build_linux build_osx osx linux windows clean todo


