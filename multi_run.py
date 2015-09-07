#!/nfs/zfs-student-3/users/2013/gbersac/.brew/bin/python3
import subprocess
import os
import time

NB_TEAM = 2
PLAYER_TEAM = 3

subprocess.call("./free_ipc.sh")
for team in range(0, NB_TEAM):
	for player in range(0,PLAYER_TEAM):
		cmd = "./run.sh " + str(team + 1)
		fstdout = None
		# fstdout = open("player" + str(i + 1), "w+")
		subprocess.Popen(cmd, shell = True, stdout = fstdout)
		time.sleep(0.01)

