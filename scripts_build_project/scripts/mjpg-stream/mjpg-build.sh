#!/bin/bash

readonly SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE:-S0}) && pwd)
readonly SCRIPT_NAME=$(basename "$0")
readonly BASE_DIR="${SCRIPT_DIR}/../.."

readonly APP_INSTALL_DIR="${BASE_DIR}/work/userapps"
readonly PROJECT_DIR="${BASE_DIR}/Apps/mjpg"
readonly CODE_DIR="${PROJECT_DIR}/mjpg-streamer/mjpg-streamer-experimental"
readonly APP_TARGET="${CODE_DIR}/_build/mjpg_streamer"
readonly APP_COMPILE_DIR="${CODE_DIR}/_build"


if [ "$1" = "clean" ]; then
	rm -rf ${APP_COMPILE_DIR}
elif [ "$1" = "build" ];then
	if [ ! -d ${CODE_DIR} ]; then
		cd ${PROJECT_DIR}
		git clone https://github.com/jacksonliam/mjpg-streamer.git
	fi
	cd ${CODE_DIR}
	mkdir _build
	cd _build
	cmake ..
	make
	rsync -v ${APP_TARGET} ${APP_INSTALL_DIR}
elif [ "$1" = "clean_all" ]; then
	rm -rf ${PROJECT_DIR}/*

fi

exit 0

