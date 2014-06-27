#!/bin/sh
cd "${0%/*}"
cd ..
./MacOS/BQTDraw -l../../BQTDraw.txt -d

# Options:
# [ -h | --help         ]            Prints usage guide & exits
# [ -v | --version      ]            Prints the software version & exits
# [ -f | --open-file    ] FILE       Opens file on startup
# [ -u | --max-undo     ] INT        Max undo & redo steps; -1 for unlimited
# [ -l | --log-file     ] FILE       Sets a log file, none by default
# [ -d | --dev-mode     ]            Enables developer mode options
# [ -t | --task-threads ] UINT       Limits the max number of task threads; 0 = no limit
# [ -e | --block-exp    ] UINT       Sets the block texture size: 2^exp x 2^exp; 1 <= exp <= 255
# Options are applied in order, so it is recommended to change the log file first to log any init errors