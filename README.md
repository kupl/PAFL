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
./main example:cpp 1-3 pafl,ochiai -P/home/minseok/PAFL/my_example/example/ -T/home/minseok/my_example/test_example/ -B/home/minseok/my_example/_bug_info/
```
