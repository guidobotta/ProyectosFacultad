class _Nodo:
	"""Representa un nodo, interior a la clase lista circular."""

	def __init__(self, dato, prox):
		"""Crea un nodo. Recibe un dato y la referencia al próximo."""
		self.dato = dato
		self.prox = prox

class Lista_Circular:
	"""Representa una lista circular con operaciones append, len y próximo"""

	def __init__(self):
		"""Crea una lista circular vacía."""
		self.prim = None
		self.len = 0
		self.actual = self.prim

	def append(self, dato):
		"""Recibe el dato que se quiere agregar. Agrega un nuevo nodo al final de la lista."""
		nuevo = _Nodo(dato, self.prim)
		if not self.prim: 
			nuevo.prox = nuevo
			self.prim = nuevo
			self.actual = nuevo
		else:
			actual = self.prim
			for lon in range(self.len - 1):
				actual = actual.prox
			actual.prox = nuevo
		self.len += 1
	
	def proximo(self):
		"""Adelanta al siguiente nodo, y lo devuelve, si la lista está vacía no hace nada"""
		if self.actual:
			proximo = self.actual.prox
			self.actual = proximo
			return proximo.dato
		  
	def get_primero(self):
		"""Devuelve el primer nodo."""
		return self.prim.dato

	def __len__(self):
		"""Devuelve la longitud de la lista."""
		return self.len