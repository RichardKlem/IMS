import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import numpy as np
import os

DIRECTORY = "/cmake-build-debug/"
FILENAME = "matrix_dump"
EXTENSION = ".txt"

cmap = ListedColormap(['white', 'red'])

for time in range(0, 100):
    file_path = DIRECTORY + FILENAME + str(time) + EXTENSION
    absolute_file_path = os.path.dirname(os.getcwd()) + file_path
    if os.path.isfile(absolute_file_path):
        dump_matrix = []
        with open(absolute_file_path) as f:
            for line in f:
                row = line[:-1]
                dump_matrix.append([int(num) for num in row])

        plt.matshow(dump_matrix, fignum=1, interpolation="nearest", cmap=cmap)
        # set minor axes in between the labels
        nrows, ncols = np.array(dump_matrix).shape
        ax = plt.gca()
        ax.set_xticks([x - 0.5 for x in range(1, ncols)], minor=True)
        ax.set_yticks([y - 0.5 for y in range(1, nrows)], minor=True)
        # plot grid on minor axes
        plt.grid(which="minor", ls="-", lw=2)
        plt.show()
