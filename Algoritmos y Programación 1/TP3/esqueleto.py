class Esqueleto:
	"""Representa al esqueleto interno del Gunpla"""
			
	def __init__(self, velocidad, energia, movilidad, slots):
		"""Constructor de la clase Esqueleto"""
		self.velocidad = velocidad
		self.energia = energia
		self.movilidad = movilidad
		self.slots = slots
	
	def get_velocidad (self):
		"""Devuelve la velocidad del esqueleto. Es un valor fijo"""
		return self.velocidad
	
	def get_energia (self):
		"""Devuelve la energía del esqueleto. Es un valor fijo"""
		return self.energia
	
	def get_movilidad (self):
		"""Devuelve la movilidad del esqueleto. Es un valor fijo"""
		return self.movilidad
	
	def get_cantidad_slots (self):
		"""Devuelve la cantidad de slots (ranuras) para armas que tiene el esqueleto. Es un valor fijo"""
		return self.slots