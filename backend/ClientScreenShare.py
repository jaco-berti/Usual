from vidstream import ScreenShareClient
import threading

client = ScreenShareClient('127.0.0.1', 8080);

t = threading.Thread(target=client.start_stream)
t.start()

while input("") != "STOP":
	continue

client.stop_stream()