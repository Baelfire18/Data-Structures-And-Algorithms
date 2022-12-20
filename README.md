# Data-Structures-And-Algorithms

This are the homeworks of [Jose Antonio Castro](https://github.com/Baelfire18) from Data Structures and Algorithms course ([IIC2133](https://github.com/IIC2133-PUC/)) in Pontificia Universidad Catlica de Chile in the semester 2021-1.

| Homework | Content |
| --- | --- |
| [HW0](./HW0/) | Diferent performance between Python and C. |
| [HW1](./HW1/) | Diferent the eficency fo a Max Tree and compare it with a Component Tree. |
| [HW2](./HW2/) | Hash pixels of a photographs. |
| [HW3](./HW3/) | Implement greedy algorithm. |

## Conditions of use

In have a [LICENSE](./LICENSE) for this code and in case you want to use it, you will have to buy me a hamburger or a beer.

## Contact

- Email: `jacastro18@uc.cl`
- Via [issues](https://github.com/Baelfire18/Data-Structures-And-Algorithms/issues).

## Docker

This repository has been also added the feature of been dockerized, eventhougt **it is not strictly necesary for it to work propertly**.

### Docker Set Up

1. Have Docker and docker-compose installed (for WSL2 you can use [this video tutorial](https://www.youtube.com/watch?v=5RQbdMn04Oc) and for macOS you can just install [docker desktop](https://docs.docker.com/desktop/mac/install/)).
2. Run `docker-compose build` (this will take a while).

### Docker Start

This commands you need to run then every time you want to start working in this docker container.

1. Run `docker compose up -d`. (first time will take a while)
2. Run `docker compose run container /bin/bash` (to enter docker):

    Ones inside docker shell:
    - Run `cd ~/volume`.
    - From here you can use the console however you want, to compile, run or use valgrind, python, etc.

## Credits

I was inspired in the docker-compose feature by [rieg-ec](https://github.com/rieg-ec) with his [repository of valgrind-docker](https://github.com/rieg-ec/valgrind-docker).
