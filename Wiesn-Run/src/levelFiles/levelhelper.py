'''
Usage:
ipython
run levelhelper.py
L = Levelhelper()
L.makePlanes(12345,130,10)
    -> copy to Levelfile
'''



class Levelhelper:
    'Encapsulates the functionality to generate strings for the Wiesn-Run levels.'

    helper_Count = 0

    def __init__(self):
        Levelhelper.helper_Count += 1

    def planes(self, startPos, height, number, mode='print'):
        plane_str = "Plane," + str(startPos) + "," + str(height) + "\n"
        for i in range(1, number):
            plane_str = plane_str + "Plane," + str(startPos + i*120) + "," + str(height) + "\n"
        if mode == 'print':
            print plane_str
        else:
            return plane_str 

    def twoPlanes(self, startPos, height1, height2, number, mode_W='print'):
        plane_str = self.planes(startPos, height1, number, mode='return')
        plane_str = plane_str + self.planes(startPos + 120, height2, number - 1, mode='return')
        if mode_W == 'print':
            print plane_str
        else:
            return plane_str

    def touristPlanes(self, startPos, height, number, mode_T='print'):
        out_str = self.planes(startPos, height, number, mode='return')
        tourists = int(round(number / 2, 0))
        for i in range(1, tourists + 1):
            out_str = out_str + "Tourist," + str(startPos + 120 + (i-1)*240) + "," + str(height+20) + "," + "0" + "\n"
        if mode_T == 'print':
            print out_str
        else:
            return out_str

    def beerObstacle(self, startPos, height, mode_b='print'):
        out_str = "Obstacle," + str(startPos) + "," + str(height) + "\n" + "Bier," + str(startPos) + "," + str(height + 140) + "\n"
        if mode_b == 'print':
            print out_str
        else:
            return out_str

    def securityObstacle(self, startPos, height, mode_s='print'):
        out_str = "Obstacle," + str(startPos) + "," + str(height) + "\n" + "Security," + str(startPos) + "," + str(height + 120) + "\n"
        if mode_s == 'print':
            print out_str
        else:
            return out_str

    def start(self):
        exit = 0
        while(not exit):
            print(chr(27) + "[2J")
            print "\nWelcome to the Levelhelper!\n"
            print "1) Make planes"
            print "2) Make two walkways"
            print "3) Make planes with standing tourists upon them"
            print "4) Make an obstacle with a beer upon it"
            print "5) Make an obstacle with a security upon it"
            print "0) Exit"
            menuEntry = int(raw_input("Go for "))
            if menuEntry == 1:
                print "Planes choosen."
                #print "Please enter the start position, height and number of planes separated by commas."
                print "Example: 1000, 130, 5"
                inTouple = input("start position, height, number of planes: ")
                print "Here you go:"
                self.planes(int(inTouple[0]), int(inTouple[1]), int(inTouple[2]))
                ok = raw_input("Press enter ")
            if menuEntry == 2:
                print "Two walkways choosen."
                #print "Please enter the start position, first height, second height and number of planes in the lower row separated by commas."
                print "Example: 1000, 130, 280, 5"
                inTouple = input("start position, first height, second height, number of planes: ")
                print "Here you go:"
                self.twoPlanes(int(inTouple[0]), int(inTouple[1]), int(inTouple[2]), int(inTouple[3]))
                ok = raw_input("Press enter ")
            if menuEntry == 3:
                print "Planes with tourists on them choosen."
                #print "Please enter the start position, height and number of planes separated by commas."
                print "Example: 1000, 130, 5"
                inTouple = input("start position, height, number of planes: ")
                print "Here you go:\n"
                self.touristPlanes(int(inTouple[0]), int(inTouple[1]), int(inTouple[2]))
                ok = raw_input("Press enter ")
            if menuEntry == 4:
                print "Obstacle with beer upon it choosen."
                #print "Please enter the start position and height separated by commas."
                print "Example: 1000, 0"
                inTouple = input("start position, height: ")
                print "Here you go:\n"
                self.beerObstacle(int(inTouple[0]), int(inTouple[1]))
                ok = raw_input("Press enter ")
            if menuEntry == 5:
                print "Obstacle with security upon it choosen."
                #print "Please enter the start position and height separated by commas."
                print "Example: 1000, 0"
                inTouple = input("start position, height: ")
                print "Here you go:\n"
                self.securityObstacle(int(inTouple[0]), int(inTouple[1]))
                ok = raw_input("Press enter ")
            if menuEntry == 0:
                exit = 1


# Anlegen einer neuen Instanz und starten
L = Levelhelper()
L.start()



