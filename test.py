import serial
from time import sleep
import msvcrt

serial = serial.Serial("COM17")

sped = 800

while True:
    print(serial.read_all())
    # print(sped)
    serial.write(str(sped).encode())
    sleep(0.2)
    if msvcrt.kbhit():
        print("Switching direction")
        msvcrt.getch()
        sped = -sped