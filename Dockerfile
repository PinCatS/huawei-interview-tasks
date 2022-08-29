
FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

# Install necessary dependencies
RUN apt-get update &&\
    apt-get install -y --no-install-recommends \
    build-essential \
    autoconf \
    automake \
    time \
    libtool \
    vim \
    gdb \
    valgrind \
    locales \
    locales-all &&\
    apt-get clean

ENV LC_ALL en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

WORKDIR /huawei

COPY . .

RUN make

CMD ["sleep", "infinity"]
