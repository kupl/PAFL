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
chmod +x docker/scripts/checkout_bugscpp.sh
docker/scripts/checkout_bugscpp.sh
```

### BugsInPy installation
```sh
git clone https://github.com/soarsmu/BugsInPy.git
```
To download the Python projects used in our experiments, you can run the following script.
```sh
chmod +x docker/scripts/checkout_bugsinpy.sh
docker/scripts/checkout_bugsinpy.sh
```

### Coverage data
We provide pre-executed coverage data to avoid running all test cases: [download link](https://figshare.com/s/1ddbc7dad6d792d1d4dc) (10 GB)\
After downloading from the link, extract the folder `PAFL_coverage` and place it in your **PAFL** directory.
`PAFL_coverage` includes the fault locations oracles, every project's execution on its test suite, and the results of CNN-FL, RNN-FL, MLP-FL, and [Aeneas](https://github.com/ICSE2022FL/ICSE2022FLCode.git)



# Installation
There are two ways to install **PAFL**: 
- building [docker container](#building-docker-container) (recommended)
- [native build](#native-build)

We recommend building a docker container since we provide the scripts for docker to reproduce our experiments.

## Building docker container
```sh
docker build --tag pafl .
docker run --rm -it -v $(pwd):/workspace pafl
```
### `docker build`
| option       | description                           |
| :----------: | :------------------------------------ |
| `--tag pafl` | tag a built image as `pafl`           |
| `.`          | build an image from current directory |
### `docker run`
| option                 | description                                                 |
| :--------------------: | :---------------------------------------------------------- |
| `--rm`                 | remove the container when it stopped                        |
| `-it`                  | enable real-time standard I/O                               |
| `-v $(pwd):/workspace` | mount `$(pwd)` in host machine to `/workspace` in container |
| `pafl`                 | create a container from the `pafl` image                    |


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
|_ PAFL_coverage : consists of test suites, fault locations oracles, DLFL results, and Aeneas results
|_ bugscpp : BugsCpp framework
|_ source : stores buggy versions of the projects

/opt/PAFL
|_ build : consists of build scripts and executable file
|_ profile : stores PAFL models and log files
|_ scripts : consists of scripts for running and evaluating, etc
|_ example : small program for example
|	|_ example : repository
|	|_ test_example : test suites
|	|_ fault.json : fault locations oracle
|_ ...
```

### 1. Caching coverage data (optional)
To reduce the cost of parsing JSON format coverage data every time, you can run the following script.
However, `PAFL_coverage` already has cached coverage data so that you can skip this part.
```sh
scripts/caching.sh
```

### 2. Running PAFL
To run the baseline fault localizer and **PAFL**, you can run the following script.
```sh
# Running SBFL
scripts/run_sbfl.sh
# Running DLFL
scripts/run_dlfl.sh
# Running Aeneas
scripts/run_aeneas.sh
```
We support parallelization using a fixed number of thread pools.
You can specify the number of threads by giving the desired number to the script (default is 1).
```sh
# Running SBFL with 32 threads
scripts/run_sbfl.sh 32
```
Cost reduction from parallelization is most effective when the project contains many source files.

The ranking list of statements is stored in this path: 
- `<test_suite_directory>/__pafl__/<profile>/ranking.json`

If you want to understand details about the commands for running **PAFL**, please read [PAFL Command](#pafl-command).

### 3. Evaluating PAFL
To get the summarized results, you can run the following script.
```sh
# Evaluating SBFL
scripts/eval_sbfl.sh
# Evaluating DLFL
scripts/eval_dlfl.sh
# Evaluating Aeneas
scripts/eval_aeneas.sh
```
The summarized results will be stored in `/workspace/evaluation`

### 4. Checking log files (optional)
Log files are stored in `/opt/pafl/profile`.
You can copy this folder to workspace by running `cp -r /opt/PAFL/profile /workspace`.



# PAFL Command
|     command     | description |
|:---------------:|:------------|
| `help`          | show full description of PAFL command |
| `run-base`      | run baseline fault localizer |
| `run-pafl`      | run PAFL |
| `train`         | train model of profile using fault location oracle |
| `profile`       | create or edit profile |
| `profile-rm`    | delete profile |
| `profile-reset` | delete model of profile (reset model version to 0) |
| `caching`       | cache coverage data of test suite for faster loading |

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
