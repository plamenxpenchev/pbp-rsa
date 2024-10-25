#!/bin/bash

CONTAINER_NAME=""
if [ "$#" -eq 0 ]; then
	CONTAINER_NAME="pbp-rsa"
elif [ "$#" -eq 1 ]; then
	PBP_RSA_USER=$1
	CONTAINER_NAME="pbp-rsa-${PBP_RSA_USER}"
else
	echo "Illegal number of script parameters." >&2
	exit 1
fi

docker run -it --rm --name ${CONTAINER_NAME} gcc-pbp-rsa-image
