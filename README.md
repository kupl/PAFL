# PAFL

## Docker

```sh
docker build --tag pafl .
docker run --rm -it -v $(pwd):/workspace pafl
```

### `docker build`
| option       | description                       |
| :----------: | :-------------------------------- |
| `--tag pafl` | tag a built image as `pafl`       |
| `.`          | build an image from `.` directory |

### `docker run`
| option                 | description                                                 |
| :--------------------: | :---------------------------------------------------------- |
| `--rm`                 | remove the container when it stopped                        |
| `-it`                  | enable real-time standard I/O                               |
| `-v $(pwd):/workspace` | mount `$(pwd)` in host machine to `/workspace` in container |
| `pafl`                 | create a container from the `pafl` image                    |

### example cmd
```sh
pafl -p example -l cpp -m ochiai,dstar,barinel -v 1-3 -d ./example/example -t ./example/test_example -i ./example/oracle --pafl
```






## Benchmark

### BugsCpp installation
```sh
git clone https://github.com/Suresoft-GLaDOS/bugscpp.git data/bugscpp
make -c data/bugscpp install
```

### BugsInPy installation
```sh
git clone https://github.com/soarsmu/BugsInPy data/BugsInPy
```

### Coverage download
[cpp-peglib](https://figshare.com/s/65499d050db11de99b12), [cppcheck](https://figshare.com/s/348a74c2030d400ae277), [Exiv2](https://figshare.com/s/1b3c2268ded5062b991f), [libchewing](https://figshare.com/s/feb7390e029c62fde5ea), [libxml2](https://figshare.com/s/13a02ae2827fcbc50940), [PROJ](https://figshare.com/s/37e71b9e8d759d17ea1d), [OpenSSL](https://figshare.com/s/37e71b9e8d759d17ea1d), [yaml-cpp](https://figshare.com/s/bf13602c72f75a93ed7c), [The Fuck](https://figshare.com/s/cb08995eef9a15590646), [FastAPI](https://figshare.com/s/cb08995eef9a15590646), [spaCy](https://figshare.com/s/4a05ae78a1e83ee7dbf5), [youtube-dl](https://figshare.com/s/bb836f5ed0eef11b1b8e)

### Project checkout
```sh
sh data/<PROJECT>/checkout.sh
```

### Run PAFL
[After running Docker,](#docker)
```sh
sh data/<PROJECT>/run.sh
```

### Evaluation
[After running Docker,](#docker)
```sh
sh data/<PROJECT>/cov_eval.sh
```
