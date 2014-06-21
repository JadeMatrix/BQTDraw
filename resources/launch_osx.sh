#!/bin/sh
cd "${0%/*}"
cd ..
./MacOS/BQTDraw -l../../BQTDraw.txt -d -t2

# Options:
# [ -h | --help        ]            Prints usage guide & exits
# [ -v | --version     ]            Prints the software version & exits
# [ -f | --open-file   ] FILE       Opens file on startup
# [ -l | --logfile     ] FILE       Sets a log file, none by default
# [ -d | --devmode     ]            Enables developer mode options
# [ -t | --taskthreads ] UINT       Limits the max number of task threads; 0 = no limit
# [ -e | --blockexp    ] UINT       Sets the block texture size: 2^exp x 2^exp; 1 <= exp <= 255
# Options are applied in order, so it is recommended to change the log file first to log any init errors