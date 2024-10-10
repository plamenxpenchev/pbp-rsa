FROM gcc:14.2
COPY docker/ /usr/src/pbp-rsa/docker/
COPY src/ /usr/src/pbp-rsa/src/
WORKDIR /usr/src/pbp-rsa/
RUN ./docker/setup.sh
CMD ["./exec/pbp-rsa"]