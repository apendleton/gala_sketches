from scenes import *

def program():
    plasma_clip = json.load(open("plasma.json"))
    blue_clip = json.load(open("blue.json"))
    heart_clip = json.load(open("heart.json"))

    while True:
        sequence(60)
        spinner(10)
        grapevine(15)
        vid(15, heart_clip, 100)
        vid(15, plasma_clip, 250)
        vid(15, blue_clip, 250)
        rainbow(20)

run(program)
