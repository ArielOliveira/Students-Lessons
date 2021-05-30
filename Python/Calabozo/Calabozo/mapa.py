import pygame
import random
import bisect
import color_mapa
#import juego

VACIO  = 0
MURO = 1
VERDE = 2

colores_mapa =   {
                VACIO: color_mapa.NEGRO,
                MURO: color_mapa.MARRON,
                VERDE: color_mapa.VERDE,
            }

#JUGADOR = pygame.image.load('jugador.png')
class Nodo:
    def __init__(self, posicion, costo, precursor):
        self.posicion=posicion
        self.costo=costo
        self.precursor=precursor
    
    def next(self):
            # Devuelve uno a uno los elementos de la list
            if self.precursor == None:
                 raise StopIteration("No hay más elementos en la lista")
    
    def getNode(self):
        return self.head




# I believe your class nodo is lacking some information, 
# gonna reimplement it here in an attempt to see if there is 
# really a need to have all the variables I am going to use
class Cell:
    def __init__(self, g, h, f, parent):
        self.g = g
        self.h = h
        self.f = f
        self.parent = parent
    
class Pair:
    def __init__(self, f, position):
        self.f = f
        self.position = position
    def __getitem__(self, val):
        return self.cell
    def __lt__(self, other):
        return self.f < other.f
    def __gt__(self, other):
        return self.f > other.f
    def __eq__(self, other):
        return self.f == other.f
        
def distancia(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def calcularMenorCoste(opened):
    minimoCosto=10000
    posicionMenor=None
     
    for value in opened.values:
        if value.costo < minimoCosto:
            minimoCosto=value.costo
            posicionMenor = value.posicion

    auxiliar=opened[posicionMenor]
    del opened[posicionMenor]
    return auxiliar


class Mapa:
    def __init__(self, ancho_mapa, alto_mapa, lado_celda):
        self.ancho_mapa = ancho_mapa
        self.alto_mapa = alto_mapa
        self.lado_celda = lado_celda
        self.mapa = {(x, y) : VACIO for x in range(self.ancho_mapa) for y in range(self.alto_mapa)}
        self.pantalla = pygame.display.set_mode((self.ancho_mapa * self.lado_celda, self.alto_mapa * self.lado_celda))

    # Added this function here
    def generate(self):
        # While AStarSearch can't find a path from the origin to all corners
        while (True):
            self.generar_aleatorio()
            self.generar_automata()

            self.mostrar_mapa()
            pygame.display.update()

            # AStarSearch returns an empty list if it fails
            if (not self.AStarSearch((0, 0), (self.alto_mapa-1, self.ancho_mapa-1))):
                continue
            elif (not self.AStarSearch((0, 0), (0, self.ancho_mapa-1))):
                continue
            elif (not self.AStarSearch((0, 0), (self.alto_mapa-1, 0))):
                continue
            break

    def generar_aleatorio(self):
         for x in range(self.ancho_mapa):
              for y in range(self.alto_mapa):
                  val=random.randrange(2)
                  self.mapa[(x,0)]=VACIO
                  self.mapa[(0,y)]=VACIO
                  #print(val)
                  if val==0:
                      self.mapa[(x,y)]=VACIO
                  if val==1:
                      self.mapa[(x,y)]=MURO
         
         #print("aqui estoy probando.............")             
         #print(self.mapa[(1,1)])

    def generar_automata(self):
        #Se crea un arreglo que es copia del mapa
        mapa_copia = dict(self.mapa)
        #print("..............................................Aqui entra sin problemas............................")
        #conocer los vecinos y saber si estan vacios o muro 1 o 0 
        for aux in range(4):
            for x in range(self.ancho_mapa):
                  for y in range(self.alto_mapa):
                       vecinosActuales=self.vecinos([x,y])
                       vecinosAbiertos = self.abiertos([x,y])
                       auxMuro=0
                       auxVacio=0
                       for a,b in vecinosActuales:
                           #print(".................esto trae el mapa en la poscicion de los vecinos")
                           if self.mapa[(a,b)] ==MURO:
                                auxMuro+=1    
                           elif self.mapa[(a,b)] ==VACIO:
                               auxVacio+=1       
                       if auxMuro>auxVacio:
                            mapa_copia[(x,y)]=MURO
                       elif auxMuro < auxVacio:
                             mapa_copia[(x,y)]=VACIO
                       elif auxMuro == auxVacio :
                            mapa_copia[(x,y)]=self.mapa[(x,y)]
            self.mapa=mapa_copia               
      
      
    def __getitem__(self,celda):
        return self.mapa[celda]

    def esta_dentro(self, celda):
        (x, y) = celda
        return (x >= 0) and (x < self.ancho_mapa) and (y >= 0) and (y < self.alto_mapa)

    def isOpen(self, celda):
        return self.mapa[celda] == VACIO

    def vecinos(self, celda):
        (x,y) = celda
        vecinos = []
        #para sacar 8 vecinos
        for i in range(-1,2,1):
            for j in range(-1,2,1):
                neighbour_x= celda[0]+i
                neighbour_y = celda[1]+j
               
                #sino es borde y no es centro añadir a la lista de vecinos
                if (neighbour_x >= 0 and neighbour_y >= 0 and neighbour_x < self.ancho_mapa and neighbour_y < self.alto_mapa):
                    vecinos.append((neighbour_x,neighbour_y))
         
        #eliminar la celda original porque no es un vecino
        iter=0
        for a,b in vecinos:
            if a== celda[0] and b == celda[1]:
                vecinos.pop(iter)
            iter+=1
        #print(vecinos)

        return vecinos

    def vecinos4(self, celda):
         (x,y) = celda
         vec4 = []
         for new_position in [(0, -1), (0, 1), (-1, 0), (1, 0)]: 
             new_position = (x+ new_position[0], y + new_position[1])
             if self.esta_dentro(new_position):
                 if self.mapa[new_position] == VACIO:
                    vec4.append(new_position)
             # Adjacent squares
             #Obtener posicion
            
             #lista con las posiciones
         
         return vec4


    def abiertos(self, celda):
        abiertos = []
        vecAux=self.vecinos(celda)
        for i in vecAux:
            if self.mapa[(i)]==VACIO:
                abiertos.append(i)
        #print(abiertos)

        return abiertos

    def buscar_camino_recto(self, origen, destino):
        route = []
        if (origen[0] == destino[0] or origen[1] == destino[1]):
            x = origen[0]
            y = origen[1]
            while ((x,y) != destino):
                if (x < destino[0]):
                    x += 1
                elif (x > destino[0]):
                    x -= 1 
                elif (y < destino[1]):
                    y += 1 
                elif (y > destino[1]):
                    y -= 1
                if (self.mapa[(x,y)] == MURO):
                    return list()
                route.append((x,y)) 
        return route

    def buscar_camino(self, origen, destino):
        #Tambien llamado algoritmo estrella
        #TODO
        caminoInverso = []
        camino = []

        #Creamos lista de celdas abiertas
        costoActual=0
        opened = {origen: Nodo(origen,distancia(origen, destino),None)}
        closed ={}
     
        while len(opened) > 0:
            A=calcularMenorCoste(opened)
            #Si es el destino, paramos
            if A.posicion == destino:
                break
            costoActual+=1
            closed=[A.posicion]=A
            vecinos=self.abiertos(A.posicion)
           
            for vecino in vecinos:
                if not vecino in closed or vecino in opened:
                    opened[vecino]=Nodo(vecino, costoActual+distancia(vecino,destino),A)

            if A.posicion != destino:
                return camino 

            temporal= A
            while(temporal is not None):
                caminoInverso.append(temporal.posicion)
                temporal=temporal.precursor

            for elem in caminoInverso[::-1]:
                camino.append(elem)

        return camino

    def getPath(self, data, dest):
        pos = dest

        path = []

        while (data[pos].parent != pos):
            path.insert(0, pos)
            pos = data[pos].parent

        path.insert(0, pos)
       
        return path

    def validDestination(self, origin, dest):
         if (self.esta_dentro(origin) == False):
            #print("Origin is out of bounds!")
            return False
         elif (self.esta_dentro(dest) == False):
            #print("Destination is out of bounds!")
            return False
         elif (self.mapa[origin] == MURO):
            #print("Origin is blocked!")
            return False
         elif (self.mapa[dest] == MURO):
            #print("Destination is blocked!")
            return False
         elif (origin == dest):
            #print("Already in destination")
            return False
        
         return True
        

    def AStarSearch(self, origin, dest):
        if (self.validDestination(origin, dest) == False):
            return list()

        closedCellList = {(x,y) : False for x in range(self.ancho_mapa) for y in range(self.alto_mapa)}
        cellData = {(x, y) : Cell(float("inf"), float("inf"), float("inf"), None) for x in range(self.ancho_mapa) for y in range(self.alto_mapa)}

        cellData[origin].g = 0
        cellData[origin].h = 0
        cellData[origin].f = 0
        cellData[origin].parent = origin

        openCellList = []
        bisect.insort(openCellList, Pair(0.0, origin))

        while(len(openCellList) > 0):
            openCell = openCellList.pop(0)

            parentPos = openCell.position

            closedCellList[parentPos] = True
            neighbours = self.vecinos4(parentPos)
        
            for neighbour in neighbours:
                newF = 0.0
                newG = 0.0
                newH = 0.0
                if (neighbour == dest):
                    cellData[neighbour].parent = parentPos
                    return self.getPath(cellData, dest)
                elif (closedCellList[neighbour] == False):  
                    newG = cellData[parentPos].g + 1
                    newH = distancia(neighbour, dest)
                    newF = newG + newH

                    if (cellData[neighbour].f > newF):
                        bisect.insort(openCellList, Pair(newF, neighbour))
                        cellData[neighbour].f = newF
                        cellData[neighbour].g = newG
                        cellData[neighbour].h = newH
                        cellData[neighbour].parent = parentPos
        #print("No path found")
        return list()


    def mostrar_mapa(self):
        for y in range(self.alto_mapa):
            for x in range(self.ancho_mapa):
                # PANTALLA.blit(textures[mapa[row][column]], (column*self.lado_celda,row*self.lado_celda))
                self.mostrar_celda((x,y), colores_mapa[self.mapa[(x,y)]])

    def mostrar_celda(self, celda, color):
        (x,y) = celda
        pygame.draw.rect(self.pantalla, color,
                         (y * self.lado_celda, x * self.lado_celda, self.lado_celda, self.lado_celda))


#if __name__ == '__main__':

#    mapa = Mapa(20,20,10)
#    mapa.mapa[(10, 10)]=MURO
#    mapa.mapa[(11, 11)] = MURO

#    mapa.generar_aleatorio()
#    mapa.generar_automata()

#    pasos = mapa.buscar_camino((1,0),(12,19))

#    for paso in pasos:
#        print(paso)
#        mapa.mostrar_mapa()
#        mapa.mostrar_celda(paso, color_mapa.ROJO)
#        pygame.display.update()
#        pygame.time.wait(1000)

    
    

   
     

    

    

       

            