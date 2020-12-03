import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

cmap = ListedColormap(['white', 'red'])

matrix = []
with open('../cmake-build-debug/matrix_dump.txt') as f:
    for line in f:
        row = line[:-1]
        matrix.append([int(num) for num in row])

plt.matshow(matrix, cmap=cmap)
plt.show()
