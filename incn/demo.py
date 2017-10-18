from scenes import *

def program():
    while True:
        for row in range(12):
            for col in range(12):
                print(row, col)
                setAllLow()
                setLevel(row, col, 1)
                render()
                time.sleep(0.5)

run(program)