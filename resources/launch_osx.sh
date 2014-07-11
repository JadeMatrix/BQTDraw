#!/bin/sh
cd "${0%/*}"
cd ..
./MacOS/BQTDraw -l../../BQTDraw.txt -d -p~/.BQTDraw.cfg

# Options:
# [ -h | --help         ]            Prints usage guide & exits
# [ -v | --version      ]            Prints the software version & exits
# [ -f | --open-file    ] FILE       Opens file on startup
# [ -l | --log-file     ] FILE       Sets a log file, none by default
# [ -d | --dev-mode     ]            Enables developer mode options
# [ -t | --task-threads ] UINT       Limits the max number of task threads; 0 = no limit
# Options are applied in order, so it is recommended to change the log file first to log any init errors