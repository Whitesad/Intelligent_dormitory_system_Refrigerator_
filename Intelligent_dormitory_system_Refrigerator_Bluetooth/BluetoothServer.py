import bluetooth
import socket
import threading
import json
from time import sleep

bd_addr = "98:D3:91:FD:37:0A"
port = 1
HC05 = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
Dict_Tem={}

def InitialBluetooth():
    HC05.connect((bd_addr, port))

def BroadcastTem(con):
    pass

def ReceiveTem():
    global Dict_Tem
    while True:
        data=str(HC05.recv(48))
        try:
            sub_data=data[data.index('}')+1:]
            content=sub_data[sub_data.index('{'):sub_data.index('}')+1]
            dict_tem=json.loads(content)
            Dict_Tem=dict_tem
            print("Success Receive!")
            # print(data)
            # print(content)
            # print(dict_tem)

        except:
            pass
            # if(not not data):
            #     print('data:'+data)
        sleep(0.1)

def Lower_Tem():
    HC05.send(b'DDDDDDDD')
    return
def Upper_Tem():
    HC05.send(b'UUUUUUUU')
    return

def test():
    threading.Thread(target=ReceiveTem).start()
    while True:
        ch=input('input select:')
        if(ch=='U'):
            Upper_Tem()
        elif(ch=='D'):
            Lower_Tem()
        print(Dict_Tem)

if __name__=="__main__":
    InitialBluetooth()
    test()
    BluzServer=socket.socket()
    BluzServer.bind('127.0.0.1',49999)
    BluzServer.listen(2)
    print('BluzServer Start!')
    while True:
        con, addr = BluzServer.accept()  # recieve connect,addr includes ip and port
        print('Connect ' + addr[0] + ':' + str(addr[1]) + " Try to Connect")
        threading.Thread(target=BroadcastTem,args=(con,)).start()