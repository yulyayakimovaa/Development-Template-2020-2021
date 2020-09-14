# Development-Template-2020-2021
Template for developing and testing C++ programs 

* Build system: cmake
* Tests: gtest
* Code style check: cpplint

## Merging an upstream repository into your fork (master branch)
```
 git checkout master
 git pull https://github.com/UsovaMA/Development-Template.git master
```
## Update working branch
```
 git checkout <your branch>
 git rebase master
```
## Build project with cmake
cmake -G "Visual Studio 15 2017" <path to sourse files>
