import os
import time
import argparse


PythonProjects: list[str] = ["thefuck", "fastapi", "spacy", "youtube-dl"]

interval = lambda beg, end: (
    list(range(beg, end + 1)) if beg < end else list(range(beg, end - 1, -1))
)

SortedVersion: dict[str, int] = dict()
SortedVersion["cppcheck"] = [
    7,
    1,
    27,
    2,
    15,
    29,
    14,
    6,
    23,
    5,
    17,
    30,
    24,
    8,
    16,
    25,
    3,
    19,
    9,
    18,
    12,
    11,
    21,
    28,
    13,
    20,
    22,
    4,
    26,
    10,
]
SortedVersion["proj"] = [
    24,
    8,
    13,
    12,
    11,
    21,
    22,
    9,
    18,
    16,
    1,
    3,
    17,
    2,
    4,
    19,
    10,
    6,
    20,
    5,
    27,
    23,
    14,
    28,
    15,
    7,
    26,
    25,
]
SortedVersion["openssl"] = [
    13,
    1,
    2,
    9,
    12,
    19,
    14,
    28,
    11,
    15,
    5,
    18,
    16,
    22,
    10,
    23,
    26,
    24,
    25,
    17,
    6,
    4,
    7,
    27,
    20,
    21,
]
SortedVersion["cpp_peglib"] = [8, 9, 7, 6, 5, 4, 2, 3, 1, 10]
SortedVersion["exiv2"] = [
    10,
    15,
    14,
    4,
    13,
    6,
    8,
    9,
    11,
    12,
    7,
    5,
    16,
    17,
    3,
    2,
    1,
    18,
    19,
    20,
]
SortedVersion["libchewing"] = [6, 8, 3, 4, 5, 7, 2, 1]
SortedVersion["libxml2"] = [4, 7, 1, 2, 3, 5, 6]
SortedVersion["yaml_cpp"] = [10] + list(range(1, 9 + 1))
SortedVersion["thefuck"] = interval(32, 13) + interval(11, 1)
SortedVersion["fastapi"] = interval(16, 2)
SortedVersion["spacy"] = interval(7, 1)
SortedVersion["youtube-dl"] = (
    interval(35, 31)
    + interval(10, 8)
    + [30, 7, 29, 28, 6, 27, 26, 5, 25, 24]
    + interval(23, 18)
    + [3, 16, 2, 15, 1, 13, 12, 11]
)

SBFL: list[str] = ["ochiai", "dstar", "barinel"]
AENEAS: list[str] = ["aeneas-ochiai", "aeneas-dstar", "aeneas-barinel"]
DLFL: list[str] = [f"{DL}-{Num}" for DL in ["CNN", "RNN", "MLP"] for Num in range(1, 6)]


def plotEqual(Iteration: int) -> None:
    print("=" * Iteration)


def main() -> int:
    Parser = argparse.ArgumentParser()
    Parser.add_argument(
        dest="Method",
        type=str,
        action="store",
        help="Baseline fault localization method",
    )
    Parser.add_argument(
        dest="Proj",
        type=str,
        action="store",
        help="Target project",
    )
    Parser.add_argument(
        "-t",
        "--thread",
        dest="Thread",
        type=int,
        default=1,
        action="store",
        help="Number of threads to use",
    )
    Parser.add_argument(
        "-u",
        "--updater",
        dest="Updater",
        type=str,
        default="1111",
        action="store",
        help="Updater configuration",
    )
    Args = Parser.parse_args()

    Method = Args.Method
    Proj = Args.Proj
    Thread = Args.Thread if Args.Thread > 0 else 1
    Updater = f"1{Args.Updater}" if Args.Updater != "1111" else ""
    Profile = f"{Method}-{Proj}" + ("-" if Updater != "" else "") + Updater
    CoverageDir = f"/workspace/data/coverage/{Proj}"

    if Proj not in SortedVersion:
        print(f"Invalid project: {Proj}")
        return 1

    if Method in AENEAS:
        CustomSusDir = f"/workspace/data/coverage/{Method}/best/{Proj}"
    elif Method in DLFL:
        CustomSusDir = f"/workspace/data/coverage/{Method[:-2]}/{Method}/{Proj}"
    elif Method in SBFL:
        CustomSusDir = None
    else:
        CustomSusDir = f"/workspace/data/coverage/{Method}/{Proj}"

    # Init profile
    os.system(
        f"pafl profile {Profile} {'py' if Proj in PythonProjects else 'cpp'} {Method if Method in SBFL else 'custom'} {Updater}"
    )
    os.system(f"pafl profile-reset {Profile}")

    # Necessary path
    setSource = lambda version: (
        f"-S /workspace/data/source/{Proj}/{Proj}-{version}/{Proj}"
        if Proj in PythonProjects
        else f"-S /workspace/data/source/{Proj}/buggy-{version}"
    )
    setCoverage = lambda version: f"-T {CoverageDir}/buggy-{version}"
    setOracle = lambda version: f"-O {CoverageDir}/oracle/{version}.json"
    setCustomSus = lambda index: (
        f"--suspiciousness-path {CustomSusDir}/{index}.json"
        if CustomSusDir is not None
        else str()
    )

    # Run Baseline FL method
    BaselineTime = time.time()
    for idx, ver in enumerate(SortedVersion[Proj], 1):
        if (
            os.system(
                f"pafl run-base -P {Profile} {setSource(ver)} {setCoverage(ver)} {setCustomSus(idx)} -c"
            )
            != 0
        ):
            return 1
    BaselineTime = time.time() - BaselineTime

    # Run PAFL
    PAFLTime = time.time()
    for idx, ver in enumerate(SortedVersion[Proj][:-1], 1):
        if (
            os.system(
                f"pafl run-pafl -P {Profile} {setSource(ver)} {setCoverage(ver)} {setCustomSus(idx)} --thread {Thread} -c"
            )
            != 0
        ):
            return 1
        if (
            os.system(
                f"pafl train -P {Profile} {setSource(ver)} {setCoverage(ver)} {setOracle(ver)} {setCustomSus(idx)} --thread {Thread} -c"
            )
            != 0
        ):
            return 1
    ver = SortedVersion[Proj][-1]
    if (
        os.system(
            f"pafl run-pafl -P {Profile} {setSource(ver)} {setCoverage(ver)} {setCustomSus(len(SortedVersion[Proj]))} --thread {Thread} -c"
        )
        != 0
    ):
        return 1
    PAFLTime = time.time() - PAFLTime

    # Display execution time
    Buffer: list[str] = list()
    Buffer.append(f"#Used threads: {Thread}")
    Buffer.append(f"Elapsed time ({Method})       : {BaselineTime:.1f} secs")
    Buffer.append(f"Elapsed time ({Method} + PAFL): {PAFLTime:.1f} secs")
    Buffer.append(
        f"Average overhead: {(PAFLTime - BaselineTime) / len(SortedVersion[Proj]):.1f} secs"
    )
    plotEqual(max([len(line) for line in Buffer]))
    print("\n".join(Buffer))
    plotEqual(max([len(line) for line in Buffer]))

    return 0


if __name__ == "__main__":
    if main() != 0:
        print("Error occurred")
        os.abort()
