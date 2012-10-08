#!/usr/bin/python

import sys

def print_err(*args):
	arg = ''
	for i in xrange(len(args)):
		arg+=args[i]
	arg+="\r\n"
	sys.stderr.write(arg)
	sys.stderr.flush()

def main():
	if len(sys.argv) < 2:
		print_err("Usage: ", sys.argv[0], " filename1 [filename2 [filename3 [...]]")
	for i in xrange(1, len(sys.argv)):
		filename = sys.argv[i]
		try:
			matrix = []
			with open(filename, 'r') as filehandle:
				for line in filehandle:
					for j in line.split():
						matrix.append(int(j))
				print sorted(matrix)
		except IOError, e:
			print_err("Can not open file ", filename, ":\r\n\t", "I/O error({0}): {1}".format(e.errno, e.strerror))
		except Exception, e:
			raise e
	pass

main()