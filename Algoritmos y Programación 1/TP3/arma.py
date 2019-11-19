MELEE, RANGO = "MELEE", "RANGO"
FISICA, LASER, HADRON = "FISICA", "LASER", "HADRON"
ARMAS_MELEE = ("GN Blade", "Greater Blade", "Golden Blade", "Ancient Mace", "Dagger","Wood Katana","Chains")
ARMAS_RANGO = ("Submachine Gun", "MP40", "Machine Cannon", "Buster Rifle","Scar","Vector","M416","MicroUzi","Awm")
TIPOS_ARMAS = {MELEE : ARMAS_MELEE, RANGO : ARMAS_RANGO}
TIPOS_MUNICION = [FISICA, LASER, HADRON]

class Arma:
	"""Representa un arma"""
	
	def __init__(self, peso, armadura, escudo, velocidad, energia, tipo_de_municion, tipo_de_arma, clase_de_arma, daño, hits, precision, tiempo_de_recarga):
		"""Constructor de la clase Arma"""
		self.peso = peso
		self.armadura = armadura 		
		self.escudo = escudo
		self.velocidad = velocidad
		self.energia = energia
		self.tipo_de_municion = tipo_de_municion
		self.tipo_de_arma = tipo_de_arma
		self.clase_de_arma = clase_de_arma
		self.daño = daño
		self.hits = hits
		self.precision = precision
		self.tiempo_de_recarga = tiempo_de_recarga
		self.disponible = True
		self.tipo_de_parte = "Arma"
			
	def get_peso (self):
		"""Devuelve el peso del arma. Es un valor fijo"""
		return self.peso
	  
	def get_armadura (self):
		"""Devuelve la armadura del arma. Es un valor fijo"""
		return self.armadura
	  
	def get_escudo (self):
		"""Devuelve el escudo del arma. Es un valor fijo"""
		return self.escudo
	  
	def get_velocidad (self):
		"""Devuelve la velocidad del arma. Es un valor fijo"""
		return self.velocidad
	  
	def get_energia (self):
		"""Devuelve la energía del arma. Es un valor fijo"""
		return self.energia
	  
	def get_tipo_municion (self):
		"""Devuelve el tipo de munición del arma: "FISICA"|"LASER"|"HADRON" """
		return self.tipo_de_municion
	  
	def get_tipo (self):
		"""Devuelve el tipo del arma: "MELEE"|"RANGO" """
		return self.tipo_de_arma
	  
	def get_clase (self):
		"""Devuelve la clase del arma, la cual es un string. Ejemplo "GN Blade" """
		return self.clase_de_arma
	  
	def get_daño (self):
		"""Devuelve el daño de un ataque del arma. Es un valor fijo"""
		return self.daño
	  
	def get_hits (self):
		"""Devuelve la cantidad de veces que puede atacar un arma en un turno. Es un valor fijo"""
		return self.hits
	  
	def get_precision (self):
		"""Devuelve la precisión del arma"""
		return self.precision
	  
	def get_tiempo_recarga (self):
		"""Devuelve la cantidad de turnos que tarda un arma en estar lista"""
		return self.tiempo_de_recarga
	  
	def esta_lista (self):
		""" Devuelve si el arma es capaz de ser utilizada en este turno o no"""
		return self.disponible
	  
	def get_tipo_parte (self):
		"""Devuelve el tipo de parte de un arma. Siempre es "Arma" """
		return self.tipo_de_parte