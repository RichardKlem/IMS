import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import os

DIRECTORY = "/cmake-build-debug/"
FILENAME = "matrix_dump"
EXTENSION = ".txt"

cmap = ListedColormap(['white', 'red'])

for time in range(0, 100, 2):
    file_path = DIRECTORY + FILENAME + str(time) + EXTENSION
    absolute_file_path = os.path.dirname(os.getcwd()) + file_path
    if not os.path.isfile(absolute_file_path):
        break
    matrix = []
    with open(absolute_file_path) as f:
        for line in f:
            row = line[:-1]
            matrix.append([int(num) for num in row])

    plt.matshow(matrix, cmap=cmap)
    plt.show(dpi=600)
