#!/usr/bin/python
import sys
hash = {'00': ["", 0, 0, 0], '11': [0, 1, 1, 0], '15': [1, 1 ,1 ,0],
	'02': ["", 2, 0, 0], '21': [0, 1, 2, 0], '25': [1, 1, 2, 0],
	'31': [0, 1, 3, 0], 'FE': ["", 4, 15, 1], 'F0': ["", 4, 15, 0],
		'F1': ["", 4, 15, 0], 'F4': ["", 4, 15, 1],
		'F5': ["", 4, 15, 0], 'FF': ["", 4, 15, 0] }
	
def main():
	proga = open(sys.argv[1]).read().split("\n")
	for i in xrange(len(proga)):
		(ip, com) = proga[i].split(":")
		ip = int(ip)
		(cop, arg) = com.split()
		arg = int(arg)
		proga[i] = [ip, cop, arg]
	COP = proga[i][1]
	ADDR = proga[i][2]

def dekkom(com):
	hash(com)[3] = !ron
	p = hash(com)[1]
	if (p == 0):
		zapp = 1
	if (p == 1):
		zapp1 = 1
	if (p == 3):
		vzap1 = 1
	if (p != 3):
		zam2 = 1
	if !(p == 2 or p ==3):
		chist = 1
	if (cop != 'FF'):
		pusk = 1
	vib = hash(com)[0]
	if ()

def alu(arg0, arg1):
	switch op:
		case 0:
			return arg0
		case 1:
			return arg1
		case 2:
			return arg0 + arg1
		case 3:
			return arg1 - arg0
		case 15:
			return -1
	return -1

def ukkom(adrcom):
	if (pusk == 1):
		ip = adrcom
	return ip
def m(*args):
	return args[args[-1]]
	
(p, zapp, zapp1, vzap1, zam, op, pusk, chist, ron, ip, COP, ADDR) = (0,0,0,0,0,0,0,0,0,0, 0, 0)
main()
