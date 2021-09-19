import serial
from time import sleep, time

serial = serial.Serial("COM17")

sped = 800
forwardtime = 1
backtime = 0.3
totaltime = 5

ts = time()
while True:
    t = time()
    if time() - ts > totaltime:
        exit()
    while time() - t < forwardtime:
        serial.write(str(sped).encode())
        sleep(0.2)
    t = time()
    while time() - t < backtime:
        serial.write(str(-sped).encode())
        sleep(0.2)