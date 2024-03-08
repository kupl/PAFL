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






## BugsCpp

### BugsCpp installation
```sh
git clone https://github.com/Suresoft-GLaDOS/bugscpp.git data/bugscpp
cd data/bugscpp; make install; cd ..; cd ..
```

### Project checkout
```sh
sh data/test_<PROJECT>/checkout.sh
```

### Run PAFL
[After running Docker,](#docker-run)
```sh
sh /workspace/pafl/data/test_<PROJECT>/run.sh
```
