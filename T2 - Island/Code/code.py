import numpy as np
import matplotlib.pyplot as plt
import sys

d = open("../Archives/date.md").readline().split()
rows = int(d[2])
colls = int(d[4])
data = np.zeros((rows,colls))
for k in range (0, int(sys.argv[1])):
    file = open("../Archives/Output/output"+str(k)+".md")
    for linha in file:
        row = int(linha.split()[1])
        coll = int(linha.split()[2])
        data[row, coll] = float(linha.split()[3])
    file.close()
    plt.matshow(data, cmap = plt.cm.get_cmap("gray"))
    plt.savefig("../Images/img"+str(k)+".png")
    plt.close('all')
#data = np.loadtxt('../Archives/Output/output.md')
