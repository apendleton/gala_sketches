import pyenttec, math, time

global port

channels = [
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1, -1, -1, -1, 17,  0, 13,  1 ],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, -1 ],
    [ -1, -1, -1, -1, -1,  5,  4, 22, 16,  3, -1, -1 ],
    [ -1, -1, -1, -1, -1, -1,  7, 20, 10, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1, -1, 23, 11,  2, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1,  8, 19, -1, -1, -1, -1, -1 ],
    [ -1, -1, -1, -1, -1,  6, 21, -1, -1, -1, -1, -1 ],
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