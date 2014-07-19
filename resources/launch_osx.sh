#!/bin/sh

cd "${0%/*}"
cd ..

# Linux release
# ./BQTDraw -l~/.BQTDraw_log.txt -d -p~/.BQTDraw.cfg > ~/BQTDraw_crashlog.txt

# OS X release
# ./MacOS/BQTDraw -l~/.BQTDraw_log.txt -p~/Application\ Support/BQTDraw/BQTDraw.cfg > ~/BQTDraw_crashlog.txt

# OS X devel
./MacOS/BQTDraw -l../../BQTDraw_log.txt -d -p~/Application\ Support/BQTDraw/BQTDraw.cfg > -l../../BQTDraw_crashlog.txt

if [ test -s ~/BQTDraw_crashlog.txt ] ; then
    echo BQTDraw has crashed, see BQTDraw_crashlog.txt
    # echo BQTDraw has crashed, see ~/BQTDraw_crashlog.txt
else
    rm -f ~/BQTDraw_crashlog.txt

# Options:
# [ -h | --help ] Prints usage guide & exits
# [ -v | --version ] Prints the software version & exits
# [ -f | --open-file ] FILE Opens file on startup
# [ -l | --log-file ] FILE Sets a log file, none by default
# [ -d | --dev-mode ] Enables developer mode options
# [ -t | --task-threads ] UINT Limits the max number of task threads; 0 = no limit
# Options are applied in order, so it is recommended to change the log file first to log any init errors