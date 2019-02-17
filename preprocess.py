import os
import csv

path = '/mnt/c/Users/Kulkarni/Work/imu_based_handwriting_recognition/data/'
reqd_len = 300
padding_values = [10000, 0.092, -0.041, -0.028, 11.265, 2.235, 9.82]

with open(path + 'a_letter.csv', 'rb') as f :
    reader = csv.reader(f)
    readings = list()
    for row in reader :
        n = len(row)
        if n != 1 :
            readings.append(row)
            # print(type(row))
        if n == 1 :
            length = len(readings)
            k = 0
            pad_length = (reqd_len - length) // 2
            if ((pad_length * 2) + length) < 300 : 
                k = 1
            print((pad_length * 2) + length + k)
            with open('final_data/a.csv', 'ab') as wf :
                wrf = csv.writer(wf)
                for i in range(pad_length) :
                    wrf.writerow(padding_values)
                for reading in readings :
                    wrf.writerow(reading)
                for i in range(pad_length + k) :
                    wrf.writerow(padding_values)

            readings = list()