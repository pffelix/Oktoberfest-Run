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

    def makePlanes(self, startPos, height, number, mode='print'):
        plane_str = "Plane," + str(startPos) + "," + str(height) + "\n"
        for i in range(1, number):
            plane_str = plane_str + "Plane," + str(startPos + i*120) + "," + str(height) + "\n"

        if mode == 'print':
            print plane_str
        else:
            return plane_str 

    def makeTwoWalkways(self, startPos, height1, height2, number, mode_W='print'):
        plane_str = self.makePlanes(startPos, height1, number, mode='return')
        plane_str = plane_str + self.makePlanes(startPos + 120, height2, number - 1, mode='return')

        if mode_W == 'print':
            print plane_str
        else:
            return plane_str

    def makeTouristPlanes(self, startPos, height, number, mode_T='print'):
        out_str = self.makePlanes(startPos, height, number, mode='return')
        tourists = int(round(number / 2, 0))
        for i in range(1, tourists + 1):
            out_str = out_str + "Tourist," + str(startPos + 120 + (i-1)*240) + "," + str(height+20) + "," + "0" + "\n"

        if mode_T == 'print':
            print out_str
        else:
            return out_str

