# Benchmark

To reproduce our experiments, you need to install [BugsCpp](https://github.com/Suresoft-GLaDOS/bugscpp.git),
[BugsInPy](https://github.com/soarsmu/BugsInPy.git), and [coverage data](#coverage-data) in your **PAFL** directory.

### BugsCpp installation

```sh
git clone https://github.com/Suresoft-GLaDOS/bugscpp.git
cd bugscpp; make install; cd ..
```

To download the C/C++ projects used in our experiments, you can run the following script.

```sh
scripts/checkout_bugscpp.sh
```

### BugsInPy installation

```sh
git clone https://github.com/soarsmu/BugsInPy.git
```

To download the Python projects used in our experiments, you can run the following script.

```sh
scripts/checkout_bugsinpy.sh
```

### Coverage data

We provide pre-executed coverage data to avoid running all test cases: [download link](https://figshare.com/s/8d82745d78ade3bbab5d) (6.5 GB)\
After downloading from the link, extract the folder `coverage` and place it in `data/` in the **PAFL** directory.
`coverage` includes the fault locations oracles, every project's execution on its test suite, and the results of CNN-FL, RNN-FL, MLP-FL, and [Aeneas](https://github.com/ICSE2022FL/ICSE2022FLCode.git)

# Installation

There are two ways to install **PAFL**:

- building [docker container](#building-docker-container) (recommended)
- [native build](#native-build)

We recommend building a docker container since we provide the scripts for docker to reproduce our experiments.

## Building docker container

```sh
docker build --tag pafl $(pwd)
docker run --rm -it -v $(pwd):/workspace pafl
```

## Native build

### Requirements

`clang>=13` or `clang>=5, gcc>=9`

### CMake stages

1. Generate native build tool
   - `build/cmake.sh`
2. Run the native build tool
   - `build/make.sh`

**PAFL** executable path: `build/release/pafl`

# Reproducing Our Experiments

After installing the benchmark and running the [docker container](#building-docker-container), you are now ready to reproduce our experiments.
Initially, the current working directory is `/workspace`.
The structure of the container is as follows:

```
/workspace
|_ BugsInPy : BugsInPy framework
|_ bugscpp : BugsCpp framework
|_ data
|  |_ source : stores buggy versions of the projects
|  |_ coverage : consists of test suites, fault locations oracles, DLFL results, and Aeneas results
|_ ...

/opt/PAFL
|_ build : consists of build scripts and executable file
|_ profile : stores PAFL models and log files
|_ example : small program for example
|	|_ example : repository
|	|_ test_example : test suites
|	|_ fault.json : fault locations oracle
|_ ...
```

### 2. Running PAFL

To run the baseline fault localizer and **PAFL**, please refer to [manual.pdf](manual.pdf) for detailed information.

If you want to understand details about the commands for running **PAFL**, you can read [PAFL Command](#pafl-command).

### 3. Evaluating PAFL

To get the summarized results, please refer to [manual.pdf](manual.pdf) for detailed information.

### 4. Reusability Guide

To use **PAFL** for your fault localizer, please refer to [manual.pdf](manual.pdf) for detailed information.

# PAFL Command

|     command     | description                                          |
| :-------------: | :--------------------------------------------------- |
|     `help`      | show full description of PAFL command                |
|   `run-base`    | run baseline fault localizer                         |
|   `run-pafl`    | run PAFL                                             |
|     `train`     | train model of profile using fault location oracle   |
|    `profile`    | create or edit profile                               |
|  `profile-rm`   | delete profile                                       |
| `profile-reset` | delete model of profile (reset model version to 0)   |
|    `caching`    | cache coverage data of test suite for faster loading |

### Example command

```sh
# Set profile (language = C++, baseline = ochiai)
pafl profile example-ochiai cpp ochiai

# For version 1 to 5
for i in {1..4}; do
  pafl run-pafl -P example-ochiai -S example/example -T example/test_example/buggy-$i
  pafl train -P example-ochiai -S example/example -T example/test_example/buggy-$i -O example/fault.json
done
pafl run-pafl -P example-ochiai -S example/example -T example/test_example/buggy-5
```
