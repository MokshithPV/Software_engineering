class _DoubleLinkedBase:
	""" A base class providing a doubly linked list representation."""

	class _Node:
		""" Lightweight, nonpublic class for storing a doubly linked node"""
		__slots__ = '_element', '_prev', '_next' # streamline memory

		def __init__(self, element, prev, next): # initialize node's fields
			self._element = element
			self._prev = prev
			self._next = next

	def __init__(self):
		"""Create an empty list"""
		self._header = self._Node(None, None, None)
		self._trailer = self._Node(None, None, None)
		self._header._next = self._trailer
		self._trailer._prev = self._header
		self._size = 0 # number of elements

	def __len__(self):
		"""Return the number of elements in the list"""
		# ===== Start writing your code here =====
		return self._size
		# ===== End writing your code here =====

	def is_empty(self):
		"""Return true if list is empty"""
		# ===== Start writing your code here =====
		if(self._size): return False
		return True
		# ===== End writing your code here =====

	def _insert_between(self, e, predecessor, successor):
		"""Add element e between two existing nodes and return new node"""
		newest = self._Node(e, predecessor, successor)
		# ===== Start writing your code here =====
		if predecessor._next == successor :
			self._size += 1
			del(predecessor._next)
			predecessor._next = newest
			successor._prev = newest
			return newest
		else:
			print("Couldn't add a new node because predecessor and successor are not next to each other")
			return None
		# ===== End writing your code here =====

	def _delete_node(self, node):
		"""Delete nonsentinel node from the list and return its elements"""
		# ===== Start writing your code here =====
		if(node._element == None and (node._prev == None or node._next == None)):
			print("node cannot be deleted because it is a sentinel node")
			return None
		node._prev._next = node._next
		node._next._prev = node._prev
		i = node._element
		del(node)
		self._size -= 1
		return i
		# ===== End writing your code here =====
