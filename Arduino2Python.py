import serial
import time
import pyautogui as pg
SerialObj = serial.Serial('COM9') # COMxx  format on Windows
                  # ttyUSBx format on Linux
SerialObj.baudrate = 9600  # set Baud rate to 9600
SerialObj.bytesize = 8   # Number of data bits = 8
SerialObj.parity  ='N'   # No parity
SerialObj.stopbits = 1   # Number of Stop bits = 1
time.sleep(3)
#SerialObj.write(b'A')    #transmit 'A' (8bit) to micro/Arduino

while True:
    liste = []
  
    Rs = SerialObj.readline()
    Rs = str(Rs)
    Rs = Rs.replace("b'", "")
    
    Rs = Rs.replace("\\r\\n'", "")


    print(Rs)
        

SerialObj.close() 

SerialObj.close()     
 # Close the port
