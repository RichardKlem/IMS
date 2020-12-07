import re
import sys

import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np
import os
import matplotlib.colors

PROJECT_DIRECTORY = os.path.dirname(os.getcwd())
PYTHON_SCRIPT_DIR = os.getcwd()
DUMP_DIRECTORY = PYTHON_SCRIPT_DIR + "/build/"
FILENAME = "matrix_dump"
EXTENSION = ".txt"

RMDIR_CMD = f"rm -r {DUMP_DIRECTORY}"
MKDIR_CMD = f"mkdir {DUMP_DIRECTORY}"
BUILD_CMD = f"cmake -B  {PYTHON_SCRIPT_DIR}/build/ -S {PROJECT_DIRECTORY} && cd ./build/ && make"
RUN_CMD = f"cd  {PYTHON_SCRIPT_DIR}/build/ && ./covid"

GLOBAL_TIME = -1

colors = ["gray", "white", "green", "red", "blue"]

cmap = matplotlib.colors.ListedColormap(colors)

files = []


def update_grid(grid):
    global GLOBAL_TIME
    GLOBAL_TIME = GLOBAL_TIME + 1

    if GLOBAL_TIME < len(files):
        absolute_file_path = DUMP_DIRECTORY + files[GLOBAL_TIME]
        new_grid = []
        with open(absolute_file_path) as f:
            for line in f:
                row = line[:-1]
                new_grid.append([int(num) for num in row])

        grid[:] = new_grid[:]
    return grid


def update_fig(frameNum, img, grid):
    grid = update_grid(grid)
    img.set_data(grid)
    img = plt.matshow(grid, fignum=1, interpolation="nearest", cmap=cmap)
    return img


def set_grid_ticks(ax, ncol_shape, rows_shape):
    ax.set_xticks([x - 0.5 for x in range(1, rows_shape)], minor=True)
    ax.set_yticks([y - 0.5 for y in range(1, ncol_shape)], minor=True)
    plt.grid(which="minor", ls="-", lw=2)


def init_grid():
    absolute_file_path = DUMP_DIRECTORY + files[0]
    new_grid = []
    with open(absolute_file_path) as f:
        for line in f:
            row = line[:-1]
            new_grid.append([int(num) for num in row])

    return new_grid


def init_figure(initial_grid, update_interval, len):
    fig = plt.figure()
    img = plt.matshow(initial_grid, fignum=1, interpolation="nearest", cmap=cmap)
    ax = plt.gca()
    rows_shape, col_shape = np.array(initial_grid).shape
    set_grid_ticks(ax, rows_shape, col_shape)
    ani = animation.FuncAnimation(fig, update_fig, init_func=init_grid, frames=len, fargs=(img, initial_grid),
                                  interval=update_interval, repeat=False)
    plt.show()


def start_simulation():
    if os.path.isdir(DUMP_DIRECTORY):
        os.system(RMDIR_CMD)
    os.system(MKDIR_CMD)
    os.system(BUILD_CMD)
    os.system(RUN_CMD)


def main():
    update_interval = 1000
    start_simulation()

    global files
    files = os.listdir(DUMP_DIRECTORY)

    files = [file for file in files if file.startswith("matrix_dump")]
    files.sort(key=lambda x: [int(c) if c.isdigit() else c for c in re.split('^[a-z]+_[a-z]+(\d+).txt$', x)])

    initial_grid = update_grid([])
    init_figure(initial_grid, update_interval, len(files) - 1)


if __name__ == '__main__':
    sys.exit(main())
