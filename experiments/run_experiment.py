"""
author: Richard Klem
email: xklemr00@stud.fit.vutbr.cz
login: xklemr00
date: 6.11.2020
"""

import argparse
import numpy as np
import os
import pandas as pd
import re
import shutil
import stat
import sys


RESULT_FILE = "results{0}.txt"
HEADER = ["#", "N(0)", "S(0)", "I(0)", "p<sub>f</sub>", "p<sub>b</sub>", "p<sub>r</sub>", "p<sub>l</sub>",
          "p<sub>s</sub>", "Cycles"]
BIN_NAME = "covid"

PROJECT_DIRECTORY = os.path.dirname(os.getcwd())
PYTHON_SCRIPT_DIR = os.getcwd()

MAKE_CMD = "make"
RUN_CMD = "./" + BIN_NAME + " {0}"


def main():
    parser = argparse.ArgumentParser(description='Experiments')
    parser.add_argument("-p", "--parameters", action="store", default=os.path.join(os.getcwd(), "experiments.txt"),
                        help="Select a path to a file with parameters.")
    parser.add_argument("--work-dir", action="store", default=os.path.join(os.getcwd(), "build"),
                        help="Path to a build directory.")
    parser.add_argument("--result-dir", action="store", default=os.path.join(os.getcwd(), "results"),
                        help="Path to a folder in which the results will be stored.")

    args = parser.parse_args(sys.argv[1:])

    if os.path.isdir(args.work_dir):
        shutil.rmtree(args.work_dir)
    os.mkdir(args.work_dir)
    os.chdir(PROJECT_DIRECTORY)
    os.system(MAKE_CMD)
    os.chdir(PYTHON_SCRIPT_DIR)
    shutil.copyfile(os.path.join(PROJECT_DIRECTORY, BIN_NAME), os.path.join(args.work_dir, BIN_NAME))
    os.chdir(args.work_dir)
    with open(args.parameters, 'r') as parameters:
        extracted_args = []
        for experiment in parameters.readlines():
            if experiment != os.linesep:
                arguments = re.match(r"(\d{1,2})\.\s(.*)", experiment)
                if os.path.isdir(os.path.join(args.work_dir, f"experiment{arguments.group(1)}")):
                    shutil.rmtree(os.path.join(args.work_dir, f"experiment{arguments.group(1)}"))
                os.mkdir(os.path.join(args.work_dir, f"experiment{arguments.group(1)}"))
                print(f"experiment {arguments.group(1)}")
                if arguments is not None:
                    os.chmod(BIN_NAME, os.stat(BIN_NAME).st_mode | stat.S_IEXEC)
                    average_cycles = []
                    for i in range(10):
                        os.system((RUN_CMD.format(arguments.group(2))) + f" -d experiment{arguments.group(1)}")
                        with open(os.path.join(f"experiment{arguments.group(1)}", "results.txt")) as result_file:
                            cycles = int(result_file.readline())
                            average_cycles.append(cycles)

                    split_args = arguments.group(2).split(' ')
                    extracted_args.append([arguments.group(1)] + split_args[1:-1:2] + [split_args[-1]] +
                                          [str(sum(average_cycles) / len(average_cycles))])

    df = pd.DataFrame(np.array(extracted_args).transpose(), HEADER).transpose()
    with open("agregated_results.html", "w") as html_file:
        html_file.writelines(df.to_html(escape=False))
    return 0


if __name__ == "__main__":
    sys.exit(main())
