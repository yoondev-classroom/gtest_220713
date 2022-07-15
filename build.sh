#!/bin/sh
g++ $1 -I ./googletest/googletest/include/ -I ./googletest/googlemock/include -pthread -lgtest -L.