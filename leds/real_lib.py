from neopixel import *

boards = [
    [  0, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0,  0],
    [  0,  0, -1, -1, -1, -1,  0,  0, -1, -1, -1, -1],
    [  0,  0,  0, -1, -1, -1,  0,  0,  0,  0,  0,  0],
    [  0,  0,  0, -1, -1, -1, -1, -1, -1, -1,  0,  0],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0],
    [  0,  0,  0,  0, -1, -1, -1, -1, -1, -1,  0,  0],
    [  0,  0,  0,  0, -1, -1,  0,  0,  0,  0,  0,  0],
    [ -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0],
    [ -1, -1,  0,  0,  0, -1, -1,  0, -1, -1, -1, -1],
    [ -1, -1, -1,  0,  0, -1, -1,  0, -1, -1, -1, -1],
    [ -1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0]
]

seq = [
    [ 26, -1, -1, -1, -1, -1, 25, 24, 23, 22, 21, 20],
    [ 27, 32, -1, -1, -1, -1,  1,  0, -1, -1, -1, -1],
    [ 28, 31, 33, -1, -1, -1,  2,  3,  4,  5,  6, 19],
    [ 29, 30, 34, -1, -1, -1, -1, -1, -1, -1,  7, 18],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, 17],
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  9, 16],
    [ 53, 54, 55, 56, -1, -1, -1, -1, -1, -1, 10, 15],
    [ 52, 51, 50, 57, -1, -1, 62, 63, 64, 65, 11, 14],
    [ -1, -1, 49, 58, 59, 60, 61, 68, 67, 66, 12, 13],
    [ -1, -1, 48, 47, 46, -1, -1, 69, -1, -1, -1, -1],
    [ -1, -1, -1, 44, 45, -1, -1, 70, -1, -1, -1, -1],
    [ -1, -1, -1, 43, 42, 41, 40, 39, 38, 37, 36, 35]
]



# shared configuration
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 5       # DMA channel to use for generating signal (try 5)
LED_BRIGHTNESS = 5     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)
LED_STRIP      = ws.WS2811_STRIP_GRB   # Strip type and colour ordering

# per-pin configuration
PINS = [
    {
        'LED_PIN': 19,
        'LED_COUNT': 71 * 12,
        'LED_CHANNEL': 1
    },
    {
        'LED_PIN': 12,
        'LED_COUNT': 33 * 12,
        'LED_CHANNEL': 0
    },
    {
        'LED_PIN': 19,
        'LED_COUNT': 27 * 12,
        'LED_CHANNEL': 0
    }
]

def getRingStart(row, col):
    boardNum = boards[row][col]
    if boardNum == -1:
        return

    strip = strips[boardNum]
    idx = seq[row][col]
    start = 12 * idx

    return strip, start

def setRing(row, col, color):
    strip, start = getRingStart(row, col)
    _color = Color(*color)

    for i in range(12):
        strip.setPixelColor(start + i, _color)
    strip.show()

def setRingQ(row, col, q, color):
    strip, start = getRingStart(row, col)
    _color = Color(*color)

    for i in range(3 * q, 3 * (q + 1)):
        strip.setPixelColor(start + i, _color)
    strip.show()

qs = [[3,0],[1,2]]
def setRingGlobalQ(rowq, colq, color):
    rq = rowq % 2;
    row = math.floor(rowq/2);
    cq = colq % 2;
    col = math.floor(colq/2);
    q = qs[rq][cq];

    setRingQ(row, col, q, color)

def setRingL(row, col, l, color):
    strip, start = getRingStart(row, col)
    _color = Color(*color)

    strip.setPixelColor(start + l, _color)
    strip.show()

def setAllRings(row, col, color):
    _color = Color(*color)

    for strip in strips:
        for pixel in range(strip.numPixels()):
            strip.setPixelColor(pixel, _color)
        strip.show()

def setAllRingsLow():
    setAllRings((0,0,0))

def setAllRingsHigh():
    setAllRings((255,255,255))

strips = []
def run(func):
	# Create NeoPixel object with appropriate configuration.
    global strips
    strips = [
        Adafruit_NeoPixel(PIN['LED_COUNT'], PIN['LED_PIN'], LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, PIN['LED_CHANNEL'], LED_STRIP) \
        for PIN in PINS
    ]

    # Intialize the library (must be called once before other functions).
	for strip in strips:
        strip.begin()

    func()
