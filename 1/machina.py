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
	IP = 0
	IR = 0
	global RON
	while (1):
		COP = proga[IP][1]
		ADDR = proga[IP][2]
		dekkom(COP)
		IA = t1 = IP + IR
		t0 = proga[t1][2]
		t2 = RVV
		t1 = m(t0, t1, t2, vib)
		t0 = RON
		t0 = alu (t0, t1)
		# IR
		t = m(t0, 0, chist)
		if (zam2 == 1):
			IR = t
		# RON
		if (zam1 == 1):
			RON = t0
		# memory
		if (zapp == 1):
			proga[IP+IA][2] = t0
		# next command
		t = m(IP+1, IA, hash[COP][3])
		if (pusk == 1):
			IP = t
		else:
			break

def dekkom(com):
	global RON
	hash[com][3] = 1 - RON
	p = hash[com][1]
	if (p == 0):
		zapp = 1
	if (p == 1):
		zam1 = 1
	if (p == 3):
		vzap1 = 1
	if (p != 3):
		zam2 = 1
	if not (p == 2 or p ==3):
		chist = 1
	if (com != 'FF'):
		pusk = 1
	vib = hash[com][0]

def alu(arg0, arg1):
	global COP
	op = hash[COP][2]
	#switch (op):
	if (op == 0):
		return arg0
	if (op == 1):
		return arg1
	if (op == 2):
		return arg0 + arg1
	if (op == 3):
		return arg1 - arg0
	if (op == 15):
		return -1
	return -1

def ukkom(adrcom):
	if (pusk == 1):
		ip = adrcom
	return ip
def m(*args):
	return args[args[-1]]
	
(p, zapp, zapp1, vzap1, zam1, op, pusk, chist, RON, IP, ADDR, IR) = (0,0,0,0,0,0,0,0,0,0, 0, 0)
RVV = 0
vib = 0
COP = ""
main()
