#!/bin/bash

if hash dos2unix 2>/dev/null; then
	dos2unix docker/setup.sh
fi
docker build -t gcc-pbp-rsa-image .
