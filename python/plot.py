import matplotlib.pyplot as plt
import numpy as np
import csv

path = "../MN_projekt_2_188839/wyniki.csv"
f = open(path, "r")
data = list(csv.reader(f, delimiter=","))
f.close()

dataArray = np.array(data)

print(dataArray[1][1])

x = np.array([row[1] for row in dataArray[6::3]]).astype(np.int64)
y = np.array([row[3] for row in dataArray[6::3]]).astype(np.float64)
y1 = np.array([row[3] for row in dataArray[7::3]]).astype(np.float64)
y2 = np.array([row[3] for row in dataArray[8::3]]).astype(np.float64)
print(x)
print(y)

fig, ax = plt.subplots()
ax.plot(x, y, color='r', label="Jacobi")
ax.plot(x, y1, color='g', label="Gauss-Seidl")
ax.plot(x, y2, color='b', label="LU")
ax.legend()
ax.set_title("Czas potrzebny na iteracje")
ax.set_xlabel("Iteracje[n]")
ax.set_ylabel("Czas[s]")
plt.show()
