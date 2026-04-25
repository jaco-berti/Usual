from vidstream import StreamingServer
import threading

server = StreamingServer('127.0.0.1', 8080);

t = threading.Thread(target=server.start_server)
t.start()

while input("") != "STOP":
	continue

server.stop_server()