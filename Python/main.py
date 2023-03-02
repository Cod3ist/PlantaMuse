import serial
import datetime
from firebase import firebase

ser = serial.Serial('COM6', 9600)

firebase = firebase.FirebaseApplication("https://plantamuse-default-rtdb.asia-southeast1.firebasedatabase.app/", None)


def retriveData():
    data = ser.readline()
    return data


while (True):
    date = datetime.date.today()
    time = datetime.datetime.now().strftime("%H:%M:%S")
    path_readings = '/Device/pixie/Readings/' + str(date)
    path_state = '/Device/pixie/'
    uInput = retriveData().decode().split(',')
    print(uInput[0])
    try:
        if ('OFF' in uInput[0]):
            if (firebase.get('/Device/pixie/State', '') != 'OFF  '):
                state = {
                    'State': uInput[0].rstrip('\r\n')
                }
                firebase.patch(path_state, state)
            else:
                continue
        elif ('ON' in uInput[0]):
            value = uInput[1].rstrip('\r\n')
            data = {
                'time': time,
                'value': int(value)
            }
            state = {
                'State': uInput[0]
            }
            firebase.patch(path_readings, data)
            firebase.patch(path_state, state)
    except KeyboardInterrupt:
        state = {
            'State': 'OFF'
        }
        firebase.patch(path_state, state)

