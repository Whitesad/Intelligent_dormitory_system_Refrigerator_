import bluetooth

bd_addr = "98:D3:91:FD:37:0A"
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
sock.connect((bd_addr,port))

while 1:
        tosend=b'z'
        sock.send(tosend)

sock.close()