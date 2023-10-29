import serial
import datetime
import math

print("Enter port:")
portstr = input()
ser = serial.Serial(portstr, 115200)

time = math.floor(datetime.datetime.now(datetime.timezone.utc).timestamp())#+3600)
print(time)
ser.write(b"TIME")
ser.write(str(time).encode())
ser.write(b'\r')
ser.close()
print("Done")
input()