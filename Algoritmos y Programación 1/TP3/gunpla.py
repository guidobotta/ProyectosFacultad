class Gunpla:
	"""Representa un Gunpla. Un Gunpla esta compuesto de un Esqueleto, un conjunto 
	de partes y un conjunto de armas."""

	def __init__(self,peso,armadura,escudo,velocidad,energia,energia_restante,movilidad,armamento):
		"""Constructor de la clase Gunpla"""
		self.peso = peso
		self.armadura = armadura
		self.escudo = escudo
		self.velocidad = velocidad
		self.energia = energia
		self.energia_restante = energia_restante 
		self.movilidad = movilidad	
		self.armamento = armamento 		

	def get_peso (self):
		"""	Devuelve el peso total del Gunpla. Un Gunpla pesa lo que 
		pesa la sumatoria de sus partes y armas"""		
		return self.peso	 

	def get_armadura (self):
		"""Devuelve la armadura total del Gunpla. Un Gunpla tiene tanta 
		armadura como la sumatoria de la armadura de sus partes y armas"""			
		return self.armadura 

	def get_escudo (self):
		"""Devuelve el escudo total del Gunpla. Un Gunpla tiene tanto escudo 
		como la sumatoria del escudo de sus partes y armas"""			
		return self.escudo

	def get_velocidad (self):
		"""Devuelve la velocidad total del Gunpla. Un Gunpla tiene tanta velocidad 
		como la sumatoria de las velocidades de sus partes y esqueleto"""	
		return self.velocidad

	def get_energia (self):
		"""Devuelve la energía total del Gunpla. Un Gunpla tiene tanta energía como la 
		sumatoria de la energía de sus partes, armas y esqueleto"""	
		return self.energia

	def get_energia_restante (self):
		"""Devuelve la energía que le resta al Gunpla"""
		return self.energia_restante

	def get_movilidad (self):
		"""Devuelve la movilidad de un Gunpla. Se calcula segun la fórmula
		movilidad=(base-peso/2+velocidad*3)/base Siendo base la movilidad del esqueleto, 
		peso el peso del Gunpla y velocidad la velocidad del Gunpla.
		La movilidad tiene un límite superior de 1 e inferior de 0."""
		return self.movilidad 

	def get_armamento (self):
		"""Devuelve una lista con todas las armas adosadas al Gunpla 
		(Se incluyen las armas disponibles en las partes)"""
		return self.armamento