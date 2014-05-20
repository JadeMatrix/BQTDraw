#!/bin/sh
cd "${0%/*}"
cd ..
./MacOS/BQTDraw -l../../BQTDraw.txt -d -t2

# Options:
# [ -d | --devmode     ]            Enables developer mode options
# [ -l | --logfile     ] FILE       Sets a log file, none by default
# [ -t | --taskthreads ] UINT       Limits the max number of task threads; 0 = no limit
# Options are applied in order, so it is recommended to change the log file first to log any init errors