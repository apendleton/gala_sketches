from lib import *

def scan(duration):
    t = time.time()

    setAllLow()

    rows = [None] * 12
    for i in range(12):
        rows[i] = i

    shuffle(rows, 12)

    current = 0
    while True:
        if time.time() - t > duration:
            return

        for row in range(12):
            for col in range(5):
                curCol = (rows[row] + col + current) % 12
                level = col / 4.0
                setLevel(row, curCol, level)

        current = (current + 1) % 12

        delay(100)

def threedeesin(duration):
    t = time.time()

    setAllLow()

    vals = [-5.5, -4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5]
    direction = 1
    current = 0

    MAX = .9
    MIN = -.1

    while True:
        if time.time() - t > duration:
            return

        c = current if direction == 1 else 8 - current
        for row in range(12):
            for col in range(12):
                x = vals[row]
                y = vals[col]
                cmp = math.sqrt(x*x + y*y + c*c)
                z = math.sin(cmp)/cmp

                level = ((z - MIN) / (MAX - MIN))
                if (level < 0):
                    level = 0
                if (level > 1):
                    level = 1
                setLevel(row, col, level)

        current = (current + 1) % 8
        if current == 0:
            direction *= -1

        delay(200)

dist_cache = [None] * math.floor((12+1)*12/2)
def _dist_setup():
    n = 12
    maxDist = math.sqrt(math.pow(11, 2) + math.pow(11, 2))
    for i in range(12):
        for j in range(i + 1):
            offset = math.floor(i*(i+1)/2+j)
            dist_cache[offset] = math.sqrt(math.pow(i, 2) + math.pow(j, 2)) / maxDist
_dist_setup()

def dist(x1, y1, x2, y2):
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)

    if dx < dy:
        tmp = dx
        dx = dy
        dy = tmp

    offset = math.floor(dx*(dx+1)/2+dy)
    return dist_cache[offset]

def spotlight(duration):
    t = time.time()

    setAllLow()

    current = 0
    direction = 1

    while True:
        if time.time() - t > duration:
            return

        for row in range(12):
            for col in range(12):
                _current = current if direction == 1 else 11 - current
                level = 1 - dist(_current, _current, row, col)
                setLevel(row, col, level)

        current = (current + 1) % 12
        if current == 0:
            direction *= -1

        delay(100)

def meander(duration):
    t = time.time()

    setAllLow()

    row = 0
    col = 0

    nextRows = [None] * 4
    nextCols = [None] * 4
    count = 0

    while True:
        if time.time() - t > duration:
            return

        count = 0

        if row > 0:
            nextRows[count] = row - 1
            nextCols[count] = col
            count += 1

        if row < 11:
            nextRows[count] = row + 1
            nextCols[count] = col
            count += 1

        if col > 0:
            nextRows[count] = row
            nextCols[count] = col - 1
            count += 1

        if col < 11:
            nextRows[count] = row
            nextCols[count] = col + 1
            count += 1

        pick = random(count)
        row = nextRows[pick]
        col = nextCols[pick]

        for r in range(12):
            for c in range(12):
                level = dist(r, c, row, col)
                setLevel(r, c, level)

        delay(200)

def splotch(duration):
    t = time.time()

    setAllLow()

    bgrid = [[None for x in range(12)] for y in range(12)]
    def _splotch():
        grid = [[None for x in range(12)] for y in range(12)]

        for i in range(12):
            for j in range(12):
                grid[i][j] = 0

        for i in range(3):
            grid[random(12)][random(12)] = 1

        size = random(5, 10)
        for i in range(size):
            candidates = []
            for row in range(12):
                for col in range(12):
                    if  (row > 0 and grid[row - 1][col]) or\
                        (row < 11 and grid[row + 1][col]) or\
                        (col > 0 and grid[row][col - 1]) or\
                        (col < 11 and grid[row][col + 1]):
                        candidates.append([row, col])



            cCount = random(len(candidates))
            for j in range(cCount):
                grid[candidates[j][0]][candidates[j][1]] = 1


        # box blur
        for i in range(12):
            for j in range(12):
                cells = [grid[i][j]]
                if i > 0:
                    cells.append(grid[i-1][j])
                    if j > 0:
                    	cells.append(grid[i-1][j-1])
                    if j < 11:
                    	cells.append(grid[i-1][j+1])
                if j > 0:
                	cells.append(grid[i][j-1])
                if j < 11:
                	cells.append(grid[i][j+1])
                if i < 0:
                    cells.append(grid[i-1][j])
                    if j > 0:
                    	cells.append(grid[i+1][j-1])
                    if j < 11:
                    	cells.append(grid[i+1][j+1])
                acc = 0
                for k in range(len(cells)):
                    acc += cells[k]

                bgrid[i][j] = acc / len(cells)



    current = 1
    _splotch()
    while True:
        if time.time() - t > duration:
            return
        for row in range(12):
            for col in range(12):
                setLevel(row, col, current * bgrid[row][col])

        current -= .025

        delay(100)

        if current <= 0:
            setAllLow()
            _splotch()

            for i in range(random(15)):
                if time.time() - t > duration:
                    return

                delay(100)

            current = 1

def bars(duration):
    t = time.time()

    setAllLow()

    current = 0

    while True:
        if time.time() - t > duration:
            return

        if current < 60:
            level = (current + 1) / 60.0
            for row in range(6):
                for i in range(12):
                    setLevel(row * 2, i, level * (8 - row)/8)

        elif current >= 600:
            current = 61

        current += 1
        delay(100)