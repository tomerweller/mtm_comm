import serial
import time

ser = serial.Serial("/dev/tty.usbserial-FTGO1C75", 9600)
while True:
	msg = ser.read(1)
	if len(msg) > 0:
		print "echoing", ord(msg)
		ser.write(msg) 