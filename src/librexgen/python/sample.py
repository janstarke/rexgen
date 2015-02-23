from rexgen import *

if __name__ == '__main__':
	for word in Iterator("abc[1-3]"):
		print word
