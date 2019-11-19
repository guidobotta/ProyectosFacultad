TIPOS_PARTES = ("SHIELD","WINGS","GLOVES","BOOTS","JETPACK","BODY-ARMOR","LEG-ARMOR","ARM-ARMOR","HELMET","BACKPACK","BELT","SHOULDER PADS","ROCKET BOOTS")
PARTES_COMPATIBLES = ("SHIELD","GLOVES","BOOTS","BODY-ARMOR","LEG-ARMOR","ARM-ARMOR","BELT")	

class Parte:
	"""Representa una parte de un Gunpla"""
	
	def __init__ (self,peso,armadura,escudo,velocidad,energia,armamento,tipo_de_parte):
		"""Constructor de la clase Parte"""
		self.peso = peso
		self.armadura = armadura
		self.escudo = escudo
		self.velocidad = velocidad
		self.energia = energia
		self.armamento = armamento
		self.tipo_de_parte = tipo_de_parte

	def get_peso(self):
		"""Devuelve el peso total de la parte. Una parte pesa 
		lo que pesa la sumatoria de sus armas más el peso base de la parte"""
		armas = self.armamento 
		peso_armas = 0
		for arma in armas:
		  peso_armas += arma.get_peso() 
		return self.peso 

	def get_armadura(self):
		"""Devuelve la armadura total de la parte. Una parte tiene tanta armadura
		como la sumatoria de la armadura de sus armas más la armadura base de la parte"""
		armas = self.armamento
		armadura_armas = 0
		for arma in armas:
		  armadura_armas += arma.get_armadura()  
		return self.armadura + armadura_armas
		
	def get_escudo(self):
		"""Devuelve el escudo total de la parte. Una parte tiene tanto escudo como la 
		sumatoria del escudo de sus armas más el escudo base de la parte"""
		armas = self.armamento
		escudo_armas = 0
		for arma in armas:
		  escudo_armas += arma.get_escudo()
		return self.escudo + escudo_armas

	def get_velocidad(self):
		"""Devuelve la velocidad total de la parte. Es un valor fijo"""
		return self.velocidad

	def get_energia(self):
		"""Devuelve la energía total de la parte. La parte tiene tanta energía como la 
		sumatoria de la energía de sus armas más la energía base de la parte"""
		armas = self.armamento 
		energia_armas = 0
		for arma in armas:
		  energia_armas += arma.get_energia()  
		return self.energia + energia_armas

	def get_armamento(self):
		"""Devuelve una lista con todas las armas adosadas a la parte"""
		return self.armamento

	def get_tipo_parte(self):
		"""Devuelve una cadena que representa el tipo de parte. Ej: "Backpack" """
		return self.tipo_de_parte
				  
