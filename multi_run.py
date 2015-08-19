#!/nfs/zfs-student-3/users/2013/gbersac/.brew/bin/python3
import subprocess
import os

NB_PROG = 3

for i in range(0, NB_PROG):
	print(os.getcwd())
	subprocess.Popen("./run.sh")
