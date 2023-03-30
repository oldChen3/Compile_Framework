#!/bin/bash

readonly SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE:-S0}) && pwd)
readonly SCRIPT_NAME=$(basename "$0")
readonly BASE_DIR="${SCRIPT_DIR}/../.."

readonly APP_INSTALL_DIR="${BASE_DIR}/work/userapps"
readonly APP_COMPILE_DIR="${BASE_DIR}/Apps/MainApp/build"
readonly APP_BIN_DIR="${BASE_DIR}/Apps/MainApp/bin"
readonly APP_TARGET="${APP_BIN_DIR}/App_Main"

if [ "$1" = 'clean' ];then
  rm -rf ${APP_COMPILE_DIR}/*
elif [ "$1" = 'clean_all' ];then
  rm -rf ${APP_COMPILE_DIR}/*
  rm ${APP_TARGET}
elif [ "$1" = 'build' ];then
  cd ${APP_COMPILE_DIR}
  cmake ../
  make
  rsync -v ${APP_TARGET} ${APP_INSTALL_DIR}
fi

exit 0

