import matplotlib.pyplot as plt
import numpy as np
import csv

path = "Ja_2000.csv"
path1 = "GS_2000.csv"
f = open(path, "r")
dataJa = list(csv.reader(f, delimiter=","))
f.close()

f = open(path1, "r")
dataGS = list(csv.reader(f,delimiter=","))
f.close()

dataJaArray = np.array(dataJa)
dataGSArray = np.array(dataGS)

Ja_length = len(dataJaArray)
GS_length = len(dataGSArray)

xJa = np.array(range(1, Ja_length)).astype(np.int64)
xGS = np.array(range(1, GS_length)).astype(np.int64)
yJa = np.array([row[1] for row in dataJaArray[1:]]).astype(np.float64)
yGS = np.array([row[1] for row in dataGSArray[1:]]).astype(np.float64)

fig, ax = plt.subplots()
ax.plot(xJa, yJa, color='r', label="Jacobi")
ax.plot(xGS, yGS, color='g', label="Gauss-Seidl")
plt.yscale("log")
ax.legend()
ax.set_title("Normy u poszczególnych metod w zadaniu E dla macierzy o N = 2000")
ax.set_xlabel("Iteracje[n]")
ax.set_ylabel("Normy")
plt.show()
