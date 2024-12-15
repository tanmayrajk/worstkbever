import serial
import time
import pyautogui    

SERIAL_PORT = 'COM5'
BAUD_RATE = 115200

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud rate")
    time.sleep(2)

    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip('\n')
            pyautogui.write(data)

except KeyboardInterrupt:
    print("Stopped by User")

except serial.SerialException as e:
    print(f"Error: {e}")

finally:
    ser.close()
    print("Serial connection closed")
