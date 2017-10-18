#from fake_lib import *
from real_lib import *

import random as rnd

random = rnd.randrange

def shuffle(arr, length):
    rnd.shuffle(arr)

def delay(millis):
    time.sleep(millis/1000.0)