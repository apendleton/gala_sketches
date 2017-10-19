import time, math, json
from lib import *

def rainbow(duration):
    t = time.time()

    setAllRingsLow()

    current = 0

    fade = [None] * 72
    for i in range(72):
        fade[i] = 6 * i / 71.0


    colors = [
        # red
        [255,0,0],

        # orange
        [255,128,0],

        # yellow
        [255,255,0],

        # green
        [0,255,0],

        # blue
        [0,0,255],

        # indigo
        [0,0,128],

        # violet
        [128,0,128]
    ]

    rowMap = {0:0,1:1,2:2,3:3,4:4,5:5,6:5,7:4,8:3,9:2,10:1,11:0}
    px = [None] * 12*12*12

    for row in range(12):
        for light in range(12):
            rRow = (6 * row) + rowMap[light]
            f = fade[rRow]
            base = int(math.floor(f))
            step = f - base
            if step == 0:
                color = colors[base]
            else:
                color = [None] * 3
                for p in range(3):
                    color[p] = int(math.floor((step * colors[base + 1][p]) + ((1 - step) * colors[base][p])))


            for col in range(12):
                px[144*row + 12*col + light] = color




    while True:
        if time.time() - t > duration:
            return

        if current < 60:
            level = (current + 1) / 60.0
            for row in range(12):
                for col in range(12):
                    for i in range(12):
                        color = px[144*row + 12*col + i]
                        setRingL(row, col, i, [int(math.floor(level*color[0])), int(math.floor(level*color[1])), int(math.floor(level*color[2]))])



        elif current >= 600:
            current = 61

        current += 1

        render()
        delay(100)

def spinner(duration):
    t = time.time()

    setAllRingsLow()

    current = 0
    while True:
        if time.time() - t > duration:
            return

        for row in range(12):
            for col in range(12):
                setRingL(row, col, (current - 1) % 12, [0,0,0])
                setRingL(row, col, current, [255,0,0])


        current = (current + 1) % 12

        render()
        delay(100)

def vid(duration, frames, ifr=100):
    t = time.time()

    setAllRingsLow()

    current = 0
    while True:
        if time.time() - t > duration:
            return

        frame = frames[current]
        for row in range(24):
            for col in range(24):
                setRingGlobalQ(row, col, frame[col][row])


        current = (current + 1) % len(frames)
        render()
        delay(ifr)

def grapevine(duration):
    t = time.time()

    setAllRingsLow()

    evens = [0, 1, 2, 3, 4, 5]
    odds = [11, 10, 9, 8, 7, 6]

    grad = {
        9: 0, 10: 1, 11: 2, 0: 3, 1: 4, 2: 5, 3: 5, 4: 4, 5: 3, 6: 2, 7: 1, 8: 0
    }

    current = 0
    direction = 1
    orientation = 1

    leftColor = [random(256), random(256), random(256)]
    rightColor = [random(256), random(256), random(256)]

    while True:
        if time.time() - t > duration:
            return

        dot = current % 6
        ring = int(math.floor(current / 6.0))

        for col in range(12):
            if col % 2 == 0:
                target = 0 if direction == 1 else 1
                cycle = evens if ring % 2 == target else odds
                hotRing = ring
                hotDot = dot
            else:
                target = 1 if direction == 1 else 0
                cycle = evens if ring % 2 == target else odds
                hotRing = 11 - ring
                hotDot = 5 - dot


            if orientation:
                colorSlot = (6 * col) + grad[cycle[hotDot]]

                color = [None] * 3
                for i in range(3):
                    lower = min(rightColor[i], leftColor[i])
                    upper = max(rightColor[i], leftColor[i])
                    color[i] = int(math.floor((colorSlot/72.0) * (upper - lower)) + lower)

                setRingL(hotRing, col, cycle[hotDot], color)
            else:
                setRingL(col, hotRing, (cycle[hotDot] + 9) % 12, [0,0,0])


        current += direction

        if direction == 1 and current == 72:
            current -= 1
            direction = -1
        elif direction == -1 and current == -1:
            current += 1
            direction = 1
            orientation = not orientation
            leftColor = [random(256), random(256), random(256)]
            rightColor = [random(256), random(256), random(256)]

        render()
        delay(100)

def sequence(duration):
    t = time.time()

    current = 0
    while True:
        setAllRingsLow()
        for row in range(12):
            for col in range(12):
                if time.time() - t > duration:
                    return

                setRing(row, col, (0,127,255))
                render()
                delay(250)
