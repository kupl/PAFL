import os
import json
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

DLFL: list[str] = ["CNN", "RNN", "MLP"]


def plotDot(Iteration: int) -> None:
    print("-" * Iteration)


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
    Args = Parser.parse_args()

    Method = Args.Method
    Proj = Args.Proj
    Thread = Args.Thread if Args.Thread > 0 else 1
    CoverageDir = f"/workspace/data/coverage/{Proj}"

    if Proj not in SortedVersion:
        print(f"Invalid project: {Proj}")
        return 1
    if Method not in DLFL:
        print(f"Invalid method: {Method}")
        return 1

    # Train
    for i in range(1, 6):
        MethodIter = f"{Method}-{i}"
        os.system(f"train_and_run {MethodIter} {Proj} -t {Thread}")

    # Init metrics
    BaselineTotal: dict[str, int | float] = {
        "AvgFR": 0,
        "AvgAR": 0,
        "Top-1": 0,
        "Top-5": 0,
        "Top-10": 0,
    }
    PAFLTotal: dict[str, int | float] = BaselineTotal.copy()

    # Evaluate
    for i in range(1, 6):
        MethodIter = f"{Method}-{i}"
        Profile = f"{MethodIter}-{Proj}"
        getOraclePath = lambda version: f"{CoverageDir}/oracle/{version}.json"
        getBaselineDir = (
            lambda version: f"{CoverageDir}/buggy-{version}/__pafl__/{Profile}-base"
        )
        getPAFLDir = (
            lambda version: f"{CoverageDir}/buggy-{version}/__pafl__/{Profile}-pafl"
        )
        TestLocs: list[int] = list()

        for version in SortedVersion[Proj]:
            # Read fault locations
            CoveredLines: list[tuple[str, str]] = list()
            CoveredFaults: set[tuple[str, int]] = set()

            with open(f"{getBaselineDir(version)}/ranking.json", "r") as base_file:
                for line in json.load(base_file)["lines"]:
                    if float(line["sus"]) > 0.0:
                        CoveredLines.append((line["file"], line["line"]))
            with open(getOraclePath(version), "r") as oracle_file:
                for obj in json.load(oracle_file)["locations"]:
                    for line in obj["lines"]:
                        item = (obj["file"], line)
                        if item in CoveredLines:
                            CoveredFaults.add(item)

            # Read ranking
            with open(f"{getBaselineDir(version)}/ranking.json", "r") as base_file:
                BaselineRanking = json.load(base_file)
                TestLocs.append(BaselineRanking["total"])
            with open(f"{getPAFLDir(version)}/ranking.json", "r") as pafl_file:
                PAFLRanking = json.load(pafl_file)

            # Calculate metrics
            for LineRanking, Total in [
                (BaselineRanking, BaselineTotal),
                (PAFLRanking, PAFLTotal),
            ]:
                FirstRanking, AverageRanking = -1, 0.0
                for line in LineRanking["lines"]:
                    if (line["file"], line["line"]) in CoveredFaults:
                        if FirstRanking == -1:
                            FirstRanking = int(line["ranking"])
                        AverageRanking += int(line["ranking"])
                if FirstRanking == -1:
                    FirstRanking = LineRanking["total"]
                AverageRanking = (
                    AverageRanking / len(CoveredFaults)
                    if len(CoveredFaults) != 0
                    else LineRanking["total"]
                )

                Total["AvgFR"] += FirstRanking
                Total["AvgAR"] += AverageRanking
                Total["Top-1"] += 1 if FirstRanking == 1 else 0
                Total["Top-5"] += 1 if FirstRanking <= 5 else 0
                Total["Top-10"] += 1 if FirstRanking <= 10 else 0

    # Calculate total metrics
    for Total in [BaselineTotal, PAFLTotal]:
        Total["AvgFR"] = Total["AvgFR"] / (len(TestLocs) * 5)
        Total["AvgAR"] = Total["AvgAR"] / (len(TestLocs) * 5)
        Total["Top-1"] = Total["Top-1"] / 5
        Total["Top-5"] = Total["Top-5"] / 5
        Total["Top-10"] = Total["Top-10"] / 5
    AverageTestLoc = sum(TestLocs) / len(TestLocs)

    # Set digits
    AvgTestLocStr = f"{AverageTestLoc:.1f}"
    MethodWidth = 2 + 4 + 1
    MaxDigits = len(AvgTestLocStr)
    # "| MaxDigits/MaxDigits "
    MetricWidth = 2 + MaxDigits + 1 + MaxDigits + 1
    ColumnWidth = max(MethodWidth, MetricWidth)
    ColumnInside = ColumnWidth - 3
    TableWidth = 8 + 2 * ColumnWidth
    Indent = ColumnWidth - MetricWidth
    Indent = " " * Indent if Indent > 0 else ""

    # Print total metrics
    print("\nAverage metrics for 5 iterations:")
    plotEqual(TableWidth)
    print(f"        | {Method:^{ColumnInside}} | {'PAFL':^{ColumnInside}}")
    plotDot(TableWidth)
    print(
        f" Avg FR |{Indent} {BaselineTotal['AvgFR']:>{MaxDigits}.1f}/{AvgTestLocStr} |{Indent} {PAFLTotal['AvgFR']:>{MaxDigits}.1f}/{AvgTestLocStr}"
    )
    print(
        f" Avg AR |{Indent} {BaselineTotal['AvgAR']:>{MaxDigits}.1f}/{AvgTestLocStr} |{Indent} {PAFLTotal['AvgAR']:>{MaxDigits}.1f}/{AvgTestLocStr}"
    )
    for top_k in ["Top-1", "Top-5", "Top-10"]:
        print(
            f" {top_k:<6} | {BaselineTotal[top_k]:>{ColumnInside}.1f} | {PAFLTotal[top_k]:>{ColumnInside}.1f}"
        )
    plotEqual(TableWidth)

    return 0


if __name__ == "__main__":
    main()
