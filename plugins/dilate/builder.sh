#!/bin/bash
# Building script

ProjectName=dilate
ProjectType=so

#if [[ $ProjectName == [* ]]; then
if [[ ${ProjectName:0:1} == '[' ]]; then
    echo Unproceeded template found!
    exit 1
fi

if [ "$1" == "debug" ]; then
  configuration="Debug"
else
  configuration="Release"
fi

BinPath="../../bin"
#ConfigPath="$BinPath/${configuration,}" # ',' mean 'First letter to lower case'


# Create plugins path if it isn't exists
if [ ! -d $BinPath ]; then
  mkdir $BinPath
  if [ ! -d $BinPath ]; then
    echo "Can't create work dir: $BinPath"
    exit 2
  fi
fi

# Create build path if it isn't exists
BuildPath="./build"
BuildConfig="$BuildPath/${configuration,}"
if [ ! -d $BuildConfig ]; then
  if [ ! -d $BuildPath ]; then
    mkdir $BuildPath
    if [ ! -d $BuildPath ]; then
      echo "Can't create dir: $BuildPath"
      exit 3 
    fi
    mkdir $BuildConfig
    if [ ! -d $BuildConfig ]; then
      echo "Can't create dir: $BuildConfig"
      exit 3
    fi
  fi
fi

cmake CMakeLists.txt -B"$BuildConfig" "-DCMAKE_BUILD_TYPE=$configuration"

if [ $? -ne 0 ]; then
  echo "CMake error!"
  exit 4
fi
  
echo "=== CMake OK! ==="
  
cd $BuildConfig
make -j 6
  
if [ $? -ne 0 ]; then
  echo "Make error!"
  exit 5
fi
  
echo "=== Make OK! ==="
  
echo "Building is completed!"

