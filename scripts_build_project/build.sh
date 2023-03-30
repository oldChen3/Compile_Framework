#!/bin/bash

readonly SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE:-S0}) && pwd)
readonly SCRIPT_NAME=$(basename "$0")
readonly BASE_DIR="${SCRIPT_DIR}"
readonly INSTALL_DIR="${SCRIPT_DIR}/work/userapps"


BUILD_TARGET=""

#显示指令要求
usage()
{
  echo "help"
}

if [ "$1" = "help" ]; then
  usage
  exit 0
fi


case "$1" in
  clean )
	BUILD_TARGET="clean"
	;;
  clean_all )
	BUILD_TARGET="clean_all"
	;;
  build )
	BUILD_TARGET="build"
	;;
  * )
	echo "error"
	exit 1
	;;
esac

build_testApp()
{
  local script_dir="${BASE_DIR}/scripts/TestApp"
  local build_script='TestApp-build.sh'
 
  cd ${script_dir}
  pwd
  if [ "$1" = 'clean' ]; then
    ./${build_script} clean
  elif [ "$1" = 'clean_all' ]; then
    ./${build_script} clean_all
  elif [ "$1" = 'build' ]; then
    ./${build_script} clean
    ./${build_script} build
    #./${build_script} install
  fi
}

build_mainApp()
{
  local script_dir="${BASE_DIR}/scripts/MainApp"
  local build_script='MainApp-build.sh'
  
  cd ${script_dir}
  pwd
  if [ "$1" = 'clean' ];then
    ./${build_script} clean
  elif [ "$1" = 'clean_all' ]; then
    ./${build_script} clean_all
  elif [ "$1" = 'build' ];then
    ./${build_script} clean
    ./${build_script} build
    #./${build_script} install
  fi
  
}

build_NetClientApp()
{
  local script_dir="${BASE_DIR}/scripts/NetClientApp"
  local build_script='NetClientApp-build.sh'
  
  cd ${script_dir}
  pwd
  if [ "$1" = 'clean' ];then
    ./${build_script} clean
  elif [ "$1" = 'clean_all' ]; then
    ./${build_script} clean_all
  elif [ "$1" = 'build' ];then
    ./${build_script} clean
    ./${build_script} build
    #./${build_script} install
  fi
  
}

if [ "${BUILD_TARGET}" = "clean" ];then
  build_mainApp clean
  build_testApp clean
  build_NetClientApp clean
elif [ "${BUILD_TARGET}" = "clean_all" ];then
  build_mainApp clean_all
  build_testApp clean_all
  build_NetClientApp clean_all
  rm -rf ${INSTALL_DIR}/*
elif [ "${BUILD_TARGET}" = "build" ];then
  build_mainApp build
  build_testApp build
  build_NetClientApp build
fi

exit 0

