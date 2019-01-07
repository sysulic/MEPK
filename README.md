# Multi-agent Epistemic Planner Kit
This is a planner for multi-agent epistemic planning. This code is continuously updated. We are planning to release a brand new version of MEPK and more details about it will be presented. You are welcome to follow this work.

###### Original code of IJCAI2017: [A General Multi-agent Epistemic Planner Based on Higher-order Belief Change](https://www.ijcai.org/proceedings/2017/0152.pdf) can be accessed [here](https://github.com/sysulic/MEPK/tree/f778be373903ee0edc47274b0b0757d412359265).


## Introduction
MEPK is implemented in C/C++. It's a knowledge-base based planner which means it treats a knowledge-base as a state in the searching progress. (More details can be found in above paper and a comprehensive introduction will be proposed later)


## Platform
Tested on Ubuntu 18.04 and macOS Mojave.


## Dependencies
[flex/bison](https://www.gnu.org/software/bison/) - for parsing epddl

[expect](http://manpages.ubuntu.com/manpages/trusty/man1/expect.1.html) - for setting timeout


## Compile and Run
Change to the directory `MEPK/src`

* Compile:
```shell
$ make
```

* Run with breadth first search:
  * Run one test case
  ```shell
  $ ./start ../benchmarks/hexa/hexa_domain3.epddl 2
  ```
  * Run all test cases
  ```shell
  $ ./run_with_bfs.sh
  ```
  
* Run with heuristic strategy:
  * Run one test case
  ```shell
  $ ./start ../benchmarks/hexa/hexa_domain3.epddl 0
  ```
  * Run all test cases
  ```shell
  $ ./run_with_heu.sh
  ```
  
* Debug:
```shell
$ ./test ../benchmarks/hexa/hexa_domain3.epddl
```
