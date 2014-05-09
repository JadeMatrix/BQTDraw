# Info for using homebrew's clang:
# http://stackoverflow.com/questions/14128298/homebrew-gcc-llvm-and-c11

################################################################################

# Compiler(s)
CC = gcc
CPP = g++

# Directories
SOURCEDIR = src
RESOURCEDIR = resources
MAKEDIR = make
OBJDIR = ${MAKEDIR}/object
BUILDDIR = ${MAKEDIR}/build

# Linked librarires
LINKS = ""

################################################################################

clean:
	rm -r ${MAKEDIR}

# TODO: Consider using a perl script for nicer output
#| awk -F: '{ print $$1":"$$2":\n    "; for(i=3;i<NF;i++){printf " %s", $$i} printf "\n" }'
todo:
	grep -n "TODO:" *.*

################################################################################

PROJNAME = BQTDraw

APPNAME = ${PROJNAME}.app
PKGINFOSTRING = APPL????

################################################################################

osx: build
	mkdir -p "${MAKEDIR}/${APPNAME}/Contents/MacOS"
	mkdir -p "${MAKEDIR}/${APPNAME}/Contents/Resources/Images"
	mkdir -p "${MAKEDIR}/${APPNAME}/Contents/Resources/Scripts"
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

build: ${OBJDIR}/bqt_main.o ${OBJDIR}/bqt_launchargs.o ${OBJDIR}/bqt_exception.o
	mkdir -p ${BUILDDIR}
	${CPP} -o "${BUILDDIR}/${PROJNAME}" ${LINKS} $?

################################################################################

${OBJDIR}/%.o: ${SOURCEDIR}/%.cpp
	mkdir -p ${OBJDIR}
	${CPP} -c $? -o ${OBJDIR}/$*.o


