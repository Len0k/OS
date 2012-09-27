#!/usr/bin/python
import sys

com_table = {'00': [1, 0, 0, 0], '11': [0, 1, 1, 0], '15': [1, 1 ,1 ,0],
	'02': [0, 2, 0, 0], '21': [0, 1, 2, 0], '25': [1, 1, 2, 0],
	'31': [0, 1, 3, 0], 'FE': [-1, 4, 15, 1], 'F0': [-1, 4, 15, 0],
		'F1': [1, 4, 15, 0], 'F4': [1, 4, 15, 1],
		'F5': [1, 4, 15, 0], 'FF': [1, 4, 15, 0] }
	
def main():
	global RON, RVV, zapp, zam1, vzap1, zam2, chist, pusk, vib, com_table
	if (len(sys.argv)<2):
		print "Usage: program filename [zapp|zam1|vzap1|zam2|chist|pusk|vib|op|pereh]"
	proga = open(sys.argv[1]).read().split("\n")
	if (len(sys.argv) > 2):
		broken = sys.argv[2]
		if broken == 'op':
			for i in com_table.keys():
				com_table[i][2] = 0
		if broken == 'pereh':
			for i in com_table.keys():
				com_table[i][3] = 0
	for i in xrange(len(proga)):
		ip, com = proga[i].split(":")
		ip = int(ip)
		cop, arg = com.split()
		arg = int(arg)
		proga[i] = [ip, cop, arg]
	pusk = 1
	IP = 0
	IR = 0
	global RON
	while 1:
		com_table['F0'][3]  = com_table['F1'][3] = 1 - RON
		global COP
		COP = proga[IP][1].upper()
		ADDR = proga[IP][2]
		dekkom(COP)
		setConstants()
		IA = t1 = ADDR + IR
		t0 = proga[t1][2]
		t2 = RVV
		t1 = m(t0, t1, t2, vib)
		t0 = RON
		t0 = alu (t0, t1)
		# IR
		t = m(t0, 0, chist)
		if zam2 == 1:
			IR = t
		# RON
		if zam1 == 1:
			RON = t0
		# memory
		if zapp == 1:
			proga[IP+IA][2] = t0
		# next command
		t = m(IP+1, IA, com_table[COP][3])
		if pusk == 1:
			IP = t
		else:
			break
	#print finish state
	print "Instruction pointer: " + str(IP)
	print "General-purpose register: " + str(RON)
	print "Index register: " + str(IR)
	#print memory
	print "Memory:"
	for i in xrange(len(proga)):
		print i, ':', proga[i][2]

def dekkom(com):
	global RON, zapp, zam1, vzap1, zam2, chist, pusk, vib, com_table
	p = com_table[com][1]
	zapp = 1 if p == 0 else 0
	zam1 = 1 if p == 1 else 0
	vzap1 = 1 if p == 3 else 0
	zam2 = 1 if p != 3 else 0
	chist = 1 if p ==2 or p ==3 else 0
	pusk = 0 if com == 'FF' else 1
	vib = com_table[com][0]

def alu(arg0, arg1):
	global COP, com_table, RON
	op = com_table[COP][2]
	#switch (op):
	if op == 0:
		return arg0
	if op == 1:
		return arg1
	if op == 2:
		return arg0 + arg1
	if op == 3:
		return arg1 - arg0
	if op == 15:
		return RON
	return -1

def m(*args):
	return args[args[-1]]

def setConstants():
	global zapp, zam1, vzap1, zam2, chist, pusk, vib, com_table
	num_hash = {'zapp' : 0, 'zam1' : 1, 'vzap1' : 2,
		'zam2': 3, 'chist' : 4, 'pusk' : 5, 'vib' : 6}
	if len(sys.argv) > 2:
		broken = sys.argv[2]
		if broken in num_hash.keys():
			(zapp, zam1, vzap1, zam2, chist, pusk, vib)[num_hash[broken]] = 0


	
(p, zapp, zapp1, vzap1, zam1, op, chist, RON, IP, ADDR, IR) = (0,0,0,0,0,0,0,0,0, 0, 0)
RVV = 0
vib = 0
COP = ""
zam2 = 0

main()
