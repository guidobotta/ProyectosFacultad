from random import randint,choice
import operator
from pila import Pila
from cola import Cola
from lista_circular import Lista_Circular
from esqueleto import Esqueleto
from arma import Arma
from arma import MELEE, RANGO, FISICA, LASER, HADRON, TIPOS_ARMAS, TIPOS_MUNICION, ARMAS_RANGO, ARMAS_MELEE
from parte import Parte
from parte import TIPOS_PARTES, PARTES_COMPATIBLES
from gunpla import Gunpla
from piloto import Piloto

def crear_equipos(cantidad_equipos):
	"""Crea los equipos vacios en los que se pondrán los pilotos, recibe la cantidad de equipos a crear
	   Pre: cantidad debe ser mayor o igual a 2"""
	equipos = []
	for cant in range(cantidad_equipos):
		equipo = []
		equipos.append(equipo)
	return equipos

def crear_pilotos(cantidad_pilotos,cantidad_equipos):
	"""Crea los pilotos y devuelve los equipos, recibe la cantidad de pilotos que se quiere crear y la cantidad de equipos en los que se los distribuirá"""
	equipos = crear_equipos(cantidad_equipos)
	for x in range(cantidad_pilotos):
		piloto = Piloto()
		for i in range(len(equipos)):
			if x % len(equipos) == i:
				equipos[i].append(piloto)
	return equipos

def crear_esqueletos(cantidad_esqueletos):
	"""Crea una lista con los esqueletos, recibe la cantidad de esqueletos que se quieren crear"""
	esqueletos = []
	for x in range(cantidad_esqueletos):
		velocidad = randint(5,25)
		energia = randint(50,100)
		movilidad = randint(100,200)
		slots = randint(2,5)
		esqueleto = Esqueleto(velocidad,energia,movilidad,slots)
		esqueletos.append(esqueleto)
	return esqueletos			

def elegir_esqueleto(esqueletos_disponibles, equipos):
	"""Dada una lista de esqueletos y los equipos, elige los esqueletos para cada piloto.
	Devuelve un diccionario de la forma { piloto1 : {"esqueleto": esqueleto}, ... }"""
	esqueletos_elegidos = {}
	for equipo in equipos:
		for piloto in equipo:
			indice = piloto.elegir_esqueleto(esqueletos_disponibles)
			esqueleto_elegido = esqueletos_disponibles[indice]
			esqueletos_elegidos[piloto] = {"esqueleto" : esqueleto_elegido}
	return esqueletos_elegidos

def generar_armas(cantidad_armas):
	"""Genera armas y se las asigna a una pila, recibe la cantidad de armas que se generaran"""
	armas = Pila()
	for x in range(cantidad_armas):
		peso = randint(100,300)
		armadura = randint(-5,50)
		escudo = randint(-10,20)
		velocidad = randint(-5,25)
		energia = randint(-70,100)
		tipo_de_municion, tipo_de_arma, clase_de_arma = seleccionar_municion_tipo_clase()
		daño = randint(1000,3000)
		hits = randint(2,4)
		precision = randint(70,90)
		tiempo_de_recarga = randint(0,5)
		arma = Arma(peso, armadura, escudo, velocidad, energia, tipo_de_municion, tipo_de_arma, clase_de_arma, daño, hits, precision, tiempo_de_recarga)
		armas.apilar(arma)
	return armas

def seleccionar_municion_tipo_clase():
	"""Devuelve el tipo de municion, el tipo de arma y la clase de arma (en ese orden) al azar."""
	tipo_de_municion = choice(TIPOS_MUNICION)
	tipo_de_arma = choice(list(TIPOS_ARMAS))
	clase_de_arma = choice(list(TIPOS_ARMAS[tipo_de_arma]))
	return tipo_de_municion, tipo_de_arma, clase_de_arma

def generar_partes(cantidad_partes):
	"""Genera partes y se las asigna a distintas pilas segun su tipo, recibe la cantidad de partes que se generaran.
	Devuelve una lista de pilas de distintos tipos de partes."""
	partes = {}
	for x in range(cantidad_partes):
		peso = randint(100,300)
		armadura = randint(-10,80)
		escudo = randint(-10,90)
		velocidad = randint(-10,25)
		energia = randint(-5,80)
		tipo_de_parte, armamento = seleccionar_tipo_armamento()
		parte = Parte(peso, armadura, escudo, velocidad, energia, armamento, tipo_de_parte)
		partes[tipo_de_parte] = partes.get(tipo_de_parte, []) + [parte]
	pilas_partes = []
	for parte in partes.values():
		pila = Pila()
		for part in parte:
			pila.apilar(part)
		pilas_partes.append(pila)		
	return pilas_partes
  
def seleccionar_tipo_armamento():
	"Devuelve el tipo de parte y el armamento (en ese orden) al azar."
	tipo_de_parte = choice(TIPOS_PARTES)
	armamento = []
	if tipo_de_parte in [PARTES_COMPATIBLES]:
		cantidad_armas = randint(0,3)
		armas = generar_armas(cantidad_armas)
		while not armas.esta_vacia():
			armamento.append(armas.desapilar())
	return tipo_de_parte, armamento
  
def crear_ronda(equipos):
	"""Recibe los equipos. Devuelve la disposición de jugadores para la elección de armas y partes 
	como una ronda"""
	ronda = Lista_Circular()
	_equipos = []
	for equipo in equipos:
		for piloto in equipo:
			_equipos.append(piloto)	
	while _equipos:
		piloto = choice(_equipos)
		ronda.append(piloto)
		_equipos.remove(piloto)
	return ronda

def elegir_armas_partes(ronda, pilas_partes, esqueletos_elegidos):
	"""Recibe la ronda de pilotos, las pilas de armas y partes y el diccionario que contiene los pilotos y su esqueleto.
	Devuelve un diccionario de la forma {piloto1 : {"esqueleto" = esqueleto, "partes" = [partes]}, ...} """
	armas_partes_elegidas = esqueletos_elegidos
	piloto = ronda.get_primero()
	while len(pilas_partes):
		pila_elegida = choice(pilas_partes)
		parte_arma = pila_elegida.desapilar()
		armas_partes_elegidas[piloto]["partes"] = armas_partes_elegidas[piloto].get("partes",[]) + [parte_arma]
		if pila_elegida.esta_vacia():
			pilas_partes.remove(pila_elegida)
		piloto = ronda.proximo()
	return armas_partes_elegidas

def reasignar_armas_partes(esquel_armas_partes):
	"""Recibe un diccionario de la forma {piloto1 : {"esqueleto" : esqueleto, "partes" : [partes]}, ...}
	Reasigna las armas y partes a los pilotos, y les asigna sus gunplas"""
	#Recorre las claves que son los pilotos
	for piloto in esquel_armas_partes:
		partes = []
		armas = []
		#Recorre las armas y partes del piloto
		for parte_arma in esquel_armas_partes[piloto]["partes"]:
			if parte_arma.get_tipo_parte() == "Arma":
				armas.append(parte_arma)
			else:
				partes.append(parte_arma)		
		partes_finales = piloto.elegir_combinacion(partes)		
		esqueleto = esquel_armas_partes[piloto]["esqueleto"]
		asignar_gunplas(piloto,esqueleto,partes_finales,armas)
		
def asignar_gunplas(piloto,esqueleto,partes,armas):
	"""Asigna un gunpla al piloto"""
	peso = 0
	escudo = 0
	armadura = 0
	velocidad = 0
	energia = 0
	armamento = []	
	for arma in armas:
		peso += arma.get_peso()
		armadura += arma.get_armadura()
		escudo += arma.get_escudo()
		energia += arma.get_energia()
		if len(armamento) < esqueleto.get_cantidad_slots():
			armamento += [arma]
	for parte in partes:
		peso += parte.get_peso()
		escudo += parte.get_escudo()
		armadura += parte.get_armadura()
		velocidad += parte.get_velocidad()
		energia += parte.get_energia()
		armamento += parte.get_armamento()
		for arma in parte.get_armamento():
			peso += arma.get_peso()
			armadura += arma.get_armadura()
			escudo += arma.get_escudo()
			energia += arma.get_energia()
			armamento += arma				
	velocidad += esqueleto.get_velocidad()
	energia += esqueleto.get_energia()
	base = esqueleto.get_movilidad()
	movilidad = (base - peso / 2 + velocidad * 3) / base
	maximo = 1
	minimo = 0 
	if movilidad > maximo:
		movilidad = maximo
	elif movilidad < minimo:
		movilidad = minimo
	energia_restante = energia
	gunpla = Gunpla(peso,armadura,escudo,velocidad,energia,energia_restante,movilidad,armamento)
	piloto.set_gunpla(gunpla)

def crear_cola_turnos(equipos):
	"""Crea una cola que representa los turnos, el orden depende de la velocidad del gunpla"""
	pilotos_velocidades = []
	for equipo in equipos:
		for piloto in equipo:
			velocidad = piloto.get_gunpla().get_velocidad()
			pilotos_velocidades.append((piloto,velocidad))
	pilotos_velocidades.sort(key = operator.itemgetter(1), reverse = True) 	
	turnos = Cola()
	for piloto in pilotos_velocidades:
		turnos.encolar(piloto[0])
	return turnos

def asignar_nombres(equipos):
	nombres = {}
	i=0
	for equipo in equipos:
		for piloto in equipo:
			nombres[piloto] = "Piloto {}".format(i)
			i+=1
	return nombres	

def revisar_disponibilidad_armas(armas_no_disponibles):
	"""Recibe las armas no disponibles, y le quita una unidad de tiempo faltante a estas, si algun arma queda con un tiempo faltante igual a 0, esta es quitada de la lista"""
	for weapons in armas_no_disponibles:
		weapons[1] -= 1
		if weapons[1] == 0:
			weapons[0].disponible = True
			armas_no_disponibles.remove(weapons)

def esta_vivo(equipos,piloto):
	"""Se fija si el piloto no fue eliminado de su equipo"""
	for equipo in equipos:
		if piloto in equipo:
			return True
	return False	

def elegir_oponentes_atacar(equipos,piloto,nombres):
	"""Elije el oponente a atacar, devuelve la lista de oponentes, el oponente a atacar y el gunpla enemigo"""				
	oponentes = choice(equipos)
	while piloto in oponentes:
		oponentes = choice(equipos)
	gunplas_oponentes = []
	for oponente in oponentes:
		gunplas_oponentes.append(oponente.get_gunpla())	
	indice_oponente_atacar = piloto.elegir_oponente(gunplas_oponentes)
	oponente_atacar = oponentes[indice_oponente_atacar]
	print("El oponente a atacar es {}".format(nombres[oponente_atacar]))
	gunpla_enemigo = oponente_atacar.get_gunpla()
	return oponentes, oponente_atacar , gunpla_enemigo					

def nuevos_turnos(daño,turnos,oponente_atacar,nombres,gunpla_enemigo,piloto):
	"""Según las condiciones necesarias, encola nuevos turnos a quien corresponda"""
	if daño == 0:
		turnos.encolar(oponente_atacar)
		print("Turno extra para {}".format(nombres[oponente_atacar]))
	porcentaje = 5/100	
	if gunpla_enemigo.get_energia_restante() < 0 and \
	abs(gunpla_enemigo.get_energia_restante()) > (gunpla_enemigo.get_energia() *porcentaje):
		turnos.encolar(piloto)
		print("Turno extra para {}".format(nombres[piloto]))

def coontrataque(arma,gunpla_enemigo,oponente_atacar,piloto):
	"""Evalúa si se debe realizar un coontrataque y en caso de ser positivo lo realiza"""
	if arma.get_tipo() == "MELEE" and gunpla_enemigo.get_energia_restante() > 0:
		arma_oponente = oponente_atacar.elegir_arma(piloto.get_gunpla())
		if arma_oponente == None:
			print("El oponente no tiene armas disponibles, por lo que no puede coontratacar")
		else:
			daño_coontrataque = calculo_de_daño(gunpla_enemigo,arma_oponente,piloto.get_gunpla(),True)
			print("El oponente coontrataco, con {} e inflingió {} de daño".format(arma_oponente.get_clase(),daño_coontrataque))	

def eliminar_pilotos(gunpla_enemigo,oponentes,nombres,oponente_atacar,equipos,piloto,turnos):
	"""Se fija si algún gunpla fue destruido, y elimina al piloto correspondiente de su equipo, si el equipo se quedó sin pilotos también lo elimina"""
	if gunpla_enemigo.get_energia_restante() < 0:
		oponentes.remove(oponente_atacar)
		print("{} fue destruido".format(nombres[oponente_atacar]))
		if len(oponentes)==0:
			equipos.remove(oponentes)
			print("El equipo de {} se quedó sin jugadores".format(nombres[oponente_atacar]))
	if piloto.get_gunpla().get_energia_restante() < 0:
		for equipo in equipos:
			if piloto in equipo:
				equipo.remove(piloto)
				print("{} fue destruido".format(nombres[piloto]))
				if len(equipo) == 0:
					equipos.remove(equipo)
					print("El equipo de {} se quedó sin jugadores".format(nombres[piloto]))
				break
	else:
		turnos.encolar(piloto)			

def ciclo(turnos,equipos,nombres):
	"""Ejecuta el ciclo del juego"""
	armas_no_disponibles = []
	while len(equipos) > 1:
		revisar_disponibilidad_armas(armas_no_disponibles)
		piloto = turnos.desencolar()
		if not esta_vivo(equipos,piloto):
			continue
		print("Hay {} equipos".format(len(equipos)))
		print("Comienza nuevo turno\n")	
		print("Es el turno de {}".format(nombres[piloto]))
		oponentes, oponente_atacar , gunpla_enemigo = elegir_oponentes_atacar(equipos,piloto,nombres)
		arma = piloto.elegir_arma(gunpla_enemigo)
		if arma == None:
			print("El piloto no tiene armas disponibles, por lo que pasa su turno")
			print()
			turnos.encolar(piloto)
			continue
		print("Se está atacando con {}".format(arma.get_clase()))
		daño =  calculo_de_daño(piloto.get_gunpla(),arma,gunpla_enemigo,False)
		print("El daño inflingido es {}".format(daño))
		arma.disponible = False
		armas_no_disponibles.append([arma,arma.get_tiempo_recarga()])
		nuevos_turnos(daño,turnos,oponente_atacar,nombres,gunpla_enemigo,piloto)
		coontrataque(arma,gunpla_enemigo,oponente_atacar,piloto)
		eliminar_pilotos(gunpla_enemigo,oponentes,nombres,oponente_atacar,equipos,piloto,turnos)			
		print("Turno terminado")
		print()	 
	print("Partida terminada, gracias por jugar")
	print("El equipo de {} es el ganador".format(nombres[equipos[0][0]]))
	
def generar_daño(arma):
	"""Genera el daño realizado en el ataque"""
	daño = 0
	precision = arma.get_precision()
	for veces in range(arma.get_hits()):
		probabilidad = randint(1,100)
		if probabilidad <= precision:
			daño += arma.get_daño()
	probabilidad = randint(1,100)
	porcentaje = 0.25 
	aumento = 1.5		
	if probabilidad <= precision * porcentaje:
		daño *= aumento
	return daño	

def combinacion_de_armas(atacante,arma):
	"""Realiza la combinación de armas, devuelve el arma nueva"""
	i = 0
	while True:
		arma_nueva = choice(atacante.get_armamento())
		if i >	len(atacante.get_armamento())*2:
			arma_nueva = None
			break
		if arma_nueva == arma:
			i+=1
			continue
		if arma_nueva.get_tipo() == arma.get_tipo() and arma_nueva.get_clase() == arma.get_clase() \
		and arma_nueva.get_tipo_municion() == arma.get_tipo_municion() and arma_nueva.esta_lista():
			break
		i += 1
	return arma_nueva	

def reduccion_de_daño(arma,daño,defensor):
	"""Devuelve la reducción de daño correspondiente"""
	if arma.get_tipo_municion() == "Fisica":
		daño_reducido = daño - defensor.get_armadura()
	elif arma.get_tipo_municion() == "Laser":
		daño_reducido = daño - daño* defensor.get_escudo()
	else:
		daño_reducido = 0
	return daño_reducido	

def calculo_de_daño(atacante,arma,defensor,coontrataque):
	"""Calcula el daño que debe ser recibido, recibe el gunpla atacante, el arma con la que ataca, el gunpla defensor y si es un coontrataque"""
	if arma == None:
		return 0
	daño = generar_daño(arma)
	if not coontrataque:
		arma_nueva = combinacion_de_armas(atacante,arma)
		if arma.get_tipo() == "MELEE":
			porcentaje = 40
			probabilidad = randint(1,100)
			if probabilidad <= porcentaje:
				daño += calculo_de_daño(atacante,arma_nueva,defensor,False)
		else:
			porcentaje = 25
			probabilidad = randint(1,100)
			if probabilidad <= porcentaje:
				daño += calculo_de_daño(atacante,arma_nueva,defensor,False)
	movilidad = defensor.get_movilidad()
	probabilidad = randint(1,100)
	porcentaje_mov = 80     
	if probabilidad <= movilidad * porcentaje_mov:       
		return 0
	daño_reducido = reduccion_de_daño(arma,daño,defensor)
	daño -= daño_reducido
	defensor.energia_restante -= daño
	return daño		 

				
def main():
	""""""
	#Creación Equipos
	cantidad_equipos = randint(2,4)
	cantidad_pilotos = cantidad_equipos * randint(2,4)
	equipos = crear_pilotos(cantidad_pilotos, cantidad_equipos)
	#Creación y elección Esqueletos
	cantidad_esqueletos = randint(cantidad_pilotos, cantidad_pilotos*2)
	esqueletos_disponibles = crear_esqueletos(cantidad_esqueletos)
	esqueletos_elegidos = elegir_esqueleto(esqueletos_disponibles, equipos)
	#Creación armas y partes
	cantidad_armas = randint(cantidad_pilotos*2,cantidad_pilotos*3)	
	cantidad_partes = randint(cantidad_pilotos*2,cantidad_pilotos*3)
	armas_partes_disponibles = [generar_armas(cantidad_armas)] + generar_partes(cantidad_partes)
	#Creación Ronda al azar
	ronda = crear_ronda(equipos)
	#Elección y Reelección de armas y partes
	esqueletos_armas_partes_elegidos = elegir_armas_partes(ronda, armas_partes_disponibles, esqueletos_elegidos)
	#Asignar gunplas / Reasignar armas,partes
	reasignar_armas_partes(esqueletos_armas_partes_elegidos)
	#Crear cola de turnos por velocidad
	turnos = crear_cola_turnos(equipos)
	#Nombres
	nombres = asignar_nombres(equipos)
	#Ciclo del juego
	ciclo(turnos,equipos,nombres)
		
main()