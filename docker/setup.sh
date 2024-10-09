#!/bin/bash
set -o pipefail

BASE_DIR=/usr/src/pbp-rsa

echo "Creating execution and libraries folders..."
mkdir -p ${BASE_DIR}/exec
mkdir -p ${BASE_DIR}/exec/keys
mkdir -p ${BASE_DIR}/exec/text-files
mkdir -p ${BASE_DIR}/libs

echo "Installing libbsd..."
apt-get update
apt-get -y install libbsd-dev

echo "Installing gmp..."
wget -P ${BASE_DIR}/libs https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
echo "a3c2b80201b89e68616f4ad30bc66aee4927c3ce50e33929ca819d5c43538898 *${BASE_DIR}/libs/gmp-6.3.0.tar.xz" | sha256sum -c
tar -xvf ${BASE_DIR}/libs/gmp-6.3.0.tar.xz -C ${BASE_DIR}/libs/
rm ${BASE_DIR}/libs/gmp-6.3.0.tar.xz

cd ${BASE_DIR}/libs/gmp-6.3.0
./configure
make
make check
make install

cd ${BASE_DIR}

echo "Compiling pbp-rsa..."
gcc ${BASE_DIR}/src/*.c ${BASE_DIR}/src/*/*.c -o ${BASE_DIR}/exec/pbp-rsa -lbsd -lm -lgmp `pkg-config --libs libbsd`

