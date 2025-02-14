# Multi-agent Epistemic Planner with Knowledge (MEPK)

A planner for multi-agent epistemic planning based on higher-order belief change.

## Citation

If you use this work in your research, please cite:

```shell
@article{wan2021general,
  title={A general multi-agent epistemic planner based on higher-order belief change},
  author={Wan, Hai and Fang, Biqing and Liu, Yongmei},
  journal={Artificial Intelligence},
  volume={301},
  pages={103562},
  year={2021},
  publisher={Elsevier}
}

```

> The original code from IJCAI 2017 paper ["A General Multi-agent Epistemic Planner Based on Higher-order Belief Change"](https://www.ijcai.org/proceedings/2017/0152.pdf) can be found [here](https://github.com/sysulic/MEPK/tree/f778be373903ee0edc47274b0b0757d412359265).


## Introduction

MEPK is a knowledge-based planner implemented in C/C++. It treats a knowledge-base as a state in the search progress, enabling reasoning about multi-agent epistemic states. The planner supports both breadth-first search and heuristic search strategies.

## System Requirements

### Supported Platforms
- Ubuntu
- macOS

### Dependencies
- [flex/bison](https://www.gnu.org/software/bison/) - For parsing EPDDL files
- [expect](http://manpages.ubuntu.com/manpages/trusty/man1/expect.1.html) - For timeout management

## Getting Started

### Compilation
Navigate to the `MEPK/src` directory and run:

```shell
$ make
```

* Run with breadth first search:
  * Run one test case
  ```shell
  $ ./mepk ../benchmarks/hexa/hexa_domain3.epddl 2
  ```
  * Run all test cases
  ```shell
  $ ./run_with_bfs.sh
  ```
  
* Run with heuristic strategy:
  * Run one test case
  ```shell
  $ ./mepk ../benchmarks/hexa/hexa_domain3.epddl 0
  ```
  * Run all test cases
  ```shell
  $ ./run_with_heu.sh
  ```
  
* Debug:
```shell
$ ./test ../benchmarks/hexa/hexa_domain3.epddl
```
