#!/bin/bash

readonly SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE:-S0}) && pwd)
readonly SCRIPT_NAME=$(basename "$0")
readonly BASE_DIR="${SCRIPT_DIR}"

readonly USER_APP_PATH="${BASE_DIR}/userapps"

echo $SCRIPT_DIR
echo $USER_APP_PATH

file_list=$(ls ${USER_APP_PATH})

cd ${USER_APP_PATH}

for bin in ${file_list[*]}
do
  if [ "${bin}" = "App_Main" ];then
	  continue
  else
    echo ${bin}
    ./${bin} fork &
  fi
done

sleep 2
./App_Main 

exit 0

