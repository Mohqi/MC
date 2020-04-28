# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import matplotlib.pyplot as plt
import csv

x = []
y = []
z = []

with open('data/profilx1.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=' ')
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))

plt.plot(x,y, label='Dose')
plt.xlabel('x')
plt.ylabel('y')
#plt.yscale("log")
plt.title('Dose Fonction de la profondeur')
plt.legend()
plt.show()