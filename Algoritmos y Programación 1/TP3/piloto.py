from random import choice

class Piloto:
	"""Inteligencia artificial para controlar un Gunpla."""

	def __init__(self):
		"""Crea un piloto y no recibe ningun parámetro"""
		self.gunpla = None

	def set_gunpla(self, gunpla):
		"""Asigna un Gunpla a un piloto"""
		self.gunpla = gunpla

	def get_gunpla(self):
		"""Devuelve el Gunpla asociado al piloto"""
		return self.gunpla

	def elegir_esqueleto(self, esqueletos):
		"""Dada una lista con esqueletos, devuelve el índice del esqueleto a 
		utilizar"""
		n = 0
		promedio_mov = 250
		promedio_energia = 300
		promedio_vel = 30
		promedio_slots = 3
		for esqueleto in esqueletos:
			movilidad = esqueleto.get_movilidad()
			energia = esqueleto.get_energia()
			velocidad = esqueleto.get_velocidad()
			slots = esqueleto.get_cantidad_slots()
			calidad = (movilidad/promedio_mov) + (energia/promedio_energia) + (velocidad/promedio_vel) + (slots/promedio_slots) 
			if n == 0 or calidad > mejor_calidad:
				n += 1
				mejor_calidad = calidad
				mejor_esqueleto = esqueleto
		return esqueletos.index(mejor_esqueleto)

	def elegir_parte(self, partes_disponibles):
		"""Dado un diccionario: {tipo_parte:parte}, devuelve el tipo de parte 
		que quiere elegir. Este metodo se utiliza para ir eligiendo de a una las partes 
		que se van a reservar para cada piloto, de entre las cuales va a poder elegir 
		para armar su modelo"""
		return choice(list(partes_disponibles.keys()))

	def _obtener_promedios(self):
		"""Devuelve los promedios de cada atributo"""
		promedio_vel = 20.5
		promedio_peso = 412
		promedio_armadura = 321
		promedio_escudo = 6 
		promedio_energia = 1447
		promedio_armas = 1.9
		promedio_daño = 2475
		promedio_hits = 2.78
		promedio_precision = 81
		promedio_tiempo = 3.16
		
		return promedio_vel,promedio_peso,promedio_armadura,promedio_escudo,promedio_energia, \
		promedio_armas,promedio_daño,promedio_hits,promedio_precision,promedio_tiempo
    

	def _obtener_atributos(self,parte):
		"""Devuelve algunos atriburos de la parte"""
		armadura = parte.get_armadura()
		escudo = parte.get_escudo()
		peso = parte.get_peso()	
		energia = parte.get_energia()
		tipo = parte.get_tipo_parte()
		if tipo != "Arma":
			cantidad_armas = len(parte.get_armamento())
			velocidad = parte.get_velocidad()
			daño = 0
			hits = 0
			precision = 0
			tiempo_recarga = 0
		else:
			cantidad_armas = 0
			velocidad = 0
			daño = parte.get_daño()
			hits = parte.get_hits()
			precision = parte.get_precision()
			tiempo_recarga = parte.get_tiempo_recarga()	
		return armadura,escudo,peso,energia,tipo,cantidad_armas,velocidad,daño,hits,precision,tiempo_recarga

	def _elegir_mejor_parte(self, partes):
		"""
		   Compara una lista de partes y devuelve la mejor opción, para elegir la mejor opción,
		   se dividen los atributos de las partes por sus correspondientes promedios, obtenidos a partir de los ejemplos de las partes
		   luego se suman los atributos. 
		"""
		n = 0
		promedios = self._obtener_promedios()
		for parte in partes: 
			armadura,escudo,peso,energia,tipo,cantidad_armas,velocidad,daño,hits,precision,tiempo_recarga = self._obtener_atributos(parte)	
			calidad = (velocidad/promedios[0]) + (peso/promedios[1]) + (armadura/promedios[2]) + (escudo/promedios[3]) + (energia/promedios[4]) \
			+ (cantidad_armas/promedios[5]) + (daño/promedios[6]) + (hits/promedios[7]) + (precision/promedios[8]) - (tiempo_recarga/promedios[9])
			if n == 0 or calidad > calidad_comparacion:
				n += 1
				mejor_parte = parte
				calidad_comparacion = calidad      
		return mejor_parte  

	def elegir_combinacion(self, partes_reservadas):
		"""Dada una lista con partes previamente reservadas, devuelve una lista con las 
		partes a utilizar para construir el Gunpla. Este metodo se utiliza para elegir las 
		partes que se van a utilizar en el modelo de entre las que se reservaron previamente 
		para cada piloto."""
		partes_utilizar = []
		partes_disponibles = {}
		for parte in partes_reservadas:
			partes_disponibles[parte.get_tipo_parte()] = partes_disponibles.get(parte.get_tipo_parte(),[]) + [parte]
		for tipo in partes_disponibles:
			partes = list(partes_disponibles[tipo])
			mejor_parte = self._elegir_mejor_parte(partes)
			partes_utilizar.append(mejor_parte)
		return partes_utilizar


	def elegir_oponente(self, oponentes):
		"""Devuelve el índice del Gunpla al cual se decide atacar de la lista de oponentes 
		pasada, el mejor oponente al que se debe atacar, se calcula dividiendo los atributos del oponente por sus respectivos promedios
		obtenidos de la lista de gunplas dada, aquel cuyo calculo sea menor, será el mejor gunpla a atacar
		"""
		n = 0
		promedio_vida = 15722
		promedio_armadura = 1852
		promedio_escudo = 52
		promedio_mov = 0.516
		for oponente in oponentes:
			vida = oponente.get_energia_restante()
			armadura = oponente.get_armadura()
			escudo = oponente.get_escudo()
			movilidad = oponente.get_movilidad()
			calculo = (vida/promedio_vida) + (armadura/promedio_armadura) + (escudo/promedio_escudo) + (movilidad/promedio_mov)
			if n == 0 or calculo < mejor_calculo:
				n += 1
				mejor_calculo = calculo
				mejor_eleccion = oponente
		return oponentes.index(mejor_eleccion)
	  
	def _obtener_atributos_arma(self,arma,armadura,escudo):
		"""Devuelve algunos atributos del arma, y ciertas condiciones en relacion a las distintas variables"""
		daño = arma.get_daño()
		hits = arma.get_hits()
		precision = arma.get_precision()
		tiempo_recarga = arma.get_tiempo_recarga()
		municion = arma.get_tipo_municion()
		tipo = arma.get_tipo()
		if (armadura < escudo and municion == "FISICA") or (armadura > escudo and municion == "LASER"):
			resistencia = 0.5
		elif (armadura > escudo and municion == "FISICA") or (armadura < escudo and municion == "LASER"):
			resistencia = 1
		else:
			resistencia = 0
		if tipo == "MELEE":
			coontrataque = 0
			combinacion = 0.4
		else:
			coontrataque = 0.5
			combinacion = 0.25	
		return 	daño,hits,precision,tiempo_recarga,municion,tipo,resistencia,coontrataque,combinacion		

	def elegir_arma(self, oponente):
		"""Devuelve el arma con la cual se decide atacar al oponente, el arma elegida se obtiene a partir de dividir los atributos del arma 
		por sus respectivos promedios, obtenidos a partir de los ejemplos de armas dados, si el piloto no tiene ningun arma disponible, devuelve None"""
		armadura = oponente.get_armadura()
		escudo = oponente.get_escudo()
		n = 0
		promedio_daño = 2475
		promedio_hits = 2.78
		promedio_precision = 81
		promedio_tiempo = 3.16
		mejor_arma = None 
		armas = self.get_gunpla().get_armamento()
		for arma in armas:
			if not arma.esta_lista():
				continue
			daño,hits,precision,tiempo_recarga,municion,tipo,resistencia,coontrataque,combinacion = self._obtener_atributos_arma(arma,armadura,escudo)
			calidad = (daño/promedio_daño) + (hits/promedio_hits) + (precision/promedio_precision) - (tiempo_recarga/promedio_tiempo) - \
			resistencia + coontrataque + combinacion
			if n == 0 or calidad > calidad_comparacion:
				n += 1
				mejor_arma = arma
				calidad_comparacion = calidad              
		return mejor_arma