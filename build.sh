#!/bin/sh
g++ $1 -I ./googletest/googletest/include/ -pthread -lgtest -L. -DGTEST_LEAK_TEST
