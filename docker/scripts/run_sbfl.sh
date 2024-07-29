#!/bin/bash
if [ -z "$1" ]; then THREAD=1
else THREAD=$1; fi

pafl profile cpp_peglib-ochiai cpp ochiai
pafl profile-reset cpp_peglib-ochiai
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 -O /workspace/PAFL_coverage/cpp_peglib/oracle/8.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 -O /workspace/PAFL_coverage/cpp_peglib/oracle/9.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 -O /workspace/PAFL_coverage/cpp_peglib/oracle/7.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 -O /workspace/PAFL_coverage/cpp_peglib/oracle/6.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 -O /workspace/PAFL_coverage/cpp_peglib/oracle/5.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 -O /workspace/PAFL_coverage/cpp_peglib/oracle/4.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 -O /workspace/PAFL_coverage/cpp_peglib/oracle/2.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 -O /workspace/PAFL_coverage/cpp_peglib/oracle/3.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 --thread $THREAD -c -l
pafl train -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 -O /workspace/PAFL_coverage/cpp_peglib/oracle/1.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-10 -T /workspace/PAFL_coverage/cpp_peglib/buggy-10 -c
pafl run-pafl -P cpp_peglib-ochiai -S /workspace/source/cpp_peglib/buggy-10 -T /workspace/PAFL_coverage/cpp_peglib/buggy-10 --thread $THREAD -c -l

pafl profile cppcheck-ochiai cpp ochiai
pafl profile-reset cppcheck-ochiai
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 -O /workspace/PAFL_coverage/cppcheck/oracle/7.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 -O /workspace/PAFL_coverage/cppcheck/oracle/1.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 -O /workspace/PAFL_coverage/cppcheck/oracle/27.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 -O /workspace/PAFL_coverage/cppcheck/oracle/2.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 -O /workspace/PAFL_coverage/cppcheck/oracle/15.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 -O /workspace/PAFL_coverage/cppcheck/oracle/29.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 -O /workspace/PAFL_coverage/cppcheck/oracle/14.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 -O /workspace/PAFL_coverage/cppcheck/oracle/6.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 -O /workspace/PAFL_coverage/cppcheck/oracle/23.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 -O /workspace/PAFL_coverage/cppcheck/oracle/5.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 -O /workspace/PAFL_coverage/cppcheck/oracle/17.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 -O /workspace/PAFL_coverage/cppcheck/oracle/30.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 -O /workspace/PAFL_coverage/cppcheck/oracle/24.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 -O /workspace/PAFL_coverage/cppcheck/oracle/8.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 -O /workspace/PAFL_coverage/cppcheck/oracle/16.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 -O /workspace/PAFL_coverage/cppcheck/oracle/25.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 -O /workspace/PAFL_coverage/cppcheck/oracle/3.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 -O /workspace/PAFL_coverage/cppcheck/oracle/19.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 -O /workspace/PAFL_coverage/cppcheck/oracle/9.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 -O /workspace/PAFL_coverage/cppcheck/oracle/18.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 -O /workspace/PAFL_coverage/cppcheck/oracle/12.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 -O /workspace/PAFL_coverage/cppcheck/oracle/11.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 -O /workspace/PAFL_coverage/cppcheck/oracle/21.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 -O /workspace/PAFL_coverage/cppcheck/oracle/28.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 -O /workspace/PAFL_coverage/cppcheck/oracle/13.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 -O /workspace/PAFL_coverage/cppcheck/oracle/20.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 -O /workspace/PAFL_coverage/cppcheck/oracle/22.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 -O /workspace/PAFL_coverage/cppcheck/oracle/4.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 --thread $THREAD -c -l
pafl train -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 -O /workspace/PAFL_coverage/cppcheck/oracle/26.json --thread $THREAD -c -l
pafl run-base -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-10 -T /workspace/PAFL_coverage/cppcheck/buggy-10 -c
pafl run-pafl -P cppcheck-ochiai -S /workspace/source/cppcheck/buggy-10 -T /workspace/PAFL_coverage/cppcheck/buggy-10 --thread $THREAD -c -l

pafl profile exiv2-ochiai cpp ochiai
pafl profile-reset exiv2-ochiai
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 -O /workspace/PAFL_coverage/exiv2/oracle/10.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 -O /workspace/PAFL_coverage/exiv2/oracle/15.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 -O /workspace/PAFL_coverage/exiv2/oracle/14.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 -O /workspace/PAFL_coverage/exiv2/oracle/4.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 -O /workspace/PAFL_coverage/exiv2/oracle/13.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 -O /workspace/PAFL_coverage/exiv2/oracle/6.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 -O /workspace/PAFL_coverage/exiv2/oracle/8.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 -O /workspace/PAFL_coverage/exiv2/oracle/9.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 -O /workspace/PAFL_coverage/exiv2/oracle/11.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 -O /workspace/PAFL_coverage/exiv2/oracle/12.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 -O /workspace/PAFL_coverage/exiv2/oracle/7.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 -O /workspace/PAFL_coverage/exiv2/oracle/5.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 -O /workspace/PAFL_coverage/exiv2/oracle/16.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 -O /workspace/PAFL_coverage/exiv2/oracle/17.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 -O /workspace/PAFL_coverage/exiv2/oracle/3.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 -O /workspace/PAFL_coverage/exiv2/oracle/2.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 -O /workspace/PAFL_coverage/exiv2/oracle/1.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 -O /workspace/PAFL_coverage/exiv2/oracle/18.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 --thread $THREAD -c -l
pafl train -P exiv2-ochiai -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 -O /workspace/PAFL_coverage/exiv2/oracle/19.json --thread $THREAD -c -l
pafl run-base -P exiv2-ochiai -S /workspace/source/exiv2/buggy-20 -T /workspace/PAFL_coverage/exiv2/buggy-20 -c
pafl run-pafl -P exiv2-ochiai -S /workspace/source/exiv2/buggy-20 -T /workspace/PAFL_coverage/exiv2/buggy-20 --thread $THREAD -c -l

pafl profile libchewing-ochiai cpp ochiai
pafl profile-reset libchewing-ochiai
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 --thread $THREAD -c -l
pafl train -P libchewing-ochiai -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 -O /workspace/PAFL_coverage/libchewing/oracle/6.json --thread $THREAD -c -l
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 --thread $THREAD -c -l
pafl train -P libchewing-ochiai -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 -O /workspace/PAFL_coverage/libchewing/oracle/8.json --thread $THREAD -c -l
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 --thread $THREAD -c -l
pafl train -P libchewing-ochiai -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 -O /workspace/PAFL_coverage/libchewing/oracle/3.json --thread $THREAD -c -l
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 --thread $THREAD -c -l
pafl train -P libchewing-ochiai -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 -O /workspace/PAFL_coverage/libchewing/oracle/4.json --thread $THREAD -c -l
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 --thread $THREAD -c -l
pafl train -P libchewing-ochiai -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 -O /workspace/PAFL_coverage/libchewing/oracle/5.json --thread $THREAD -c -l
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 --thread $THREAD -c -l
pafl train -P libchewing-ochiai -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 -O /workspace/PAFL_coverage/libchewing/oracle/7.json --thread $THREAD -c -l
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 --thread $THREAD -c -l
pafl train -P libchewing-ochiai -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 -O /workspace/PAFL_coverage/libchewing/oracle/2.json --thread $THREAD -c -l
pafl run-base -P libchewing-ochiai -S /workspace/source/libchewing/buggy-1 -T /workspace/PAFL_coverage/libchewing/buggy-1 -c
pafl run-pafl -P libchewing-ochiai -S /workspace/source/libchewing/buggy-1 -T /workspace/PAFL_coverage/libchewing/buggy-1 --thread $THREAD -c -l

pafl profile libxml2-ochiai cpp ochiai
pafl profile-reset libxml2-ochiai
pafl run-base -P libxml2-ochiai -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 -c
pafl run-pafl -P libxml2-ochiai -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 --thread $THREAD -c -l
pafl train -P libxml2-ochiai -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 -O /workspace/PAFL_coverage/libxml2/oracle/4.json --thread $THREAD -c -l
pafl run-base -P libxml2-ochiai -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 -c
pafl run-pafl -P libxml2-ochiai -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 --thread $THREAD -c -l
pafl train -P libxml2-ochiai -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 -O /workspace/PAFL_coverage/libxml2/oracle/7.json --thread $THREAD -c -l
pafl run-base -P libxml2-ochiai -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 -c
pafl run-pafl -P libxml2-ochiai -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 --thread $THREAD -c -l
pafl train -P libxml2-ochiai -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 -O /workspace/PAFL_coverage/libxml2/oracle/1.json --thread $THREAD -c -l
pafl run-base -P libxml2-ochiai -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 -c
pafl run-pafl -P libxml2-ochiai -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 --thread $THREAD -c -l
pafl train -P libxml2-ochiai -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 -O /workspace/PAFL_coverage/libxml2/oracle/2.json --thread $THREAD -c -l
pafl run-base -P libxml2-ochiai -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 -c
pafl run-pafl -P libxml2-ochiai -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 --thread $THREAD -c -l
pafl train -P libxml2-ochiai -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 -O /workspace/PAFL_coverage/libxml2/oracle/3.json --thread $THREAD -c -l
pafl run-base -P libxml2-ochiai -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 -c
pafl run-pafl -P libxml2-ochiai -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 --thread $THREAD -c -l
pafl train -P libxml2-ochiai -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 -O /workspace/PAFL_coverage/libxml2/oracle/5.json --thread $THREAD -c -l
pafl run-base -P libxml2-ochiai -S /workspace/source/libxml2/buggy-6 -T /workspace/PAFL_coverage/libxml2/buggy-6 -c
pafl run-pafl -P libxml2-ochiai -S /workspace/source/libxml2/buggy-6 -T /workspace/PAFL_coverage/libxml2/buggy-6 --thread $THREAD -c -l

pafl profile proj-ochiai cpp ochiai
pafl profile-reset proj-ochiai
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 -O /workspace/PAFL_coverage/proj/oracle/24.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 -O /workspace/PAFL_coverage/proj/oracle/8.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 -O /workspace/PAFL_coverage/proj/oracle/13.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 -O /workspace/PAFL_coverage/proj/oracle/12.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 -O /workspace/PAFL_coverage/proj/oracle/11.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 -O /workspace/PAFL_coverage/proj/oracle/21.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 -O /workspace/PAFL_coverage/proj/oracle/22.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 -O /workspace/PAFL_coverage/proj/oracle/9.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 -O /workspace/PAFL_coverage/proj/oracle/18.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 -O /workspace/PAFL_coverage/proj/oracle/16.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 -O /workspace/PAFL_coverage/proj/oracle/1.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 -O /workspace/PAFL_coverage/proj/oracle/3.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 -O /workspace/PAFL_coverage/proj/oracle/17.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 -O /workspace/PAFL_coverage/proj/oracle/2.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 -O /workspace/PAFL_coverage/proj/oracle/4.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 -O /workspace/PAFL_coverage/proj/oracle/19.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 -O /workspace/PAFL_coverage/proj/oracle/10.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 -O /workspace/PAFL_coverage/proj/oracle/6.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 -O /workspace/PAFL_coverage/proj/oracle/20.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 -O /workspace/PAFL_coverage/proj/oracle/5.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 -O /workspace/PAFL_coverage/proj/oracle/27.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 -O /workspace/PAFL_coverage/proj/oracle/23.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 -O /workspace/PAFL_coverage/proj/oracle/14.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 -O /workspace/PAFL_coverage/proj/oracle/28.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 -O /workspace/PAFL_coverage/proj/oracle/15.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 -O /workspace/PAFL_coverage/proj/oracle/7.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 --thread $THREAD -c -l
pafl train -P proj-ochiai -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 -O /workspace/PAFL_coverage/proj/oracle/26.json --thread $THREAD -c -l
pafl run-base -P proj-ochiai -S /workspace/source/proj/buggy-25 -T /workspace/PAFL_coverage/proj/buggy-25 -c
pafl run-pafl -P proj-ochiai -S /workspace/source/proj/buggy-25 -T /workspace/PAFL_coverage/proj/buggy-25 --thread $THREAD -c -l

pafl profile openssl-ochiai cpp ochiai
pafl profile-reset openssl-ochiai
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 -O /workspace/PAFL_coverage/openssl/oracle/13.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 -O /workspace/PAFL_coverage/openssl/oracle/1.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 -O /workspace/PAFL_coverage/openssl/oracle/2.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 -O /workspace/PAFL_coverage/openssl/oracle/9.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 -O /workspace/PAFL_coverage/openssl/oracle/12.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 -O /workspace/PAFL_coverage/openssl/oracle/19.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 -O /workspace/PAFL_coverage/openssl/oracle/14.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 -O /workspace/PAFL_coverage/openssl/oracle/28.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 -O /workspace/PAFL_coverage/openssl/oracle/11.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 -O /workspace/PAFL_coverage/openssl/oracle/15.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 -O /workspace/PAFL_coverage/openssl/oracle/5.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 -O /workspace/PAFL_coverage/openssl/oracle/18.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 -O /workspace/PAFL_coverage/openssl/oracle/16.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 -O /workspace/PAFL_coverage/openssl/oracle/22.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 -O /workspace/PAFL_coverage/openssl/oracle/10.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 -O /workspace/PAFL_coverage/openssl/oracle/23.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 -O /workspace/PAFL_coverage/openssl/oracle/26.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 -O /workspace/PAFL_coverage/openssl/oracle/24.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 -O /workspace/PAFL_coverage/openssl/oracle/25.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 -O /workspace/PAFL_coverage/openssl/oracle/17.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 -O /workspace/PAFL_coverage/openssl/oracle/6.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 -O /workspace/PAFL_coverage/openssl/oracle/4.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 -O /workspace/PAFL_coverage/openssl/oracle/7.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 -O /workspace/PAFL_coverage/openssl/oracle/27.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 --thread $THREAD -c -l
pafl train -P openssl-ochiai -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 -O /workspace/PAFL_coverage/openssl/oracle/20.json --thread $THREAD -c -l
pafl run-base -P openssl-ochiai -S /workspace/source/openssl/buggy-21 -T /workspace/PAFL_coverage/openssl/buggy-21 -c
pafl run-pafl -P openssl-ochiai -S /workspace/source/openssl/buggy-21 -T /workspace/PAFL_coverage/openssl/buggy-21 --thread $THREAD -c -l

pafl profile yaml_cpp-ochiai cpp ochiai
pafl profile-reset yaml_cpp-ochiai
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 -O /workspace/PAFL_coverage/yaml_cpp/oracle/10.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 -O /workspace/PAFL_coverage/yaml_cpp/oracle/1.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 -O /workspace/PAFL_coverage/yaml_cpp/oracle/2.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 -O /workspace/PAFL_coverage/yaml_cpp/oracle/3.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 -O /workspace/PAFL_coverage/yaml_cpp/oracle/4.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 -O /workspace/PAFL_coverage/yaml_cpp/oracle/5.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 -O /workspace/PAFL_coverage/yaml_cpp/oracle/6.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 -O /workspace/PAFL_coverage/yaml_cpp/oracle/7.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 --thread $THREAD -c -l
pafl train -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 -O /workspace/PAFL_coverage/yaml_cpp/oracle/8.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-9 -T /workspace/PAFL_coverage/yaml_cpp/buggy-9 -c
pafl run-pafl -P yaml_cpp-ochiai -S /workspace/source/yaml_cpp/buggy-9 -T /workspace/PAFL_coverage/yaml_cpp/buggy-9 --thread $THREAD -c -l

pafl profile thefuck-ochiai python ochiai
pafl profile-reset thefuck-ochiai
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 -O /workspace/PAFL_coverage/thefuck/oracle/32.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 -O /workspace/PAFL_coverage/thefuck/oracle/31.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 -O /workspace/PAFL_coverage/thefuck/oracle/30.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 -O /workspace/PAFL_coverage/thefuck/oracle/29.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 -O /workspace/PAFL_coverage/thefuck/oracle/28.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 -O /workspace/PAFL_coverage/thefuck/oracle/27.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 -O /workspace/PAFL_coverage/thefuck/oracle/26.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 -O /workspace/PAFL_coverage/thefuck/oracle/25.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 -O /workspace/PAFL_coverage/thefuck/oracle/24.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 -O /workspace/PAFL_coverage/thefuck/oracle/23.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 -O /workspace/PAFL_coverage/thefuck/oracle/22.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 -O /workspace/PAFL_coverage/thefuck/oracle/21.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 -O /workspace/PAFL_coverage/thefuck/oracle/20.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 -O /workspace/PAFL_coverage/thefuck/oracle/19.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 -O /workspace/PAFL_coverage/thefuck/oracle/18.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 -O /workspace/PAFL_coverage/thefuck/oracle/17.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 -O /workspace/PAFL_coverage/thefuck/oracle/16.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 -O /workspace/PAFL_coverage/thefuck/oracle/15.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 -O /workspace/PAFL_coverage/thefuck/oracle/14.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 -O /workspace/PAFL_coverage/thefuck/oracle/13.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 -O /workspace/PAFL_coverage/thefuck/oracle/11.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 -O /workspace/PAFL_coverage/thefuck/oracle/10.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 -O /workspace/PAFL_coverage/thefuck/oracle/9.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 -O /workspace/PAFL_coverage/thefuck/oracle/8.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 -O /workspace/PAFL_coverage/thefuck/oracle/7.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 -O /workspace/PAFL_coverage/thefuck/oracle/6.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 -O /workspace/PAFL_coverage/thefuck/oracle/5.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 -O /workspace/PAFL_coverage/thefuck/oracle/4.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 -O /workspace/PAFL_coverage/thefuck/oracle/3.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 --thread $THREAD -c -l
pafl train -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 -O /workspace/PAFL_coverage/thefuck/oracle/2.json --thread $THREAD -c -l
pafl run-base -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-1/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-1 -c
pafl run-pafl -P thefuck-ochiai -S /workspace/source/thefuck/thefuck-1/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-1 --thread $THREAD -c -l

pafl profile fastapi-ochiai python ochiai
pafl profile-reset fastapi-ochiai
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 -O /workspace/PAFL_coverage/fastapi/oracle/16.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 -O /workspace/PAFL_coverage/fastapi/oracle/15.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 -O /workspace/PAFL_coverage/fastapi/oracle/14.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 -O /workspace/PAFL_coverage/fastapi/oracle/13.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 -O /workspace/PAFL_coverage/fastapi/oracle/12.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 -O /workspace/PAFL_coverage/fastapi/oracle/11.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 -O /workspace/PAFL_coverage/fastapi/oracle/10.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 -O /workspace/PAFL_coverage/fastapi/oracle/9.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 -O /workspace/PAFL_coverage/fastapi/oracle/8.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 -O /workspace/PAFL_coverage/fastapi/oracle/7.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 -O /workspace/PAFL_coverage/fastapi/oracle/6.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 -O /workspace/PAFL_coverage/fastapi/oracle/5.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 -O /workspace/PAFL_coverage/fastapi/oracle/4.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 --thread $THREAD -c -l
pafl train -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 -O /workspace/PAFL_coverage/fastapi/oracle/3.json --thread $THREAD -c -l
pafl run-base -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-2/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-2 -c
pafl run-pafl -P fastapi-ochiai -S /workspace/source/fastapi/fastapi-2/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-2 --thread $THREAD -c -l

pafl profile spacy-ochiai python ochiai
pafl profile-reset spacy-ochiai
pafl run-base -P spacy-ochiai -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 -c
pafl run-pafl -P spacy-ochiai -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 --thread $THREAD -c -l
pafl train -P spacy-ochiai -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 -O /workspace/PAFL_coverage/spacy/oracle/7.json --thread $THREAD -c -l
pafl run-base -P spacy-ochiai -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 -c
pafl run-pafl -P spacy-ochiai -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 --thread $THREAD -c -l
pafl train -P spacy-ochiai -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 -O /workspace/PAFL_coverage/spacy/oracle/6.json --thread $THREAD -c -l
pafl run-base -P spacy-ochiai -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 -c
pafl run-pafl -P spacy-ochiai -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 --thread $THREAD -c -l
pafl train -P spacy-ochiai -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 -O /workspace/PAFL_coverage/spacy/oracle/5.json --thread $THREAD -c -l
pafl run-base -P spacy-ochiai -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 -c
pafl run-pafl -P spacy-ochiai -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 --thread $THREAD -c -l
pafl train -P spacy-ochiai -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 -O /workspace/PAFL_coverage/spacy/oracle/4.json --thread $THREAD -c -l
pafl run-base -P spacy-ochiai -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 -c
pafl run-pafl -P spacy-ochiai -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 --thread $THREAD -c -l
pafl train -P spacy-ochiai -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 -O /workspace/PAFL_coverage/spacy/oracle/3.json --thread $THREAD -c -l
pafl run-base -P spacy-ochiai -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 -c
pafl run-pafl -P spacy-ochiai -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 --thread $THREAD -c -l
pafl train -P spacy-ochiai -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 -O /workspace/PAFL_coverage/spacy/oracle/2.json --thread $THREAD -c -l
pafl run-base -P spacy-ochiai -S /workspace/source/spacy/spacy-1/spacy -T /workspace/PAFL_coverage/spacy/buggy-1 -c
pafl run-pafl -P spacy-ochiai -S /workspace/source/spacy/spacy-1/spacy -T /workspace/PAFL_coverage/spacy/buggy-1 --thread $THREAD -c -l

pafl profile youtube-dl-ochiai python ochiai
pafl profile-reset youtube-dl-ochiai
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 -O /workspace/PAFL_coverage/youtube-dl/oracle/35.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 -O /workspace/PAFL_coverage/youtube-dl/oracle/34.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 -O /workspace/PAFL_coverage/youtube-dl/oracle/33.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 -O /workspace/PAFL_coverage/youtube-dl/oracle/32.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 -O /workspace/PAFL_coverage/youtube-dl/oracle/31.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 -O /workspace/PAFL_coverage/youtube-dl/oracle/10.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 -O /workspace/PAFL_coverage/youtube-dl/oracle/9.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 -O /workspace/PAFL_coverage/youtube-dl/oracle/8.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 -O /workspace/PAFL_coverage/youtube-dl/oracle/30.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 -O /workspace/PAFL_coverage/youtube-dl/oracle/7.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 -O /workspace/PAFL_coverage/youtube-dl/oracle/29.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 -O /workspace/PAFL_coverage/youtube-dl/oracle/28.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 -O /workspace/PAFL_coverage/youtube-dl/oracle/6.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 -O /workspace/PAFL_coverage/youtube-dl/oracle/27.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 -O /workspace/PAFL_coverage/youtube-dl/oracle/26.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 -O /workspace/PAFL_coverage/youtube-dl/oracle/5.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 -O /workspace/PAFL_coverage/youtube-dl/oracle/25.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 -O /workspace/PAFL_coverage/youtube-dl/oracle/24.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 -O /workspace/PAFL_coverage/youtube-dl/oracle/23.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 -O /workspace/PAFL_coverage/youtube-dl/oracle/22.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 -O /workspace/PAFL_coverage/youtube-dl/oracle/21.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 -O /workspace/PAFL_coverage/youtube-dl/oracle/20.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 -O /workspace/PAFL_coverage/youtube-dl/oracle/19.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 -O /workspace/PAFL_coverage/youtube-dl/oracle/18.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 -O /workspace/PAFL_coverage/youtube-dl/oracle/3.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 -O /workspace/PAFL_coverage/youtube-dl/oracle/16.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 -O /workspace/PAFL_coverage/youtube-dl/oracle/2.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 -O /workspace/PAFL_coverage/youtube-dl/oracle/15.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 -O /workspace/PAFL_coverage/youtube-dl/oracle/1.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 -O /workspace/PAFL_coverage/youtube-dl/oracle/13.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 --thread $THREAD -c -l
pafl train -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 -O /workspace/PAFL_coverage/youtube-dl/oracle/12.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-11/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-11 -c
pafl run-pafl -P youtube-dl-ochiai -S /workspace/source/youtube-dl/youtube-dl-11/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-11 --thread $THREAD -c -l

pafl profile cpp_peglib-dstar cpp dstar
pafl profile-reset cpp_peglib-dstar
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 -O /workspace/PAFL_coverage/cpp_peglib/oracle/8.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 -O /workspace/PAFL_coverage/cpp_peglib/oracle/9.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 -O /workspace/PAFL_coverage/cpp_peglib/oracle/7.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 -O /workspace/PAFL_coverage/cpp_peglib/oracle/6.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 -O /workspace/PAFL_coverage/cpp_peglib/oracle/5.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 -O /workspace/PAFL_coverage/cpp_peglib/oracle/4.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 -O /workspace/PAFL_coverage/cpp_peglib/oracle/2.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 -O /workspace/PAFL_coverage/cpp_peglib/oracle/3.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 --thread $THREAD -c -l
pafl train -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 -O /workspace/PAFL_coverage/cpp_peglib/oracle/1.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-10 -T /workspace/PAFL_coverage/cpp_peglib/buggy-10 -c
pafl run-pafl -P cpp_peglib-dstar -S /workspace/source/cpp_peglib/buggy-10 -T /workspace/PAFL_coverage/cpp_peglib/buggy-10 --thread $THREAD -c -l

pafl profile cppcheck-dstar cpp dstar
pafl profile-reset cppcheck-dstar
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 -O /workspace/PAFL_coverage/cppcheck/oracle/7.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 -O /workspace/PAFL_coverage/cppcheck/oracle/1.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 -O /workspace/PAFL_coverage/cppcheck/oracle/27.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 -O /workspace/PAFL_coverage/cppcheck/oracle/2.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 -O /workspace/PAFL_coverage/cppcheck/oracle/15.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 -O /workspace/PAFL_coverage/cppcheck/oracle/29.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 -O /workspace/PAFL_coverage/cppcheck/oracle/14.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 -O /workspace/PAFL_coverage/cppcheck/oracle/6.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 -O /workspace/PAFL_coverage/cppcheck/oracle/23.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 -O /workspace/PAFL_coverage/cppcheck/oracle/5.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 -O /workspace/PAFL_coverage/cppcheck/oracle/17.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 -O /workspace/PAFL_coverage/cppcheck/oracle/30.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 -O /workspace/PAFL_coverage/cppcheck/oracle/24.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 -O /workspace/PAFL_coverage/cppcheck/oracle/8.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 -O /workspace/PAFL_coverage/cppcheck/oracle/16.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 -O /workspace/PAFL_coverage/cppcheck/oracle/25.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 -O /workspace/PAFL_coverage/cppcheck/oracle/3.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 -O /workspace/PAFL_coverage/cppcheck/oracle/19.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 -O /workspace/PAFL_coverage/cppcheck/oracle/9.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 -O /workspace/PAFL_coverage/cppcheck/oracle/18.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 -O /workspace/PAFL_coverage/cppcheck/oracle/12.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 -O /workspace/PAFL_coverage/cppcheck/oracle/11.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 -O /workspace/PAFL_coverage/cppcheck/oracle/21.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 -O /workspace/PAFL_coverage/cppcheck/oracle/28.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 -O /workspace/PAFL_coverage/cppcheck/oracle/13.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 -O /workspace/PAFL_coverage/cppcheck/oracle/20.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 -O /workspace/PAFL_coverage/cppcheck/oracle/22.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 -O /workspace/PAFL_coverage/cppcheck/oracle/4.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 --thread $THREAD -c -l
pafl train -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 -O /workspace/PAFL_coverage/cppcheck/oracle/26.json --thread $THREAD -c -l
pafl run-base -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-10 -T /workspace/PAFL_coverage/cppcheck/buggy-10 -c
pafl run-pafl -P cppcheck-dstar -S /workspace/source/cppcheck/buggy-10 -T /workspace/PAFL_coverage/cppcheck/buggy-10 --thread $THREAD -c -l

pafl profile exiv2-dstar cpp dstar
pafl profile-reset exiv2-dstar
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 -O /workspace/PAFL_coverage/exiv2/oracle/10.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 -O /workspace/PAFL_coverage/exiv2/oracle/15.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 -O /workspace/PAFL_coverage/exiv2/oracle/14.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 -O /workspace/PAFL_coverage/exiv2/oracle/4.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 -O /workspace/PAFL_coverage/exiv2/oracle/13.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 -O /workspace/PAFL_coverage/exiv2/oracle/6.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 -O /workspace/PAFL_coverage/exiv2/oracle/8.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 -O /workspace/PAFL_coverage/exiv2/oracle/9.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 -O /workspace/PAFL_coverage/exiv2/oracle/11.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 -O /workspace/PAFL_coverage/exiv2/oracle/12.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 -O /workspace/PAFL_coverage/exiv2/oracle/7.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 -O /workspace/PAFL_coverage/exiv2/oracle/5.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 -O /workspace/PAFL_coverage/exiv2/oracle/16.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 -O /workspace/PAFL_coverage/exiv2/oracle/17.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 -O /workspace/PAFL_coverage/exiv2/oracle/3.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 -O /workspace/PAFL_coverage/exiv2/oracle/2.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 -O /workspace/PAFL_coverage/exiv2/oracle/1.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 -O /workspace/PAFL_coverage/exiv2/oracle/18.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 --thread $THREAD -c -l
pafl train -P exiv2-dstar -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 -O /workspace/PAFL_coverage/exiv2/oracle/19.json --thread $THREAD -c -l
pafl run-base -P exiv2-dstar -S /workspace/source/exiv2/buggy-20 -T /workspace/PAFL_coverage/exiv2/buggy-20 -c
pafl run-pafl -P exiv2-dstar -S /workspace/source/exiv2/buggy-20 -T /workspace/PAFL_coverage/exiv2/buggy-20 --thread $THREAD -c -l

pafl profile libchewing-dstar cpp dstar
pafl profile-reset libchewing-dstar
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 --thread $THREAD -c -l
pafl train -P libchewing-dstar -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 -O /workspace/PAFL_coverage/libchewing/oracle/6.json --thread $THREAD -c -l
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 --thread $THREAD -c -l
pafl train -P libchewing-dstar -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 -O /workspace/PAFL_coverage/libchewing/oracle/8.json --thread $THREAD -c -l
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 --thread $THREAD -c -l
pafl train -P libchewing-dstar -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 -O /workspace/PAFL_coverage/libchewing/oracle/3.json --thread $THREAD -c -l
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 --thread $THREAD -c -l
pafl train -P libchewing-dstar -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 -O /workspace/PAFL_coverage/libchewing/oracle/4.json --thread $THREAD -c -l
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 --thread $THREAD -c -l
pafl train -P libchewing-dstar -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 -O /workspace/PAFL_coverage/libchewing/oracle/5.json --thread $THREAD -c -l
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 --thread $THREAD -c -l
pafl train -P libchewing-dstar -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 -O /workspace/PAFL_coverage/libchewing/oracle/7.json --thread $THREAD -c -l
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 --thread $THREAD -c -l
pafl train -P libchewing-dstar -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 -O /workspace/PAFL_coverage/libchewing/oracle/2.json --thread $THREAD -c -l
pafl run-base -P libchewing-dstar -S /workspace/source/libchewing/buggy-1 -T /workspace/PAFL_coverage/libchewing/buggy-1 -c
pafl run-pafl -P libchewing-dstar -S /workspace/source/libchewing/buggy-1 -T /workspace/PAFL_coverage/libchewing/buggy-1 --thread $THREAD -c -l

pafl profile libxml2-dstar cpp dstar
pafl profile-reset libxml2-dstar
pafl run-base -P libxml2-dstar -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 -c
pafl run-pafl -P libxml2-dstar -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 --thread $THREAD -c -l
pafl train -P libxml2-dstar -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 -O /workspace/PAFL_coverage/libxml2/oracle/4.json --thread $THREAD -c -l
pafl run-base -P libxml2-dstar -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 -c
pafl run-pafl -P libxml2-dstar -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 --thread $THREAD -c -l
pafl train -P libxml2-dstar -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 -O /workspace/PAFL_coverage/libxml2/oracle/7.json --thread $THREAD -c -l
pafl run-base -P libxml2-dstar -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 -c
pafl run-pafl -P libxml2-dstar -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 --thread $THREAD -c -l
pafl train -P libxml2-dstar -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 -O /workspace/PAFL_coverage/libxml2/oracle/1.json --thread $THREAD -c -l
pafl run-base -P libxml2-dstar -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 -c
pafl run-pafl -P libxml2-dstar -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 --thread $THREAD -c -l
pafl train -P libxml2-dstar -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 -O /workspace/PAFL_coverage/libxml2/oracle/2.json --thread $THREAD -c -l
pafl run-base -P libxml2-dstar -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 -c
pafl run-pafl -P libxml2-dstar -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 --thread $THREAD -c -l
pafl train -P libxml2-dstar -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 -O /workspace/PAFL_coverage/libxml2/oracle/3.json --thread $THREAD -c -l
pafl run-base -P libxml2-dstar -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 -c
pafl run-pafl -P libxml2-dstar -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 --thread $THREAD -c -l
pafl train -P libxml2-dstar -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 -O /workspace/PAFL_coverage/libxml2/oracle/5.json --thread $THREAD -c -l
pafl run-base -P libxml2-dstar -S /workspace/source/libxml2/buggy-6 -T /workspace/PAFL_coverage/libxml2/buggy-6 -c
pafl run-pafl -P libxml2-dstar -S /workspace/source/libxml2/buggy-6 -T /workspace/PAFL_coverage/libxml2/buggy-6 --thread $THREAD -c -l

pafl profile proj-dstar cpp dstar
pafl profile-reset proj-dstar
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 -O /workspace/PAFL_coverage/proj/oracle/24.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 -O /workspace/PAFL_coverage/proj/oracle/8.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 -O /workspace/PAFL_coverage/proj/oracle/13.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 -O /workspace/PAFL_coverage/proj/oracle/12.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 -O /workspace/PAFL_coverage/proj/oracle/11.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 -O /workspace/PAFL_coverage/proj/oracle/21.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 -O /workspace/PAFL_coverage/proj/oracle/22.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 -O /workspace/PAFL_coverage/proj/oracle/9.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 -O /workspace/PAFL_coverage/proj/oracle/18.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 -O /workspace/PAFL_coverage/proj/oracle/16.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 -O /workspace/PAFL_coverage/proj/oracle/1.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 -O /workspace/PAFL_coverage/proj/oracle/3.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 -O /workspace/PAFL_coverage/proj/oracle/17.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 -O /workspace/PAFL_coverage/proj/oracle/2.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 -O /workspace/PAFL_coverage/proj/oracle/4.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 -O /workspace/PAFL_coverage/proj/oracle/19.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 -O /workspace/PAFL_coverage/proj/oracle/10.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 -O /workspace/PAFL_coverage/proj/oracle/6.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 -O /workspace/PAFL_coverage/proj/oracle/20.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 -O /workspace/PAFL_coverage/proj/oracle/5.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 -O /workspace/PAFL_coverage/proj/oracle/27.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 -O /workspace/PAFL_coverage/proj/oracle/23.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 -O /workspace/PAFL_coverage/proj/oracle/14.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 -O /workspace/PAFL_coverage/proj/oracle/28.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 -O /workspace/PAFL_coverage/proj/oracle/15.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 -O /workspace/PAFL_coverage/proj/oracle/7.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 --thread $THREAD -c -l
pafl train -P proj-dstar -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 -O /workspace/PAFL_coverage/proj/oracle/26.json --thread $THREAD -c -l
pafl run-base -P proj-dstar -S /workspace/source/proj/buggy-25 -T /workspace/PAFL_coverage/proj/buggy-25 -c
pafl run-pafl -P proj-dstar -S /workspace/source/proj/buggy-25 -T /workspace/PAFL_coverage/proj/buggy-25 --thread $THREAD -c -l

pafl profile openssl-dstar cpp dstar
pafl profile-reset openssl-dstar
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 -O /workspace/PAFL_coverage/openssl/oracle/13.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 -O /workspace/PAFL_coverage/openssl/oracle/1.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 -O /workspace/PAFL_coverage/openssl/oracle/2.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 -O /workspace/PAFL_coverage/openssl/oracle/9.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 -O /workspace/PAFL_coverage/openssl/oracle/12.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 -O /workspace/PAFL_coverage/openssl/oracle/19.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 -O /workspace/PAFL_coverage/openssl/oracle/14.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 -O /workspace/PAFL_coverage/openssl/oracle/28.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 -O /workspace/PAFL_coverage/openssl/oracle/11.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 -O /workspace/PAFL_coverage/openssl/oracle/15.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 -O /workspace/PAFL_coverage/openssl/oracle/5.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 -O /workspace/PAFL_coverage/openssl/oracle/18.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 -O /workspace/PAFL_coverage/openssl/oracle/16.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 -O /workspace/PAFL_coverage/openssl/oracle/22.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 -O /workspace/PAFL_coverage/openssl/oracle/10.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 -O /workspace/PAFL_coverage/openssl/oracle/23.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 -O /workspace/PAFL_coverage/openssl/oracle/26.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 -O /workspace/PAFL_coverage/openssl/oracle/24.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 -O /workspace/PAFL_coverage/openssl/oracle/25.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 -O /workspace/PAFL_coverage/openssl/oracle/17.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 -O /workspace/PAFL_coverage/openssl/oracle/6.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 -O /workspace/PAFL_coverage/openssl/oracle/4.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 -O /workspace/PAFL_coverage/openssl/oracle/7.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 -O /workspace/PAFL_coverage/openssl/oracle/27.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 --thread $THREAD -c -l
pafl train -P openssl-dstar -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 -O /workspace/PAFL_coverage/openssl/oracle/20.json --thread $THREAD -c -l
pafl run-base -P openssl-dstar -S /workspace/source/openssl/buggy-21 -T /workspace/PAFL_coverage/openssl/buggy-21 -c
pafl run-pafl -P openssl-dstar -S /workspace/source/openssl/buggy-21 -T /workspace/PAFL_coverage/openssl/buggy-21 --thread $THREAD -c -l

pafl profile yaml_cpp-dstar cpp dstar
pafl profile-reset yaml_cpp-dstar
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 -O /workspace/PAFL_coverage/yaml_cpp/oracle/10.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 -O /workspace/PAFL_coverage/yaml_cpp/oracle/1.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 -O /workspace/PAFL_coverage/yaml_cpp/oracle/2.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 -O /workspace/PAFL_coverage/yaml_cpp/oracle/3.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 -O /workspace/PAFL_coverage/yaml_cpp/oracle/4.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 -O /workspace/PAFL_coverage/yaml_cpp/oracle/5.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 -O /workspace/PAFL_coverage/yaml_cpp/oracle/6.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 -O /workspace/PAFL_coverage/yaml_cpp/oracle/7.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 --thread $THREAD -c -l
pafl train -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 -O /workspace/PAFL_coverage/yaml_cpp/oracle/8.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-9 -T /workspace/PAFL_coverage/yaml_cpp/buggy-9 -c
pafl run-pafl -P yaml_cpp-dstar -S /workspace/source/yaml_cpp/buggy-9 -T /workspace/PAFL_coverage/yaml_cpp/buggy-9 --thread $THREAD -c -l

pafl profile thefuck-dstar python dstar
pafl profile-reset thefuck-dstar
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 -O /workspace/PAFL_coverage/thefuck/oracle/32.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 -O /workspace/PAFL_coverage/thefuck/oracle/31.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 -O /workspace/PAFL_coverage/thefuck/oracle/30.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 -O /workspace/PAFL_coverage/thefuck/oracle/29.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 -O /workspace/PAFL_coverage/thefuck/oracle/28.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 -O /workspace/PAFL_coverage/thefuck/oracle/27.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 -O /workspace/PAFL_coverage/thefuck/oracle/26.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 -O /workspace/PAFL_coverage/thefuck/oracle/25.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 -O /workspace/PAFL_coverage/thefuck/oracle/24.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 -O /workspace/PAFL_coverage/thefuck/oracle/23.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 -O /workspace/PAFL_coverage/thefuck/oracle/22.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 -O /workspace/PAFL_coverage/thefuck/oracle/21.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 -O /workspace/PAFL_coverage/thefuck/oracle/20.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 -O /workspace/PAFL_coverage/thefuck/oracle/19.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 -O /workspace/PAFL_coverage/thefuck/oracle/18.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 -O /workspace/PAFL_coverage/thefuck/oracle/17.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 -O /workspace/PAFL_coverage/thefuck/oracle/16.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 -O /workspace/PAFL_coverage/thefuck/oracle/15.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 -O /workspace/PAFL_coverage/thefuck/oracle/14.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 -O /workspace/PAFL_coverage/thefuck/oracle/13.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 -O /workspace/PAFL_coverage/thefuck/oracle/11.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 -O /workspace/PAFL_coverage/thefuck/oracle/10.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 -O /workspace/PAFL_coverage/thefuck/oracle/9.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 -O /workspace/PAFL_coverage/thefuck/oracle/8.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 -O /workspace/PAFL_coverage/thefuck/oracle/7.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 -O /workspace/PAFL_coverage/thefuck/oracle/6.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 -O /workspace/PAFL_coverage/thefuck/oracle/5.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 -O /workspace/PAFL_coverage/thefuck/oracle/4.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 -O /workspace/PAFL_coverage/thefuck/oracle/3.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 --thread $THREAD -c -l
pafl train -P thefuck-dstar -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 -O /workspace/PAFL_coverage/thefuck/oracle/2.json --thread $THREAD -c -l
pafl run-base -P thefuck-dstar -S /workspace/source/thefuck/thefuck-1/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-1 -c
pafl run-pafl -P thefuck-dstar -S /workspace/source/thefuck/thefuck-1/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-1 --thread $THREAD -c -l

pafl profile fastapi-dstar python dstar
pafl profile-reset fastapi-dstar
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 -O /workspace/PAFL_coverage/fastapi/oracle/16.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 -O /workspace/PAFL_coverage/fastapi/oracle/15.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 -O /workspace/PAFL_coverage/fastapi/oracle/14.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 -O /workspace/PAFL_coverage/fastapi/oracle/13.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 -O /workspace/PAFL_coverage/fastapi/oracle/12.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 -O /workspace/PAFL_coverage/fastapi/oracle/11.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 -O /workspace/PAFL_coverage/fastapi/oracle/10.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 -O /workspace/PAFL_coverage/fastapi/oracle/9.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 -O /workspace/PAFL_coverage/fastapi/oracle/8.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 -O /workspace/PAFL_coverage/fastapi/oracle/7.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 -O /workspace/PAFL_coverage/fastapi/oracle/6.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 -O /workspace/PAFL_coverage/fastapi/oracle/5.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 -O /workspace/PAFL_coverage/fastapi/oracle/4.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 --thread $THREAD -c -l
pafl train -P fastapi-dstar -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 -O /workspace/PAFL_coverage/fastapi/oracle/3.json --thread $THREAD -c -l
pafl run-base -P fastapi-dstar -S /workspace/source/fastapi/fastapi-2/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-2 -c
pafl run-pafl -P fastapi-dstar -S /workspace/source/fastapi/fastapi-2/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-2 --thread $THREAD -c -l

pafl profile spacy-dstar python dstar
pafl profile-reset spacy-dstar
pafl run-base -P spacy-dstar -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 -c
pafl run-pafl -P spacy-dstar -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 --thread $THREAD -c -l
pafl train -P spacy-dstar -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 -O /workspace/PAFL_coverage/spacy/oracle/7.json --thread $THREAD -c -l
pafl run-base -P spacy-dstar -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 -c
pafl run-pafl -P spacy-dstar -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 --thread $THREAD -c -l
pafl train -P spacy-dstar -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 -O /workspace/PAFL_coverage/spacy/oracle/6.json --thread $THREAD -c -l
pafl run-base -P spacy-dstar -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 -c
pafl run-pafl -P spacy-dstar -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 --thread $THREAD -c -l
pafl train -P spacy-dstar -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 -O /workspace/PAFL_coverage/spacy/oracle/5.json --thread $THREAD -c -l
pafl run-base -P spacy-dstar -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 -c
pafl run-pafl -P spacy-dstar -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 --thread $THREAD -c -l
pafl train -P spacy-dstar -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 -O /workspace/PAFL_coverage/spacy/oracle/4.json --thread $THREAD -c -l
pafl run-base -P spacy-dstar -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 -c
pafl run-pafl -P spacy-dstar -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 --thread $THREAD -c -l
pafl train -P spacy-dstar -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 -O /workspace/PAFL_coverage/spacy/oracle/3.json --thread $THREAD -c -l
pafl run-base -P spacy-dstar -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 -c
pafl run-pafl -P spacy-dstar -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 --thread $THREAD -c -l
pafl train -P spacy-dstar -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 -O /workspace/PAFL_coverage/spacy/oracle/2.json --thread $THREAD -c -l
pafl run-base -P spacy-dstar -S /workspace/source/spacy/spacy-1/spacy -T /workspace/PAFL_coverage/spacy/buggy-1 -c
pafl run-pafl -P spacy-dstar -S /workspace/source/spacy/spacy-1/spacy -T /workspace/PAFL_coverage/spacy/buggy-1 --thread $THREAD -c -l

pafl profile youtube-dl-dstar python dstar
pafl profile-reset youtube-dl-dstar
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 -O /workspace/PAFL_coverage/youtube-dl/oracle/35.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 -O /workspace/PAFL_coverage/youtube-dl/oracle/34.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 -O /workspace/PAFL_coverage/youtube-dl/oracle/33.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 -O /workspace/PAFL_coverage/youtube-dl/oracle/32.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 -O /workspace/PAFL_coverage/youtube-dl/oracle/31.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 -O /workspace/PAFL_coverage/youtube-dl/oracle/10.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 -O /workspace/PAFL_coverage/youtube-dl/oracle/9.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 -O /workspace/PAFL_coverage/youtube-dl/oracle/8.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 -O /workspace/PAFL_coverage/youtube-dl/oracle/30.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 -O /workspace/PAFL_coverage/youtube-dl/oracle/7.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 -O /workspace/PAFL_coverage/youtube-dl/oracle/29.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 -O /workspace/PAFL_coverage/youtube-dl/oracle/28.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 -O /workspace/PAFL_coverage/youtube-dl/oracle/6.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 -O /workspace/PAFL_coverage/youtube-dl/oracle/27.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 -O /workspace/PAFL_coverage/youtube-dl/oracle/26.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 -O /workspace/PAFL_coverage/youtube-dl/oracle/5.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 -O /workspace/PAFL_coverage/youtube-dl/oracle/25.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 -O /workspace/PAFL_coverage/youtube-dl/oracle/24.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 -O /workspace/PAFL_coverage/youtube-dl/oracle/23.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 -O /workspace/PAFL_coverage/youtube-dl/oracle/22.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 -O /workspace/PAFL_coverage/youtube-dl/oracle/21.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 -O /workspace/PAFL_coverage/youtube-dl/oracle/20.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 -O /workspace/PAFL_coverage/youtube-dl/oracle/19.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 -O /workspace/PAFL_coverage/youtube-dl/oracle/18.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 -O /workspace/PAFL_coverage/youtube-dl/oracle/3.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 -O /workspace/PAFL_coverage/youtube-dl/oracle/16.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 -O /workspace/PAFL_coverage/youtube-dl/oracle/2.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 -O /workspace/PAFL_coverage/youtube-dl/oracle/15.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 -O /workspace/PAFL_coverage/youtube-dl/oracle/1.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 -O /workspace/PAFL_coverage/youtube-dl/oracle/13.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 --thread $THREAD -c -l
pafl train -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 -O /workspace/PAFL_coverage/youtube-dl/oracle/12.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-11/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-11 -c
pafl run-pafl -P youtube-dl-dstar -S /workspace/source/youtube-dl/youtube-dl-11/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-11 --thread $THREAD -c -l

pafl profile cpp_peglib-jaccard cpp jaccard
pafl profile-reset cpp_peglib-jaccard
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-8 -T /workspace/PAFL_coverage/cpp_peglib/buggy-8 -O /workspace/PAFL_coverage/cpp_peglib/oracle/8.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-9 -T /workspace/PAFL_coverage/cpp_peglib/buggy-9 -O /workspace/PAFL_coverage/cpp_peglib/oracle/9.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-7 -T /workspace/PAFL_coverage/cpp_peglib/buggy-7 -O /workspace/PAFL_coverage/cpp_peglib/oracle/7.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-6 -T /workspace/PAFL_coverage/cpp_peglib/buggy-6 -O /workspace/PAFL_coverage/cpp_peglib/oracle/6.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-5 -T /workspace/PAFL_coverage/cpp_peglib/buggy-5 -O /workspace/PAFL_coverage/cpp_peglib/oracle/5.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-4 -T /workspace/PAFL_coverage/cpp_peglib/buggy-4 -O /workspace/PAFL_coverage/cpp_peglib/oracle/4.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-2 -T /workspace/PAFL_coverage/cpp_peglib/buggy-2 -O /workspace/PAFL_coverage/cpp_peglib/oracle/2.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-3 -T /workspace/PAFL_coverage/cpp_peglib/buggy-3 -O /workspace/PAFL_coverage/cpp_peglib/oracle/3.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 --thread $THREAD -c -l
pafl train -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-1 -T /workspace/PAFL_coverage/cpp_peglib/buggy-1 -O /workspace/PAFL_coverage/cpp_peglib/oracle/1.json --thread $THREAD -c -l
pafl run-base -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-10 -T /workspace/PAFL_coverage/cpp_peglib/buggy-10 -c
pafl run-pafl -P cpp_peglib-jaccard -S /workspace/source/cpp_peglib/buggy-10 -T /workspace/PAFL_coverage/cpp_peglib/buggy-10 --thread $THREAD -c -l

pafl profile cppcheck-jaccard cpp jaccard
pafl profile-reset cppcheck-jaccard
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-7 -T /workspace/PAFL_coverage/cppcheck/buggy-7 -O /workspace/PAFL_coverage/cppcheck/oracle/7.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-1 -T /workspace/PAFL_coverage/cppcheck/buggy-1 -O /workspace/PAFL_coverage/cppcheck/oracle/1.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-27 -T /workspace/PAFL_coverage/cppcheck/buggy-27 -O /workspace/PAFL_coverage/cppcheck/oracle/27.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-2 -T /workspace/PAFL_coverage/cppcheck/buggy-2 -O /workspace/PAFL_coverage/cppcheck/oracle/2.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-15 -T /workspace/PAFL_coverage/cppcheck/buggy-15 -O /workspace/PAFL_coverage/cppcheck/oracle/15.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-29 -T /workspace/PAFL_coverage/cppcheck/buggy-29 -O /workspace/PAFL_coverage/cppcheck/oracle/29.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-14 -T /workspace/PAFL_coverage/cppcheck/buggy-14 -O /workspace/PAFL_coverage/cppcheck/oracle/14.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-6 -T /workspace/PAFL_coverage/cppcheck/buggy-6 -O /workspace/PAFL_coverage/cppcheck/oracle/6.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-23 -T /workspace/PAFL_coverage/cppcheck/buggy-23 -O /workspace/PAFL_coverage/cppcheck/oracle/23.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-5 -T /workspace/PAFL_coverage/cppcheck/buggy-5 -O /workspace/PAFL_coverage/cppcheck/oracle/5.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-17 -T /workspace/PAFL_coverage/cppcheck/buggy-17 -O /workspace/PAFL_coverage/cppcheck/oracle/17.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-30 -T /workspace/PAFL_coverage/cppcheck/buggy-30 -O /workspace/PAFL_coverage/cppcheck/oracle/30.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-24 -T /workspace/PAFL_coverage/cppcheck/buggy-24 -O /workspace/PAFL_coverage/cppcheck/oracle/24.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-8 -T /workspace/PAFL_coverage/cppcheck/buggy-8 -O /workspace/PAFL_coverage/cppcheck/oracle/8.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-16 -T /workspace/PAFL_coverage/cppcheck/buggy-16 -O /workspace/PAFL_coverage/cppcheck/oracle/16.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-25 -T /workspace/PAFL_coverage/cppcheck/buggy-25 -O /workspace/PAFL_coverage/cppcheck/oracle/25.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-3 -T /workspace/PAFL_coverage/cppcheck/buggy-3 -O /workspace/PAFL_coverage/cppcheck/oracle/3.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-19 -T /workspace/PAFL_coverage/cppcheck/buggy-19 -O /workspace/PAFL_coverage/cppcheck/oracle/19.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-9 -T /workspace/PAFL_coverage/cppcheck/buggy-9 -O /workspace/PAFL_coverage/cppcheck/oracle/9.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-18 -T /workspace/PAFL_coverage/cppcheck/buggy-18 -O /workspace/PAFL_coverage/cppcheck/oracle/18.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-12 -T /workspace/PAFL_coverage/cppcheck/buggy-12 -O /workspace/PAFL_coverage/cppcheck/oracle/12.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-11 -T /workspace/PAFL_coverage/cppcheck/buggy-11 -O /workspace/PAFL_coverage/cppcheck/oracle/11.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-21 -T /workspace/PAFL_coverage/cppcheck/buggy-21 -O /workspace/PAFL_coverage/cppcheck/oracle/21.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-28 -T /workspace/PAFL_coverage/cppcheck/buggy-28 -O /workspace/PAFL_coverage/cppcheck/oracle/28.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-13 -T /workspace/PAFL_coverage/cppcheck/buggy-13 -O /workspace/PAFL_coverage/cppcheck/oracle/13.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-20 -T /workspace/PAFL_coverage/cppcheck/buggy-20 -O /workspace/PAFL_coverage/cppcheck/oracle/20.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-22 -T /workspace/PAFL_coverage/cppcheck/buggy-22 -O /workspace/PAFL_coverage/cppcheck/oracle/22.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-4 -T /workspace/PAFL_coverage/cppcheck/buggy-4 -O /workspace/PAFL_coverage/cppcheck/oracle/4.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 --thread $THREAD -c -l
pafl train -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-26 -T /workspace/PAFL_coverage/cppcheck/buggy-26 -O /workspace/PAFL_coverage/cppcheck/oracle/26.json --thread $THREAD -c -l
pafl run-base -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-10 -T /workspace/PAFL_coverage/cppcheck/buggy-10 -c
pafl run-pafl -P cppcheck-jaccard -S /workspace/source/cppcheck/buggy-10 -T /workspace/PAFL_coverage/cppcheck/buggy-10 --thread $THREAD -c -l

pafl profile exiv2-jaccard cpp jaccard
pafl profile-reset exiv2-jaccard
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-10 -T /workspace/PAFL_coverage/exiv2/buggy-10 -O /workspace/PAFL_coverage/exiv2/oracle/10.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-15 -T /workspace/PAFL_coverage/exiv2/buggy-15 -O /workspace/PAFL_coverage/exiv2/oracle/15.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-14 -T /workspace/PAFL_coverage/exiv2/buggy-14 -O /workspace/PAFL_coverage/exiv2/oracle/14.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-4 -T /workspace/PAFL_coverage/exiv2/buggy-4 -O /workspace/PAFL_coverage/exiv2/oracle/4.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-13 -T /workspace/PAFL_coverage/exiv2/buggy-13 -O /workspace/PAFL_coverage/exiv2/oracle/13.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-6 -T /workspace/PAFL_coverage/exiv2/buggy-6 -O /workspace/PAFL_coverage/exiv2/oracle/6.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-8 -T /workspace/PAFL_coverage/exiv2/buggy-8 -O /workspace/PAFL_coverage/exiv2/oracle/8.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-9 -T /workspace/PAFL_coverage/exiv2/buggy-9 -O /workspace/PAFL_coverage/exiv2/oracle/9.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-11 -T /workspace/PAFL_coverage/exiv2/buggy-11 -O /workspace/PAFL_coverage/exiv2/oracle/11.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-12 -T /workspace/PAFL_coverage/exiv2/buggy-12 -O /workspace/PAFL_coverage/exiv2/oracle/12.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-7 -T /workspace/PAFL_coverage/exiv2/buggy-7 -O /workspace/PAFL_coverage/exiv2/oracle/7.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-5 -T /workspace/PAFL_coverage/exiv2/buggy-5 -O /workspace/PAFL_coverage/exiv2/oracle/5.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-16 -T /workspace/PAFL_coverage/exiv2/buggy-16 -O /workspace/PAFL_coverage/exiv2/oracle/16.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-17 -T /workspace/PAFL_coverage/exiv2/buggy-17 -O /workspace/PAFL_coverage/exiv2/oracle/17.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-3 -T /workspace/PAFL_coverage/exiv2/buggy-3 -O /workspace/PAFL_coverage/exiv2/oracle/3.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-2 -T /workspace/PAFL_coverage/exiv2/buggy-2 -O /workspace/PAFL_coverage/exiv2/oracle/2.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-1 -T /workspace/PAFL_coverage/exiv2/buggy-1 -O /workspace/PAFL_coverage/exiv2/oracle/1.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-18 -T /workspace/PAFL_coverage/exiv2/buggy-18 -O /workspace/PAFL_coverage/exiv2/oracle/18.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 --thread $THREAD -c -l
pafl train -P exiv2-jaccard -S /workspace/source/exiv2/buggy-19 -T /workspace/PAFL_coverage/exiv2/buggy-19 -O /workspace/PAFL_coverage/exiv2/oracle/19.json --thread $THREAD -c -l
pafl run-base -P exiv2-jaccard -S /workspace/source/exiv2/buggy-20 -T /workspace/PAFL_coverage/exiv2/buggy-20 -c
pafl run-pafl -P exiv2-jaccard -S /workspace/source/exiv2/buggy-20 -T /workspace/PAFL_coverage/exiv2/buggy-20 --thread $THREAD -c -l

pafl profile libchewing-jaccard cpp jaccard
pafl profile-reset libchewing-jaccard
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 --thread $THREAD -c -l
pafl train -P libchewing-jaccard -S /workspace/source/libchewing/buggy-6 -T /workspace/PAFL_coverage/libchewing/buggy-6 -O /workspace/PAFL_coverage/libchewing/oracle/6.json --thread $THREAD -c -l
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 --thread $THREAD -c -l
pafl train -P libchewing-jaccard -S /workspace/source/libchewing/buggy-8 -T /workspace/PAFL_coverage/libchewing/buggy-8 -O /workspace/PAFL_coverage/libchewing/oracle/8.json --thread $THREAD -c -l
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 --thread $THREAD -c -l
pafl train -P libchewing-jaccard -S /workspace/source/libchewing/buggy-3 -T /workspace/PAFL_coverage/libchewing/buggy-3 -O /workspace/PAFL_coverage/libchewing/oracle/3.json --thread $THREAD -c -l
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 --thread $THREAD -c -l
pafl train -P libchewing-jaccard -S /workspace/source/libchewing/buggy-4 -T /workspace/PAFL_coverage/libchewing/buggy-4 -O /workspace/PAFL_coverage/libchewing/oracle/4.json --thread $THREAD -c -l
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 --thread $THREAD -c -l
pafl train -P libchewing-jaccard -S /workspace/source/libchewing/buggy-5 -T /workspace/PAFL_coverage/libchewing/buggy-5 -O /workspace/PAFL_coverage/libchewing/oracle/5.json --thread $THREAD -c -l
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 --thread $THREAD -c -l
pafl train -P libchewing-jaccard -S /workspace/source/libchewing/buggy-7 -T /workspace/PAFL_coverage/libchewing/buggy-7 -O /workspace/PAFL_coverage/libchewing/oracle/7.json --thread $THREAD -c -l
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 --thread $THREAD -c -l
pafl train -P libchewing-jaccard -S /workspace/source/libchewing/buggy-2 -T /workspace/PAFL_coverage/libchewing/buggy-2 -O /workspace/PAFL_coverage/libchewing/oracle/2.json --thread $THREAD -c -l
pafl run-base -P libchewing-jaccard -S /workspace/source/libchewing/buggy-1 -T /workspace/PAFL_coverage/libchewing/buggy-1 -c
pafl run-pafl -P libchewing-jaccard -S /workspace/source/libchewing/buggy-1 -T /workspace/PAFL_coverage/libchewing/buggy-1 --thread $THREAD -c -l

pafl profile libxml2-jaccard cpp jaccard
pafl profile-reset libxml2-jaccard
pafl run-base -P libxml2-jaccard -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 -c
pafl run-pafl -P libxml2-jaccard -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 --thread $THREAD -c -l
pafl train -P libxml2-jaccard -S /workspace/source/libxml2/buggy-4 -T /workspace/PAFL_coverage/libxml2/buggy-4 -O /workspace/PAFL_coverage/libxml2/oracle/4.json --thread $THREAD -c -l
pafl run-base -P libxml2-jaccard -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 -c
pafl run-pafl -P libxml2-jaccard -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 --thread $THREAD -c -l
pafl train -P libxml2-jaccard -S /workspace/source/libxml2/buggy-7 -T /workspace/PAFL_coverage/libxml2/buggy-7 -O /workspace/PAFL_coverage/libxml2/oracle/7.json --thread $THREAD -c -l
pafl run-base -P libxml2-jaccard -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 -c
pafl run-pafl -P libxml2-jaccard -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 --thread $THREAD -c -l
pafl train -P libxml2-jaccard -S /workspace/source/libxml2/buggy-1 -T /workspace/PAFL_coverage/libxml2/buggy-1 -O /workspace/PAFL_coverage/libxml2/oracle/1.json --thread $THREAD -c -l
pafl run-base -P libxml2-jaccard -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 -c
pafl run-pafl -P libxml2-jaccard -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 --thread $THREAD -c -l
pafl train -P libxml2-jaccard -S /workspace/source/libxml2/buggy-2 -T /workspace/PAFL_coverage/libxml2/buggy-2 -O /workspace/PAFL_coverage/libxml2/oracle/2.json --thread $THREAD -c -l
pafl run-base -P libxml2-jaccard -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 -c
pafl run-pafl -P libxml2-jaccard -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 --thread $THREAD -c -l
pafl train -P libxml2-jaccard -S /workspace/source/libxml2/buggy-3 -T /workspace/PAFL_coverage/libxml2/buggy-3 -O /workspace/PAFL_coverage/libxml2/oracle/3.json --thread $THREAD -c -l
pafl run-base -P libxml2-jaccard -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 -c
pafl run-pafl -P libxml2-jaccard -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 --thread $THREAD -c -l
pafl train -P libxml2-jaccard -S /workspace/source/libxml2/buggy-5 -T /workspace/PAFL_coverage/libxml2/buggy-5 -O /workspace/PAFL_coverage/libxml2/oracle/5.json --thread $THREAD -c -l
pafl run-base -P libxml2-jaccard -S /workspace/source/libxml2/buggy-6 -T /workspace/PAFL_coverage/libxml2/buggy-6 -c
pafl run-pafl -P libxml2-jaccard -S /workspace/source/libxml2/buggy-6 -T /workspace/PAFL_coverage/libxml2/buggy-6 --thread $THREAD -c -l

pafl profile proj-jaccard cpp jaccard
pafl profile-reset proj-jaccard
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-24 -T /workspace/PAFL_coverage/proj/buggy-24 -O /workspace/PAFL_coverage/proj/oracle/24.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-8 -T /workspace/PAFL_coverage/proj/buggy-8 -O /workspace/PAFL_coverage/proj/oracle/8.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-13 -T /workspace/PAFL_coverage/proj/buggy-13 -O /workspace/PAFL_coverage/proj/oracle/13.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-12 -T /workspace/PAFL_coverage/proj/buggy-12 -O /workspace/PAFL_coverage/proj/oracle/12.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-11 -T /workspace/PAFL_coverage/proj/buggy-11 -O /workspace/PAFL_coverage/proj/oracle/11.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-21 -T /workspace/PAFL_coverage/proj/buggy-21 -O /workspace/PAFL_coverage/proj/oracle/21.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-22 -T /workspace/PAFL_coverage/proj/buggy-22 -O /workspace/PAFL_coverage/proj/oracle/22.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-9 -T /workspace/PAFL_coverage/proj/buggy-9 -O /workspace/PAFL_coverage/proj/oracle/9.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-18 -T /workspace/PAFL_coverage/proj/buggy-18 -O /workspace/PAFL_coverage/proj/oracle/18.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-16 -T /workspace/PAFL_coverage/proj/buggy-16 -O /workspace/PAFL_coverage/proj/oracle/16.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-1 -T /workspace/PAFL_coverage/proj/buggy-1 -O /workspace/PAFL_coverage/proj/oracle/1.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-3 -T /workspace/PAFL_coverage/proj/buggy-3 -O /workspace/PAFL_coverage/proj/oracle/3.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-17 -T /workspace/PAFL_coverage/proj/buggy-17 -O /workspace/PAFL_coverage/proj/oracle/17.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-2 -T /workspace/PAFL_coverage/proj/buggy-2 -O /workspace/PAFL_coverage/proj/oracle/2.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-4 -T /workspace/PAFL_coverage/proj/buggy-4 -O /workspace/PAFL_coverage/proj/oracle/4.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-19 -T /workspace/PAFL_coverage/proj/buggy-19 -O /workspace/PAFL_coverage/proj/oracle/19.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-10 -T /workspace/PAFL_coverage/proj/buggy-10 -O /workspace/PAFL_coverage/proj/oracle/10.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-6 -T /workspace/PAFL_coverage/proj/buggy-6 -O /workspace/PAFL_coverage/proj/oracle/6.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-20 -T /workspace/PAFL_coverage/proj/buggy-20 -O /workspace/PAFL_coverage/proj/oracle/20.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-5 -T /workspace/PAFL_coverage/proj/buggy-5 -O /workspace/PAFL_coverage/proj/oracle/5.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-27 -T /workspace/PAFL_coverage/proj/buggy-27 -O /workspace/PAFL_coverage/proj/oracle/27.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-23 -T /workspace/PAFL_coverage/proj/buggy-23 -O /workspace/PAFL_coverage/proj/oracle/23.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-14 -T /workspace/PAFL_coverage/proj/buggy-14 -O /workspace/PAFL_coverage/proj/oracle/14.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-28 -T /workspace/PAFL_coverage/proj/buggy-28 -O /workspace/PAFL_coverage/proj/oracle/28.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-15 -T /workspace/PAFL_coverage/proj/buggy-15 -O /workspace/PAFL_coverage/proj/oracle/15.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-7 -T /workspace/PAFL_coverage/proj/buggy-7 -O /workspace/PAFL_coverage/proj/oracle/7.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 --thread $THREAD -c -l
pafl train -P proj-jaccard -S /workspace/source/proj/buggy-26 -T /workspace/PAFL_coverage/proj/buggy-26 -O /workspace/PAFL_coverage/proj/oracle/26.json --thread $THREAD -c -l
pafl run-base -P proj-jaccard -S /workspace/source/proj/buggy-25 -T /workspace/PAFL_coverage/proj/buggy-25 -c
pafl run-pafl -P proj-jaccard -S /workspace/source/proj/buggy-25 -T /workspace/PAFL_coverage/proj/buggy-25 --thread $THREAD -c -l

pafl profile openssl-jaccard cpp jaccard
pafl profile-reset openssl-jaccard
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-13 -T /workspace/PAFL_coverage/openssl/buggy-13 -O /workspace/PAFL_coverage/openssl/oracle/13.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-1 -T /workspace/PAFL_coverage/openssl/buggy-1 -O /workspace/PAFL_coverage/openssl/oracle/1.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-2 -T /workspace/PAFL_coverage/openssl/buggy-2 -O /workspace/PAFL_coverage/openssl/oracle/2.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-9 -T /workspace/PAFL_coverage/openssl/buggy-9 -O /workspace/PAFL_coverage/openssl/oracle/9.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-12 -T /workspace/PAFL_coverage/openssl/buggy-12 -O /workspace/PAFL_coverage/openssl/oracle/12.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-19 -T /workspace/PAFL_coverage/openssl/buggy-19 -O /workspace/PAFL_coverage/openssl/oracle/19.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-14 -T /workspace/PAFL_coverage/openssl/buggy-14 -O /workspace/PAFL_coverage/openssl/oracle/14.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-28 -T /workspace/PAFL_coverage/openssl/buggy-28 -O /workspace/PAFL_coverage/openssl/oracle/28.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-11 -T /workspace/PAFL_coverage/openssl/buggy-11 -O /workspace/PAFL_coverage/openssl/oracle/11.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-15 -T /workspace/PAFL_coverage/openssl/buggy-15 -O /workspace/PAFL_coverage/openssl/oracle/15.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-5 -T /workspace/PAFL_coverage/openssl/buggy-5 -O /workspace/PAFL_coverage/openssl/oracle/5.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-18 -T /workspace/PAFL_coverage/openssl/buggy-18 -O /workspace/PAFL_coverage/openssl/oracle/18.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-16 -T /workspace/PAFL_coverage/openssl/buggy-16 -O /workspace/PAFL_coverage/openssl/oracle/16.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-22 -T /workspace/PAFL_coverage/openssl/buggy-22 -O /workspace/PAFL_coverage/openssl/oracle/22.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-10 -T /workspace/PAFL_coverage/openssl/buggy-10 -O /workspace/PAFL_coverage/openssl/oracle/10.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-23 -T /workspace/PAFL_coverage/openssl/buggy-23 -O /workspace/PAFL_coverage/openssl/oracle/23.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-26 -T /workspace/PAFL_coverage/openssl/buggy-26 -O /workspace/PAFL_coverage/openssl/oracle/26.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-24 -T /workspace/PAFL_coverage/openssl/buggy-24 -O /workspace/PAFL_coverage/openssl/oracle/24.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-25 -T /workspace/PAFL_coverage/openssl/buggy-25 -O /workspace/PAFL_coverage/openssl/oracle/25.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-17 -T /workspace/PAFL_coverage/openssl/buggy-17 -O /workspace/PAFL_coverage/openssl/oracle/17.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-6 -T /workspace/PAFL_coverage/openssl/buggy-6 -O /workspace/PAFL_coverage/openssl/oracle/6.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-4 -T /workspace/PAFL_coverage/openssl/buggy-4 -O /workspace/PAFL_coverage/openssl/oracle/4.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-7 -T /workspace/PAFL_coverage/openssl/buggy-7 -O /workspace/PAFL_coverage/openssl/oracle/7.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-27 -T /workspace/PAFL_coverage/openssl/buggy-27 -O /workspace/PAFL_coverage/openssl/oracle/27.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 --thread $THREAD -c -l
pafl train -P openssl-jaccard -S /workspace/source/openssl/buggy-20 -T /workspace/PAFL_coverage/openssl/buggy-20 -O /workspace/PAFL_coverage/openssl/oracle/20.json --thread $THREAD -c -l
pafl run-base -P openssl-jaccard -S /workspace/source/openssl/buggy-21 -T /workspace/PAFL_coverage/openssl/buggy-21 -c
pafl run-pafl -P openssl-jaccard -S /workspace/source/openssl/buggy-21 -T /workspace/PAFL_coverage/openssl/buggy-21 --thread $THREAD -c -l

pafl profile yaml_cpp-jaccard cpp jaccard
pafl profile-reset yaml_cpp-jaccard
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-10 -T /workspace/PAFL_coverage/yaml_cpp/buggy-10 -O /workspace/PAFL_coverage/yaml_cpp/oracle/10.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-1 -T /workspace/PAFL_coverage/yaml_cpp/buggy-1 -O /workspace/PAFL_coverage/yaml_cpp/oracle/1.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-2 -T /workspace/PAFL_coverage/yaml_cpp/buggy-2 -O /workspace/PAFL_coverage/yaml_cpp/oracle/2.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-3 -T /workspace/PAFL_coverage/yaml_cpp/buggy-3 -O /workspace/PAFL_coverage/yaml_cpp/oracle/3.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-4 -T /workspace/PAFL_coverage/yaml_cpp/buggy-4 -O /workspace/PAFL_coverage/yaml_cpp/oracle/4.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-5 -T /workspace/PAFL_coverage/yaml_cpp/buggy-5 -O /workspace/PAFL_coverage/yaml_cpp/oracle/5.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-6 -T /workspace/PAFL_coverage/yaml_cpp/buggy-6 -O /workspace/PAFL_coverage/yaml_cpp/oracle/6.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-7 -T /workspace/PAFL_coverage/yaml_cpp/buggy-7 -O /workspace/PAFL_coverage/yaml_cpp/oracle/7.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 --thread $THREAD -c -l
pafl train -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-8 -T /workspace/PAFL_coverage/yaml_cpp/buggy-8 -O /workspace/PAFL_coverage/yaml_cpp/oracle/8.json --thread $THREAD -c -l
pafl run-base -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-9 -T /workspace/PAFL_coverage/yaml_cpp/buggy-9 -c
pafl run-pafl -P yaml_cpp-jaccard -S /workspace/source/yaml_cpp/buggy-9 -T /workspace/PAFL_coverage/yaml_cpp/buggy-9 --thread $THREAD -c -l

pafl profile thefuck-jaccard python jaccard
pafl profile-reset thefuck-jaccard
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-32/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-32 -O /workspace/PAFL_coverage/thefuck/oracle/32.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-31/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-31 -O /workspace/PAFL_coverage/thefuck/oracle/31.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-30/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-30 -O /workspace/PAFL_coverage/thefuck/oracle/30.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-29/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-29 -O /workspace/PAFL_coverage/thefuck/oracle/29.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-28/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-28 -O /workspace/PAFL_coverage/thefuck/oracle/28.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-27/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-27 -O /workspace/PAFL_coverage/thefuck/oracle/27.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-26/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-26 -O /workspace/PAFL_coverage/thefuck/oracle/26.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-25/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-25 -O /workspace/PAFL_coverage/thefuck/oracle/25.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-24/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-24 -O /workspace/PAFL_coverage/thefuck/oracle/24.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-23/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-23 -O /workspace/PAFL_coverage/thefuck/oracle/23.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-22/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-22 -O /workspace/PAFL_coverage/thefuck/oracle/22.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-21/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-21 -O /workspace/PAFL_coverage/thefuck/oracle/21.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-20/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-20 -O /workspace/PAFL_coverage/thefuck/oracle/20.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-19/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-19 -O /workspace/PAFL_coverage/thefuck/oracle/19.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-18/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-18 -O /workspace/PAFL_coverage/thefuck/oracle/18.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-17/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-17 -O /workspace/PAFL_coverage/thefuck/oracle/17.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-16/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-16 -O /workspace/PAFL_coverage/thefuck/oracle/16.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-15/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-15 -O /workspace/PAFL_coverage/thefuck/oracle/15.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-14/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-14 -O /workspace/PAFL_coverage/thefuck/oracle/14.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-13/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-13 -O /workspace/PAFL_coverage/thefuck/oracle/13.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-11/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-11 -O /workspace/PAFL_coverage/thefuck/oracle/11.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-10/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-10 -O /workspace/PAFL_coverage/thefuck/oracle/10.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-9/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-9 -O /workspace/PAFL_coverage/thefuck/oracle/9.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-8/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-8 -O /workspace/PAFL_coverage/thefuck/oracle/8.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-7/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-7 -O /workspace/PAFL_coverage/thefuck/oracle/7.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-6/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-6 -O /workspace/PAFL_coverage/thefuck/oracle/6.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-5/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-5 -O /workspace/PAFL_coverage/thefuck/oracle/5.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-4/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-4 -O /workspace/PAFL_coverage/thefuck/oracle/4.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-3/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-3 -O /workspace/PAFL_coverage/thefuck/oracle/3.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 --thread $THREAD -c -l
pafl train -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-2/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-2 -O /workspace/PAFL_coverage/thefuck/oracle/2.json --thread $THREAD -c -l
pafl run-base -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-1/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-1 -c
pafl run-pafl -P thefuck-jaccard -S /workspace/source/thefuck/thefuck-1/thefuck -T /workspace/PAFL_coverage/thefuck/buggy-1 --thread $THREAD -c -l

pafl profile fastapi-jaccard python jaccard
pafl profile-reset fastapi-jaccard
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-16/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-16 -O /workspace/PAFL_coverage/fastapi/oracle/16.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-15/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-15 -O /workspace/PAFL_coverage/fastapi/oracle/15.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-14/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-14 -O /workspace/PAFL_coverage/fastapi/oracle/14.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-13/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-13 -O /workspace/PAFL_coverage/fastapi/oracle/13.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-12/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-12 -O /workspace/PAFL_coverage/fastapi/oracle/12.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-11/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-11 -O /workspace/PAFL_coverage/fastapi/oracle/11.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-10/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-10 -O /workspace/PAFL_coverage/fastapi/oracle/10.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-9/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-9 -O /workspace/PAFL_coverage/fastapi/oracle/9.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-8/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-8 -O /workspace/PAFL_coverage/fastapi/oracle/8.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-7/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-7 -O /workspace/PAFL_coverage/fastapi/oracle/7.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-6/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-6 -O /workspace/PAFL_coverage/fastapi/oracle/6.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-5/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-5 -O /workspace/PAFL_coverage/fastapi/oracle/5.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-4/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-4 -O /workspace/PAFL_coverage/fastapi/oracle/4.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 --thread $THREAD -c -l
pafl train -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-3/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-3 -O /workspace/PAFL_coverage/fastapi/oracle/3.json --thread $THREAD -c -l
pafl run-base -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-2/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-2 -c
pafl run-pafl -P fastapi-jaccard -S /workspace/source/fastapi/fastapi-2/fastapi -T /workspace/PAFL_coverage/fastapi/buggy-2 --thread $THREAD -c -l

pafl profile spacy-jaccard python jaccard
pafl profile-reset spacy-jaccard
pafl run-base -P spacy-jaccard -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 -c
pafl run-pafl -P spacy-jaccard -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 --thread $THREAD -c -l
pafl train -P spacy-jaccard -S /workspace/source/spacy/spacy-7/spacy -T /workspace/PAFL_coverage/spacy/buggy-7 -O /workspace/PAFL_coverage/spacy/oracle/7.json --thread $THREAD -c -l
pafl run-base -P spacy-jaccard -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 -c
pafl run-pafl -P spacy-jaccard -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 --thread $THREAD -c -l
pafl train -P spacy-jaccard -S /workspace/source/spacy/spacy-6/spacy -T /workspace/PAFL_coverage/spacy/buggy-6 -O /workspace/PAFL_coverage/spacy/oracle/6.json --thread $THREAD -c -l
pafl run-base -P spacy-jaccard -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 -c
pafl run-pafl -P spacy-jaccard -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 --thread $THREAD -c -l
pafl train -P spacy-jaccard -S /workspace/source/spacy/spacy-5/spacy -T /workspace/PAFL_coverage/spacy/buggy-5 -O /workspace/PAFL_coverage/spacy/oracle/5.json --thread $THREAD -c -l
pafl run-base -P spacy-jaccard -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 -c
pafl run-pafl -P spacy-jaccard -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 --thread $THREAD -c -l
pafl train -P spacy-jaccard -S /workspace/source/spacy/spacy-4/spacy -T /workspace/PAFL_coverage/spacy/buggy-4 -O /workspace/PAFL_coverage/spacy/oracle/4.json --thread $THREAD -c -l
pafl run-base -P spacy-jaccard -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 -c
pafl run-pafl -P spacy-jaccard -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 --thread $THREAD -c -l
pafl train -P spacy-jaccard -S /workspace/source/spacy/spacy-3/spacy -T /workspace/PAFL_coverage/spacy/buggy-3 -O /workspace/PAFL_coverage/spacy/oracle/3.json --thread $THREAD -c -l
pafl run-base -P spacy-jaccard -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 -c
pafl run-pafl -P spacy-jaccard -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 --thread $THREAD -c -l
pafl train -P spacy-jaccard -S /workspace/source/spacy/spacy-2/spacy -T /workspace/PAFL_coverage/spacy/buggy-2 -O /workspace/PAFL_coverage/spacy/oracle/2.json --thread $THREAD -c -l
pafl run-base -P spacy-jaccard -S /workspace/source/spacy/spacy-1/spacy -T /workspace/PAFL_coverage/spacy/buggy-1 -c
pafl run-pafl -P spacy-jaccard -S /workspace/source/spacy/spacy-1/spacy -T /workspace/PAFL_coverage/spacy/buggy-1 --thread $THREAD -c -l

pafl profile youtube-dl-jaccard python jaccard
pafl profile-reset youtube-dl-jaccard
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-35/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-35 -O /workspace/PAFL_coverage/youtube-dl/oracle/35.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-34/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-34 -O /workspace/PAFL_coverage/youtube-dl/oracle/34.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-33/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-33 -O /workspace/PAFL_coverage/youtube-dl/oracle/33.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-32/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-32 -O /workspace/PAFL_coverage/youtube-dl/oracle/32.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-31/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-31 -O /workspace/PAFL_coverage/youtube-dl/oracle/31.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-10/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-10 -O /workspace/PAFL_coverage/youtube-dl/oracle/10.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-9/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-9 -O /workspace/PAFL_coverage/youtube-dl/oracle/9.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-8/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-8 -O /workspace/PAFL_coverage/youtube-dl/oracle/8.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-30/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-30 -O /workspace/PAFL_coverage/youtube-dl/oracle/30.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-7/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-7 -O /workspace/PAFL_coverage/youtube-dl/oracle/7.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-29/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-29 -O /workspace/PAFL_coverage/youtube-dl/oracle/29.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-28/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-28 -O /workspace/PAFL_coverage/youtube-dl/oracle/28.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-6/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-6 -O /workspace/PAFL_coverage/youtube-dl/oracle/6.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-27/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-27 -O /workspace/PAFL_coverage/youtube-dl/oracle/27.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-26/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-26 -O /workspace/PAFL_coverage/youtube-dl/oracle/26.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-5/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-5 -O /workspace/PAFL_coverage/youtube-dl/oracle/5.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-25/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-25 -O /workspace/PAFL_coverage/youtube-dl/oracle/25.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-24/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-24 -O /workspace/PAFL_coverage/youtube-dl/oracle/24.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-23/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-23 -O /workspace/PAFL_coverage/youtube-dl/oracle/23.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-22/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-22 -O /workspace/PAFL_coverage/youtube-dl/oracle/22.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-21/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-21 -O /workspace/PAFL_coverage/youtube-dl/oracle/21.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-20/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-20 -O /workspace/PAFL_coverage/youtube-dl/oracle/20.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-19/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-19 -O /workspace/PAFL_coverage/youtube-dl/oracle/19.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-18/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-18 -O /workspace/PAFL_coverage/youtube-dl/oracle/18.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-3/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-3 -O /workspace/PAFL_coverage/youtube-dl/oracle/3.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-16/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-16 -O /workspace/PAFL_coverage/youtube-dl/oracle/16.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-2/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-2 -O /workspace/PAFL_coverage/youtube-dl/oracle/2.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-15/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-15 -O /workspace/PAFL_coverage/youtube-dl/oracle/15.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-1/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-1 -O /workspace/PAFL_coverage/youtube-dl/oracle/1.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-13/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-13 -O /workspace/PAFL_coverage/youtube-dl/oracle/13.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 --thread $THREAD -c -l
pafl train -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-12/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-12 -O /workspace/PAFL_coverage/youtube-dl/oracle/12.json --thread $THREAD -c -l
pafl run-base -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-11/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-11 -c
pafl run-pafl -P youtube-dl-jaccard -S /workspace/source/youtube-dl/youtube-dl-11/youtube-dl -T /workspace/PAFL_coverage/youtube-dl/buggy-11 --thread $THREAD -c -l

