import matplotlib.pyplot as plt

# Num of Elements in each class
broj_elemenata = [9992, 10000, 9298, 1406, 9999]

# Class names
klase = ['Slikarstvo', 'Fotografija', 'Šema', 'Skica', 'Tekst']

plt.bar(klase, broj_elemenata, color='skyblue')

plt.title('Broj elemenata po klasi')
plt.xlabel('Klase')
plt.ylabel('Broj elemenata')

# PLotting the graph
plt.show()
