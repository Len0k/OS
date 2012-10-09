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
		print_err("Usage: {0} filename1 [filename2 [filename3 [...]]".format(sys.argv[0]))
	matrix = []
	for i in xrange(1, len(sys.argv)):
		filename = sys.argv[i]
		try:
			with open(filename, 'r') as filehandle:
				for line in filehandle:
					for j in line.split():
						try:
							matrix.append(int(j))
						except ValueError, e:
							print_err("ValueError in {0}:\r\n\t{1}".format(filename, e.message))
		except IOError, e:
			print_err("Can not open file ", filename, ":\r\n\t", "I/O error({0}): {1}".format(e.errno, e.strerror))
		except MemoryError, e:
			print_err("AAA! Out of memory by file {0}!!!".format(filename))
			raise e
		except Exception, e:
			raise e
	print sorted(matrix)


main()