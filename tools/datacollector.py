import serial
import time
import threading
from datetime import datetime

PORT = "COM8"
BAUDRATE = 115200
OUTPUT_FILE = "aahaar_dataset.txt"

stop_requested = False

def wait_for_stop():
    global stop_requested
    input()
    stop_requested = True

print("======================================")
print("       AAHAAR SCANNER DATA LOGGER")
print("======================================")

fruit = input("Enter fruit name: ").strip()
ripeness = input("Enter ripeness: ").strip()

if not fruit or not ripeness:
    print("ERROR: Fruit and ripeness are required.")
    raise SystemExit(1)

try:
    ser = serial.Serial(PORT, BAUDRATE, timeout=1)
except Exception as e:
    print("ERROR: Cannot open serial port.")
    print(e)
    raise SystemExit(1)

time.sleep(2)
ser.reset_input_buffer()

command = f"LABEL,{fruit},{ripeness}\n"
ser.write(command.encode())
ser.flush()

time.sleep(1)

while ser.in_waiting:
    response = ser.readline().decode("utf-8", errors="ignore").strip()
    if response:
        print("ESP32:", response)

input("Press ENTER to START collection...")

ser.write(b"START\n")
ser.flush()

print("\nCAPTURING - press ENTER to stop\n")

with open(OUTPUT_FILE, "a", buffering=1, encoding="utf-8") as file:
    if file.tell() == 0:
        file.write(
            "timestamp,fruit,ripeness,"
            "F1,F2,F3,F4,F5,F6,F7,F8,NIR,CLEAR\n"
        )

    stop_thread = threading.Thread(target=wait_for_stop, daemon=True)
    stop_thread.start()

    count = 0

    while not stop_requested:
        line = ser.readline().decode("utf-8", errors="ignore").strip()

        if not line:
            continue

        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
        print("ESP32:", line)

        if line.startswith("DATA,"):
            sensor_data = line[5:]
            file.write(
                f"{timestamp},{fruit},{ripeness},{sensor_data}\n"
            )
            file.flush()
            count += 1

ser.write(b"STOP\n")
ser.flush()
time.sleep(0.5)

ser.close()

print("\n======================================")
print("CAPTURE FINISHED")
print("======================================")
print("Readings saved:", count)
print("File:", OUTPUT_FILE)
