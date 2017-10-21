import pyenttec, math, time

global port

channels = [
    [  221,  206,  208,  204,  209,  214,  219,  195,  196,  194,  193,  197 ],
    [  226,  231,   40,   65,   71,  207,  212,  215,   89,    0,   92,   93 ],
    [  234,   86,   29,   38,   37,  235,  205,  198,   53,   52,   54,   55 ],
    [  236,  233,   70,   31,   30,   94,  237,  238,    1,   77,   78,   72 ],
    [   41,   43,   68,   91,   95,   96,   36,  239,  200,   73,  100,    3 ],
    [  230,  203,   69,   97,   99,   67,   49,   48,   17,   80,   13,   81 ],
    [  192,  201,   64,   27,   34,   74,   79,   51,   50,   12,   98,  232 ],
    [  199,  229,   66,   45,   35,    5,    4,   22,   16,   83,  102,  223 ],
    [  224,  104,   46,   44,   42,   85,    7,   20,   10,  103,   90,    2 ],
    [    8,  210,   24,   47,   26,   88,   23,   11,   82,   75,   57,  101 ],
    [  225,  202,  216,  213,   84,   18,   19,   62,   60,   61,   56,   33 ],
    [  211,   28,   87,  222,  227,    6,   21,   59,   58,   63,   76,   32 ],
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
