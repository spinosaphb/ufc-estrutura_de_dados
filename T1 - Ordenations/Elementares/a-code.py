import matplotlib.pyplot as plt

plt.figure(num=None, figsize=(8, 6), dpi=90, facecolor='w', edgecolor='k')
archives = ["bubblesort","insertionsort","selectionsort"]
algorithms = ['BubbleSort','InsertionSort','SelectionSort']
formats = ['','','']
kf = open("../Code/data.md")
maxkf = int(kf.readline())
for k in range(maxkf):
    for i in range(3):
        file = open(archives[i]+'/'+archives[i]+str(k)+".md")
        y = []
        x = []
        line = ""
        line2 = ""
        while True:
            line = file.readline()
            line2 = file.readline()
            if(line==''):break
            x.append(int(line.split()[2]))
            y.append(float(line2.split()[2])) 
            file.readline()
        file.close()
        plt.plot(x,y,formats[i],label = algorithms[i])
    plt.legend(loc='upper left', shadow=True, fontsize='x-large').get_frame().set_facecolor('#FFFFFF')
    plt.ylabel("q ( n )")
    plt.xlabel("n")
    plt.title("Algoritmos de ordenação elementares")
    plt.grid()
    plt.savefig("0 - Graphs/fig"+str(k)+".png")
    plt.clf()
#plt.show()
    
        
