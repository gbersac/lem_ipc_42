#!/nfs/zfs-student-3/users/2013/gbersac/.brew/bin/python3
import subprocess
import os

NB_PROG = 3

subprocess.call("./free_ipc.sh")
for i in range(0, NB_PROG):
	cmd = "./run.sh " + str(i + 1)
	fstdout = None
	# fstdout = open("player" + str(i + 1), "w+")
	subprocess.Popen(cmd, shell = True, stdout = fstdout)
