cmake_minimum_required(VERSION 3.22)
project(RA_Handin_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(RA_Handin_2 main.cpp sum-set/SumSet.h sum-set/ChainingSumSet.h hash-function/MultiplyShiftHash.h hash-function/SplitMixHash.h hash-function/StdHash.h random-gen/PseudoRandomGen.h random-gen/RandomGen.h hash-function/FourWiseHash.h hash-function/HGHash.h hash-function/FourWiseHashSlow.h hash-function/HGHashSlow.h test/HashTester.h sum-set/SketchSumSet.h test/SumSetTester.h test/SketchTester.h hash-function/MultiplyShiftHashTask9.h)

