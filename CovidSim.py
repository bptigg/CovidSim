import matplotlib.pyplot as plt

def main():
    file = input("Filename: ")
    CVO_file = open("Output/" + file + ".cvo", "r")

    values = []
    for i in range(0,9):
        values.append(CVO_file.readline().strip())
    values.pop(0)
    CVO_file.close()
    
    R_0 = []
    Mortality = []
    Morbidity = []

    succept = []
    infected = []
    removed = []
    dead = []
    host = []

    read(values, R_0, " R0.cvo", 0, CVO_file, file)
    read(values, succept, " succept.cvo", 1, CVO_file, file)
    read(values, infected, " infected.cvo", 2, CVO_file, file)
    read(values, removed, " recovered.cvo", 3, CVO_file, file)
    read(values, host, " host.cvo", 4, CVO_file, file)
    read(values, dead, " dead.cvo", 5, CVO_file, file)
    read(values, Mortality, " mortality.cvo", 6, CVO_file, file)
    read(values, Morbidity, " morbidity.cvo", 7, CVO_file, file)
    
    print("Data Loaded")
    
    if values[0] == '1':
        draw(R_0, file + " R0")
    if values[1] == '1':
        draw(succept, file + " susceptible")
    if values[2] == '1':
        draw(infected, file + " infected")
    if values[3] == '1':
        draw(removed, file + " recovered")
    if values[4] == '1':
        draw(host, file + " hostpilized")
    if values[5] == '1':
        draw(dead, file + " dead")
    if values[6] == '1':
        draw(Mortality, file + " mortality rate")
    if values[7] == '1':
        draw(Morbidity, file + " morbidity rate")

def read(list_1, list_2, extension, position, FILE, file_name):
    if list_1[position] == '1':
        FILE = open("Output/" + file_name + extension, "r")
        for value in FILE:
            list_2.append(float(value.split()[0]))
        FILE.close()

def draw(list , name):
    plt.plot(list)
    plt.show()
    #plt.savefig("Graphs/" + name )
    plt.close()

main()