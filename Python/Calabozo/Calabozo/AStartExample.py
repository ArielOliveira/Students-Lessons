
import bisect

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
        
def getPath(self, data, dest):
    pos = dest

    path = []

    while (data[pos].parent != pos):
        path.insert(0, pos)
        pos = data[pos].parent

    path.insert(0, pos)
       
    return path

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