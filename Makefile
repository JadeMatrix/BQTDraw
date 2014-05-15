################################################################################

# Compiler(s)
CC = gcc
CPPC = g++

# Directories
SOURCEDIR = src
RESOURCEDIR = resources
MAKEDIR = make
OBJDIR = ${MAKEDIR}/object
BUILDDIR = ${MAKEDIR}/build

# Fast format build version folder
FFBUILD = gcc40.mac.x64
FFOBJDIR = ${FASTFORMAT_ROOT}/build/${FFBUILD}

# Headers & librarires
INCLUDE = -I${FASTFORMAT_ROOT}/include -I${STLSOFT}/include
LINKS = 

################################################################################

clean:
	rm -r ${MAKEDIR}

# TODO: Consider using a perl script for nicer output
#| awk -F: '{ print $$1":"$$2":\n    "; for(i=3;i<NF;i++){printf " %s", $$i} printf "\n" }'
todo:
	grep -nr --include \* "TODO:[ ]\+" .  # Using '[ ]' so the grep line is ignored by grep

################################################################################

PROJNAME = BQTDraw

APPNAME = ${PROJNAME}.app
PKGINFOSTRING = APPL????

################################################################################

osx: build
	mkdir -p "${MAKEDIR}/${APPNAME}/Contents/MacOS"
	mkdir -p "${MAKEDIR}/${APPNAME}/Contents/Resources"
	cp "${RESOURCEDIR}/Info.plist" "${MAKEDIR}/${APPNAME}/Contents/Info.plist"
	cp "${SOURCEDIR}/launch.sh" "${MAKEDIR}/${APPNAME}/Contents/MacOS/launch.sh"
	cp "${BUILDDIR}/${PROJNAME}" "${MAKEDIR}/${APPNAME}/Contents/MacOS/${PROJNAME}"
	echo ${PKGINFOSTRING} > "${MAKEDIR}/${APPNAME}/Contents/PkgInfo"
	cp "${RESOURCEDIR}/${PROJNAME}_app.icns" "${MAKEDIR}/${APPNAME}/Contents/Resources/${PROJNAME}_app.icns"

linux:
	# Not supported yet

windows:
	# Not supported yet

################################################################################

# TODO: consider using macro(s)
CORE_OBJECTS =	${OBJDIR}/bqt_condition.o \
				${OBJDIR}/bqt_exception.o \
				${OBJDIR}/bqt_launchargs.o \
				${OBJDIR}/bqt_main.o \
				${OBJDIR}/bqt_mutex.o \
				${OBJDIR}/bqt_semaphore.o \
				${OBJDIR}/bqt_taskexec.o \
				${OBJDIR}/bqt_taskqueue.o \
				${OBJDIR}/bqt_threadutil.o \
				${OBJDIR}/bqt_thread.o

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

build: ${CORE_OBJECTS}
	make fastformat
	mkdir -p ${BUILDDIR}
	${CPPC} -o "${BUILDDIR}/${PROJNAME}" ${LINKS} $? ${FF_OBJECTS}

# Making FastFormat assumes you have FASTFORMAT_ROOT and STLSOFT set as specified in the FastFormat INSTALL.txt
fastformat:
	cd ${FFOBJDIR}; make build.libs.core

################################################################################

${OBJDIR}/%.o: ${SOURCEDIR}/%.cpp
	mkdir -p ${OBJDIR}
	${CPPC} -c ${INCLUDE} $? -o ${OBJDIR}/$*.o


