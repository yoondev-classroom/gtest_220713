# Google Test 설치 방법
```
$ wget https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
$ tar xvf release-1.12.1.tar.gz
$ rm release-1.12.1.tar.gz
$ mv googletest-release-1.12.1/ googletest

# gtest-all.cc
$ g++ ./googletest/googletest/src/gtest-all.cc -c -I./googletest/googletest/include/ -I./googletest/googletest

# main.cpp
$ g++ main.cpp -c -I./googletest/googletest/include/

$ g++ main.o gtest-all.o -pthread

# gtest_main.cc
$ g++ ./googletest/googletest/src/gtest_main.cc -c -I ./googletest/googletest/include/
$ g++ gtest-all.o gtest_main.o -pthread

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gtest_main.o
```

# Google Mock 설치 방법
- gtest-all.cc / gmock-all.cc / gmock_main.cpp
```
# gtest-all.cc
$ g++ ./googletest/googletest/src/gtest-all.cc -c -I./googletest/googletest/include/ -I./googletest/googletest

# gmock-all.cc
$ g++ ./googletest/googlemock/src/gmock-all.cc -c -I ./googletest/googlemock/include/ -I ./googletest/googlemock/ -I ./googletest/googletest/include

# gmock_main.cc
$ g++ ./googletest/googlemock/src/gmock_main.cc -c -I ./googletest/googlemock/include/ -I ./googletest/googletest/include/

# libgtest.a
$ ar rcv libgtest.a gtest-all.o gmock-all.o gmock_main.o

```



1. googletest - xUnit Test Framework
2. googlemock - Test Double
- main의 동작은 거의 변하지 않습니다.
  main을 직접 작성할 필요가 없다면, 테스트 라이브러리에 main을 포함하면 편리합니다.

- 정적 라이브러리: libgtest.a => 권장
  : 실행 파일에 라이브러리의 모든 구현이 포함됩니다.
    - 라이브러리가 변경되면, 실행 파일을 다시 만들어야 합니다.
    - 실행 파일을 옮길 때, 의존성을 고민할 필요가 없습니다.

- 동적 라이브러리: libgtest.so
  : 실행 파일에 라이브러리의 의존성만 포함됩니다.
    실행 파일을 실행할 때 라이브러리를 로드합니다.
    - 라이브러리가 변경되어도, 실행 파일을 다시 만들 필요가 없습니다.
    - 실행 파일과 라이브러리가 모두 포함되어야 합니다.