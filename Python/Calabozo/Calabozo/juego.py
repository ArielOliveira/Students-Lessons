import pygame, sys, random, math
from pygame.locals import *
from mapa import Mapa, distancia, VACIO, MURO
import color_mapa

LADO_CELDA  = 10
ANCHO_MAPA  = 50
ALTO_MAPA = 50

DONE = 0
FAILED = 1
IN_EXECUTION = 2

ATCK_DIST = 1

pygame.init()

from enum import Enum

class Estado(Enum):
    PATRULLAR = 1
    BUSCAR = 2
    RASTREAR = 3
    LUCHA = 4
    HUIR = 5
    MUERTO = 6

# Make sure to check the Monstruo initial values
class Monstruo():
    def __init__(self, posicion):
        self.posicion = posicion
        self.movimientos = []
        self.estado = Estado.PATRULLAR
        self.lentitud = 5
        self.vida = 10
        self.armadura = 2
        self.fuerza = 8
        self.turno = 0

        self.execution = {
            Estado.PATRULLAR: IN_EXECUTION,
            Estado.BUSCAR: DONE,
            Estado.RASTREAR: DONE,
            Estado.HUIR: DONE,
            Estado.LUCHA: DONE
        }

        self.switcher = {
            Estado.PATRULLAR: self.patrullar,
            Estado.BUSCAR: self.buscar,
            Estado.RASTREAR: self.rastrear,
            Estado.HUIR: self.huir,
            Estado.LUCHA: self.luchar
        }

        self.canSee = False
        self.canSmell = False
        self.max_dist_olfato = 10
        self.max_dist_vista = 20

    def oler(self, other):
        if (distancia(self.posicion, other.posicion) < self.max_dist_olfato): 
            if (not self.rastrear(other)):    
                return False
            return True
        else:
            return False

    def ver(self, other):
        if (distancia(self.posicion, other.posicion) < self.max_dist_vista):
            if (not self.straight_path(other)):
                return False
            return True
        else:
            return False

    def percibir(self, other):
        self.canSmell = self.oler(other)
        self.canSee = self.ver(other)
    
    def straight_path(self, other):
        straightPath = []
        straightPath = mapa.buscar_camino_recto(self.posicion, other.posicion)
        if (not straightPath):
            list()       
        else:
            return straightPath

    # Might be different than the original
    def buscar(self, other):
        if (self.execution[self.estado] == IN_EXECUTION):
            if (distancia(self.posicion, other.posicion) >= ATCK_DIST and len(self.movimientos) == 0):
                if (self.canSee):
                    self.movimientos = self.straight_path(other)
                elif (self.canSmell):
                    self.movimientos = self.rastrear(other)
                else:
                    self.execution[self.estado] = DONE
                    self.estado = Estado.PATRULLAR
                    self.execution[self.estado] = IN_EXECUTION
            elif (distancia(self.posicion, other.posicion) <= ATCK_DIST):
                self.estado = Estado.LUCHA
            elif (len(self.movimientos) > 0):
                self.posicion = self.movimientos.pop(0)
                if (len(self.movimientos) == 0):
                    self.execution[self.estado] = DONE
                    self.estado = Estado.PATRULLAR
                    self.execution[self.estado] = IN_EXECUTION


    def rastrear(self, other):
        trackToPlayer = mapa.AStarSearch(self.posicion, other.posicion)
        if (not trackToPlayer):
            return list()
        else:
            return trackToPlayer

    # Changed from the original
    def huir(self, other):
        if (self.execution[self.estado] == IN_EXECUTION):
            #Added a check to see whether the enemy can see or smell the player
            #before trying to escape
            if (len(self.movimientos) == 0 and (self.canSee or self.canSmell)):
                escape_route = list()
                distance = distancia(self.posicion, other.posicion)
                new_distance = 0

                while (not escape_route and new_distance <= distance):
                    a = random.random() * 2 * 3.14
                    r = (random.random() * 20) + 10
                    escape = ((int)(r * math.cos(a)), (int)(r * math.sin(a)))

                    escape_route = mapa.AStarSearch(self.posicion, escape)
                    if (escape_route):
                        new_distance = distancia(escape_route[len(escape_route)-1], other.posicion)                    
                self.movimientos = escape_route
            # Slight changes from the original
            else:
                if (len(self.movimientos) > 0):
                    self.posicion = self.movimientos.pop(0)
                if (len(self.movimientos) == 0):
                    self.execution[self.estado] = DONE
                    self.estado = Estado.PATRULLAR
                    self.execution[self.estado] = IN_EXECUTION

    # Might have been changed from the original
    def patrullar(self, other):
        # From here ###########################################
        distance = distancia(self.posicion, other.posicion)
        if (distance <= self.max_dist_vista and other.vida > 0 and self.execution[self.estado] != IN_EXECUTION):
            if (self.vida <= 4):
                self.estado = Estado.HUIR
            else:
                self.estado = Estado.BUSCAR
            self.execution[self.estado] = IN_EXECUTION
        # To here ##############################################
        else:
            x = random.randint(0, 10)
            y = random.randint(0, 10)

            newPosition = (0, 0)
            moveX = 0
            moveY = 0

            chanceToMoveTowardsX = 5
            chanceToMoveTowardsY = 5

            if (x > chanceToMoveTowardsX):
                if (random.randint(0, 10) > chanceToMoveTowardsX):
                    moveX = 1
                else:
                    moveX = -1
            elif (y > chanceToMoveTowardsY):
                if (random.randint(0, 10) > chanceToMoveTowardsY):
                    moveY = 1
                else:
                    moveY = -1

            newPosition = (moveX + self.posicion[0], moveY + self.posicion[1])
            if (mapa.esta_dentro(newPosition) and mapa.isOpen(newPosition)):
                self.posicion = newPosition
            self.execution[self.estado] = DONE

    def atacar(self, other):
        other.defender(random.randint(0, self.fuerza))   

    def defender(self, ataque):
         if (ataque > self.armadura):
            self.vida -= ataque - self.armadura
         if (self.vida <= 0):
            self.estado = Estado.MUERTO  
         elif (self.vida <= 4):
            self.estado = Estado.HUIR
            self.execution[self.estado] = IN_EXECUTION

    # Changed here
    def luchar(self, other):
        # Only goes into 'luchar' state if the player is still alive
        if (other.vida > 0):
            if (self.vida > 4 and distancia(self.posicion, other.posicion) <= ATCK_DIST):
                self.atacar(other)
            elif (distancia(self.posicion, other.posicion) > ATCK_DIST):
                self.estado = Estado.BUSCAR
        # Otherwise keeps patrolling
        else:
            self.execution[self.estado] = DONE
            self.estado = Estado.PATRULLAR
            self.execution[self.estado] = IN_EXECUTION


    def actualizar(self, other):
        if (self.estado != Estado.MUERTO):
            self.percibir(other)
            self.switcher[self.estado](other)

class Jugador():
    def __init__(self, posicion):
        self.posicion = posicion
        self.movimientos = []
        self.vida = 10
        self.armadura = 5
        self.fuerza = 10

    # Added this function to end the game
    def endGame(self):
        pygame.time.wait(80)
        pygame.quit()
        sys.exit()

    def atacar(self, other):
        other.defender(random.randint(0, self.fuerza))

    def defender(self, ataque):
        if(ataque > self.armadura):
            self.vida -= (ataque-self.armadura)

    def actualizar(self, events):
        for event in events:
            if event.type == QUIT:
                self.endGame()

            # Added this check
            if (self.vida <= 0):
                print("You died")
                self.endGame()
            
            if event.type == KEYDOWN:
                newPos = list(self.posicion)
                if event.key == K_RIGHT :
                    newPos[1] += 1
                if event.key == K_LEFT :
                    newPos[1] -= 1
                if event.key == K_UP :
                    newPos[0] -= 1
                if event.key == K_DOWN :
                    newPos[0] += 1
                newPos = tuple(newPos)

                if mapa.esta_dentro(newPos) and (mapa[newPos] == VACIO):
                    posiciones = []
                    self.posicion = newPos
                if event.key == K_SPACE:
                    for monstruo in monstruos:
                        if(distancia(monstruo.posicion,self.posicion)<= ATCK_DIST):
                            self.atacar(monstruo)

            elif event.type == MOUSEBUTTONDOWN:
                destination = (event.pos[1] // LADO_CELDA, event.pos[0] // LADO_CELDA)
                mapM = (event.pos[0] // LADO_CELDA, event.pos[1] // LADO_CELDA)
                self.movimientos = mapa.AStarSearch(self.posicion, destination)

        if (len(self.movimientos) > 0):
            self.posicion = self.movimientos.pop(0)



mapa = Mapa(ANCHO_MAPA,ALTO_MAPA,LADO_CELDA)
# Added this function to mapa
mapa.generate()

jugador = Jugador((0,0))
monstruos = [Monstruo((0,ANCHO_MAPA-1)), Monstruo((ALTO_MAPA-1,ANCHO_MAPA-1)), Monstruo((ALTO_MAPA-1,0))]

while True:
    mapa.mostrar_mapa()
    if (jugador.vida > 0):
        mapa.mostrar_celda(jugador.posicion, color_mapa.ROJO)
    else:
        # Problem in this line
        # If the player dies it will crash
        mapa.mostrar_celda(jugador.posicion, color_mapa.BLANCO)

    jugador.actualizar(pygame.event.get())
    noMontruosVivos = True
    for monstruo in monstruos:
        # Checking if there is a monster still alive
        if (monstruo.vida > 0):
            noMontruosVivos = False
        monstruo.actualizar(jugador)
        color = color_mapa.AZUL
        if(monstruo.estado == Estado.MUERTO):
            color = color_mapa.VERDE
        mapa.mostrar_celda(monstruo.posicion,color)
    
    pygame.display.update()
    pygame.time.wait(100)

    # Added this check
    # If all monsters are dead, game ends
    if (noMontruosVivos):
        print("You won")
        jugador.endGame()

