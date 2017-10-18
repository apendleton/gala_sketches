import tkinter, time, math, sys
from threading import Thread

canvas = None
root = None
queue = []

def run(func):
    def thread():
        time.sleep(.5)
        func()

    t = Thread(target=thread)
    t.start()

    global canvas, root
    root = tkinter.Tk()

    canvas = tkinter.Canvas(root, height=600, width=600)
    canvas.pack()

    root.after(0, lambda: _setAll(0))

    def update(ev):
        while len(queue):
            queue.pop(0)()

    root.bind('<<update>>', update)
    root.mainloop()

def anim():
    setAllLow()
    for row in range(12):
        for col in range(12):
            setLevel(row, col, 0.5)
            time.sleep(.1)


def _setLevel(row, col, level):
    x = col * 50
    y = row * 50

    l = hex(math.floor(level * 255))[2:].zfill(2)
    if ('x') in l:
        print(level, l)
    c = "".join(["#", l, l, l])

    global canvas
    canvas.create_rectangle(x, y, x + 50, y + 50, fill=c)

def _setAll(level):
    l = hex(math.floor(level * 255))[2:].zfill(2)
    c = "".join(["#", l, l, l])

    global canvas
    canvas.create_rectangle(0, 0, 600, 600, fill=c)

def setLevel(row, col, level):
    global queue
    queue.append(lambda: _setLevel(row, col, level))
    root.event_generate("<<update>>", when="tail")

def setAll(level):
    global queue
    queue.append(lambda: _setAll(level))
    root.event_generate("<<update>>", when="tail")

def setAllLow():
    setAll(0)

def setAllHigh():
    setAll(0)

def render():
    pass