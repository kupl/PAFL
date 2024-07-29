# Benchmark
To reproduce our experiments, you have to install [BugsCpp](https://github.com/Suresoft-GLaDOS/bugscpp.git),
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
`PAFL_coverage` includes the ground truth of fault lines, every project's execution on its test suite, and the result of CNN-FL, RNN-FL, MLP-FL, and [Aeneas](https://github.com/ICSE2022FL/ICSE2022FLCode.git)



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
After installing the benchmark and running the docker container, you are now ready to reproduce our experiments.
The structure of the container is as follows:
```
/workspace
|_ BugsInPy : BugsInPy framework
|_ PAFL_coverage : consists of coverage data, ground truth of fault lines, DLFL and Aeneas result 
|_ bugscpp : BugsCpp framework
|_ source : stores buggy versions of the projects

/opt/PAFL
|_ build : building scripts and executable file
|_ scripts : consists of scripts for running and evaluating
|_ example : samll program for example
|	|_ example : source codes
|	|_ test_example : test result including coverage data
|	|_ fault.json : information of fault locations
|_ ...
```

## Running PAFL

### Caching coverage data

### 

## Evaluating PAFL

## 


# PAFL
PAFL: Project-aware Fault Localization. 
