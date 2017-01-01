#!/bin/bash

BUILD_DIR=build
SCRIPT_DIR=scripts
SRC_DIR=src

cd ..
if [ ! -d "$BUILD_DIR" ]; then
  mkdir ${BUILD_DIR} 
fi
cd ${BUILD_DIR} 

echo "Generate Makefile..."
cmake ../${SRC_DIR} -Dtest=ON
echo

echo "Compiling..."
make
echo

echo "Testing..."
./ztl_test
echo

cd ../${SCRIPT_DIR}

# echo "Running binary..."
# echo "--------------------------------------------------------------------------------------------------------------"
# echo "--------------------------------------------------------------------------------------------------------------"
# echo "--------------------------------------------------------------------------------------------------------------"
# ./project
# echo
# 
# echo "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
# echo "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
# echo "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
# echo "Finished!"
# rm project
# echo
