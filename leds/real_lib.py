from neopixel import *

# 0: panel 9
# 1: panel 10, 11, 12

boards = [
    [  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0 ],
    [  0,  0,  1,  1,  1,  1,  0,  0,  1,  1,  1,  1 ],
    [  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0 ],
    [  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0 ],
    [  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0 ],
    [  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0 ],
    [  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0 ],
    [  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0 ],
    [  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 ],
    [  1,  1,  0,  0,  0,  1,  1,  0,  1,  1,  1,  1 ],
    [  1,  1,  1,  0,  0,  1,  1,  0,  1,  1,  1,  1 ],
    [  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0 ],
]

seq = [
    [ 26, 19, 20, 21, 36, 35, 25, 24, 23, 22, 21, 20 ],
    [ 27, 32, 18, 22, 67, 66,  1,  0, 64, 63,  5,  4 ],
    [ 28, 31, 33, 68, 14, 65,  2,  3,  4,  5,  6, 19 ],
    [ 29, 30, 34, 15, 13, 10,  9,  6, 62, 34,  7, 18 ],
    [ 37, 69, 17, 72, 45, 11,  8,  7, 31, 33,  8, 17 ],
    [ 38, 70, 16, 71, 44, 12, 61, 29, 30, 32,  9, 16 ],
    [ 53, 54, 55, 56, 43, 60, 58, 28, 57, 56, 10, 15 ],
    [ 52, 51, 50, 57, 42, 59, 62, 63, 64, 65, 11, 14 ],
    [ 49, 50, 49, 58, 59, 60, 61, 68, 67, 66, 12, 13 ],
    [ 48, 41, 48, 47, 46, 51, 27, 69, 26, 25, 55,  3 ],
    [  0, 40, 47, 44, 45, 52, 53, 70, 54, 24, 23,  2 ],
    [  1, 39, 46, 43, 42, 41, 40, 39, 38, 37, 36, 35 ],
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
        'LED_PIN': 12,
        'LED_COUNT': 71 * 12,
        'LED_CHANNEL': 0
    },
    {
        'LED_PIN': 19,
        'LED_COUNT': 73 * 12,
        'LED_CHANNEL': 1
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
