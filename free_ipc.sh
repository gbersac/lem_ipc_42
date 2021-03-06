#!/bin/sh
# kill ipc progs
ps | grep "lem_ipc" | awk 'BEGIN { FS = " " } ; { system("sleep" " 0.1") ; system("kill "$1) }'
# free all ressources in ipc
ipcs | grep ^m |  awk 'BEGIN { FS = " " } ; { system("ipcrm -m "$2) }'
ipcs | grep ^s |  awk 'BEGIN { FS = " " } ; { system("ipcrm -s "$2) }'
ipcs | grep ^q |  awk 'BEGIN { FS = " " } ; { system("ipcrm -q "$2) }'
