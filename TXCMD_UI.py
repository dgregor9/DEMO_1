##################
#ECE599 - HW4 (MazeRunner)
#David Gregory
##################
# Transmitter Code - Run on VM#

import socket

UDP_IP = "10.10.10.100" #Target IP (destination); RPi
UDP_PORT = 5005

# Setup socket connection to Raspberry Pi
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP

while True:
  CMD = raw_input("Type CMD (w,a,d,x,s):")
  
  #FORWARD
  if CMD == "w":
  	print("FORWARD")
	sock.sendto(CMD, (UDP_IP, UDP_PORT))
	
  #LEFT	
  elif CMD == "a":
	print("LEFT")
	sock.sendto(CMD, (UDP_IP, UDP_PORT))
	
  #RIGHT	
  elif CMD == "d":
	print("RIGHT")
	sock.sendto(CMD, (UDP_IP, UDP_PORT))
	
  #REVERSE	
  elif CMD == "x":
	print("REVERSE")
	sock.sendto(CMD, (UDP_IP, UDP_PORT))

  #STOP	
  elif CMD == "s":
	print("STOP")
	sock.sendto(CMD, (UDP_IP, UDP_PORT))
	
  #ERROR	
  else:
	print("INCORRECT: TRY AGAIN!")







