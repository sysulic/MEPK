# Multi-agent Epistemic Planner with Knowledge (MEPK)

A planner for multi-agent epistemic planning based on higher-order belief change.

## Citation

If you use this work in your research, please cite:

```bibtex
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
>

Recently, we proposed two new algorithms for MEPK [code](https://github.com/sysulic/MEPK/releases/tag/new-algos).

If you use these two new algorithms, please cite:

```bibtex
@inproceedings{fang2024heuristic,
  title={Heuristic strategies for accelerating multi-agent epistemic planning},
  author={Fang, Biqing and Lin, Fangzhen},
  booktitle={Proceedings of the International Conference on Principles of Knowledge Representation and Reasoning},
  volume={21},
  number={1},
  pages={339--349},
  year={2024}
}
```


## Introduction

MEPK is a knowledge-based planner implemented in C/C++. It treats a knowledge-base as a state in the search progress, enabling reasoning about multi-agent epistemic states. The planner supports both breadth-first search and heuristic search strategies.

We are developing [MEP Online (Ipv6)](http://[2409:8a55:c4d:f8b0:bd90:8649:dbb6:54a5]:3000/), an interactive platform designed to make MEPK more accessible and easier to understand.

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
