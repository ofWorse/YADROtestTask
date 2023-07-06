#!/bin/bash

HEADERS='../src/headers/'
CPP='../src/cpp/'

g++ -o test ${HEADERS}file.h ${CPP}file.cpp ${HEADERS}inputProtection.h ${HEADERS}Tape.h ${CPP}Tape.cpp tests.cpp -lgtest -lgtest_main -pthread

