#!/usr/bin/python
import sys

def main():
	proga = open(sys.argv[1]).read().split("\n")[:-1]
	print proga
	pass

def ukkom():
	pass

def regkom():
	pass

def dekkom():
	hash = {'00': ["", 0, 0, 0], '11': [0, 1, 1, 0], '15': [1, 1 ,1 ,0],
		'02': ["", 2, 0, 0], '21': [0, 1, 2, 0], '25': [1, 1, 2, 0],
		'31': [0, 1, 3, 0], 'FE': ["", 4, 15, 1], 'F0': ["", 4, 15, 1],
		'F1': ["", 4, 15, 0], 'F4': ["", 4, 15, 1],
		'F5': ["", 4, 15, 0], 'FF': ["", 4, 15, 0] }
	

def alu():
	pass

main()
