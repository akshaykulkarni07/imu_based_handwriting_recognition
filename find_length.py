import os
import csv

path = '/mnt/c/Users/Kulkarni/Work/imu_based_handwriting_recognition/data/'

for filename in os.listdir('data/'):
    print(filename)
    f = open(path + filename, 'rb')
    # reader object to read the csv file
    reader = csv.reader(f)

    for row in reader :
        n = len(row)
        if n == 1 :
            print(row[0])