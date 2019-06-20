import bluetooth
import socket
import threading
import json
from time import sleep
import datetime

bd_addr = "98:D3:91:FD:37:0A"
port = 1
HC05 = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
Dict_Tem={}
List_Connect=[]


def InitialBluetooth():
    HC05.connect((bd_addr, port))

def BroadcastTem():
    dict={}
    dict['type']='TEM'
    dict['currenttem']=Dict_Tem['c']
    dict['targettem']=Dict_Tem['t']
    for con in List_Connect:
        try:
            bytes_mes = bytes(json.dumps(dict), encoding='utf8')
            con.send(bytes_mes)
            sleep(0.01)
        except:
            con.close()
            List_Connect.remove(con)
            print('Send Error! Connect has removed!')

def Thread_Fresh():
    while True:
        HC05.send(b'SSSSSS')
        sleep(10)

def Thread_Listen(con):
    while True:
        try:
            dict_bytes = con.recv(2048)
            dict_dict = json.loads(str(dict_bytes, encoding='utf8'))
            if('type'in dict_dict.keys() and dict_dict['type']=='COMMAND'):
                if(dict_dict['command']=='up'):
                    Upper_Tem()
                elif(dict_dict['command']=='lower'):
                    Lower_Tem()
        except:
            con.close()
            List_Connect.remove(con)
            print('Listen Error! Connect has removed!')

def ReceiveTem():
    global Dict_Tem
    time_stamp = datetime.datetime.now()
    while True:
        data=str(HC05.recv(48))
        try:
            sub_data=data[data.index('}')+1:]
            content=sub_data[sub_data.index('{'):sub_data.index('}')+1]
            dict_tem=json.loads(content)
            Dict_Tem=dict_tem
            print(time_stamp.strftime('%Y.%m.%d-%H:%M:%S'))
            print("Success Receive!The Tem has been refreshed!")
            BroadcastTem()
        except:
            print('Receive Message Error!')
            raise Exception('Receive Message Error!')
        sleep(0.1)

def Lower_Tem():
    print('Lower The Tem')
    HC05.send(b'DDDDDDDD')
    return
def Upper_Tem():
    print('Update The Tem')
    HC05.send(b'UUUUUUUU')
    return

def test():
    print('-------Test Mode--------')
    while True:
        ch=input('input select:')
        if(ch=='U'):
            Upper_Tem()
        elif(ch=='D'):
            Lower_Tem()
        print(Dict_Tem)

if __name__=="__main__":
    InitialBluetooth()
    threading.Thread(target=Thread_Fresh).start()
    threading.Thread(target=ReceiveTem).start()

    threading.Thread(target=test,args=()).start()

    BluzServer=socket.socket()
    BluzServer.bind('127.0.0.1',49999)
    BluzServer.listen(2)
    print('BluzServer Start!')
    while True:
        con, addr = BluzServer.accept()  # recieve connect,addr which contains ip and port
        print('Connect ' + addr[0] + ':' + str(addr[1]) + " Connected!")
        threading.Thread(target=Thread_Listen,args=(con,)).start()
        List_Connect.append(con)