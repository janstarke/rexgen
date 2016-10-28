from ctypes import *
rexgen = cdll.LoadLibrary("@librexgen_filename@")

class SimpleString:
	def __init__(self):
		self.c_simplestring_new = rexgen.c_simplestring_new
		self.c_simplestring_new.restype = c_void_p

		self.c_simplestring_to_ansi_string = rexgen.c_simplestring_to_ansi_string
		self.c_simplestring_to_ansi_string.argtypes = [c_void_p, c_char_p, c_uint]

		self.c_simplestring_clear = rexgen.c_simplestring_clear
		self.c_simplestring_clear.argtypes = [c_void_p]
		self.c_iterator_value = rexgen.c_iterator_value
		self.c_iterator_value.argtypes = [c_void_p, c_void_p]

		self.__len = 64
		self.__buffer = create_string_buffer(self.__len);
		self.__str = self.c_simplestring_new()

	def next(self, raw_iterator):
		self.c_simplestring_clear(self.__str)
		self.c_iterator_value(raw_iterator, self.__str)
		self.c_simplestring_to_ansi_string(self.__str, self.__buffer, self.__len)
		return self.__buffer.value

class Iterator:
	def __init__(self, regex):
		self.c_regex_iterator = rexgen.c_regex_iterator
		self.c_regex_iterator.restype = c_void_p

		self.c_iterator_next = rexgen.c_iterator_next
		self.c_iterator_next.argtypes = [c_void_p]

		self.c_iterator_delete = rexgen.c_iterator_delete
		self.c_iterator_delete.argtypes=[c_void_p]

		self.__iterator = self.c_regex_iterator(regex, 0, 2, 0)
		self.__str = SimpleString()

	def __iter__(self):
		return self

	def next(self):
		if self.c_iterator_next(self.__iterator):
			return self.__str.next(self.__iterator)
		else:
			raise StopIteration()
