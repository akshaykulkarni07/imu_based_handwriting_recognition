import os
import csv

path = '/mnt/c/Users/Kulkarni/Work/imu_based_handwriting_recognition/data/'
# Required constant length
reqd_len = 300
# Letter whose data is being pre-processed.
letter = 'b'
# Values to be used as padding. These values are obtained by
# holding the pen stationary and taking an average of those readings.
padding_values = [10000, 0.092, -0.041, -0.028, 11.265, 2.235, 9.82, letter]

with open(path + 'b_letter.csv', 'rb') as f :
    # reader object to read the csv file
    reader = csv.reader(f)
    # an empty list that will contain readings from one sample only
    readings = list()
    for row in reader :
        n = len(row)
        # checking if length of row is not 1, since that would mean end of sample
        if n != 1 :
            # adding the label
            row.append(letter)
            # adding the current row to the current sample
            readings.append(row)
        
        # if length of row is 1, then current sample has ended
        # and needs to be saved after adding required padding on both sides.
        if n == 1 :
            # Calculating padding and also accounting for when padding on both
            # sides is not symmetrical
            length = len(readings)
            k = 0
            pad_length = (reqd_len - length) // 2
            if ((pad_length * 2) + length) < 300 : 
                k = 1

            # writing the padding and data to csv file
            with open('final_data/b.csv', 'ab') as wf :
                wrf = csv.writer(wf)
                for i in range(pad_length) :
                    wrf.writerow(padding_values)
                for reading in readings :
                    wrf.writerow(reading)
                for i in range(pad_length + k) :
                    wrf.writerow(padding_values)

            readings = list()