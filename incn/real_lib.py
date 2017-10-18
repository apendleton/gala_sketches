import pyenttec, math, time

global port

channels = [
    [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1, 239, 238, 237, 236, 235, 234, -1],
    [233, -1, -1, 230, 229, 227, -1, 225, -1, 223, -1, 221],
    [220, 219, 218, 216, 215, 214, 213, 212, 211, 210, 209, 208],
    [207, 206, -1, 204, 203, 202, 201, 200, 199, 198, 197, 196],
    [195, -1, 193, 192, -1, -1, -1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
    [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
    [23, 22, 21, 20, 19, 18, 17, 16, -1, 14, -1, 12],
    [11, 10, 9, 8, 7, 6, 5, -1, 3, 2, 1, -1]
]

MAX = 60

def setLevel(row, col, level):
    channel = channels[row][col]
    if channel == -1:
        return
    port.set_channel(channel, math.floor(level * MAX))

def render():
    port.render()

def setAll(level):
    for row in range(12):
        for col in range(12):
            channel = channels[row][col]
            if channel == -1:
                continue
            port.set_channel(channel, math.floor(level * MAX))
    port.render()

def setAllLow():
    setAll(0)

def setAllHigh():
    setAll(1)

def run(func):
    global port

    port = pyenttec.select_port()

    func()