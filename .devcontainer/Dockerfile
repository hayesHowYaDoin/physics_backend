# Use Ubuntu as the base image
FROM ubuntu:22.04
LABEL maintainer="Jordan Hayes jordanhayes98@gmail.com"

# Configure timezone
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Update and install basic packages
RUN apt-get update
RUN apt-get install -y \
        build-essential \
        git \
        openssh-server \
        gdb \
        pkg-config \
        valgrind \
        systemd-coredump \
        nano

# GCC 11
RUN echo "************************ GCC ************************"
RUN apt-get install -y software-properties-common
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get update
RUN apt-get install -y gcc-11 g++-11
RUN PATH=/bin:$PATH

# CMake 3.28
RUN echo "************************ CMake ************************"
ADD https://cmake.org/files/v3.28/cmake-3.28.0-linux-x86_64.sh /cmake-3.28.0-linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /cmake-3.28.0-linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN cmake --version

# Install Ninja
RUN echo "************************ Ninja ************************"
RUN apt-get install -y ninja-build

# Google Benchmark
RUN echo "************************ Google Benchmark ************************"
RUN git clone https://github.com/google/benchmark
RUN mkdir -p  benchmark/build && cd benchmark/build
WORKDIR "benchmark/build"
RUN cmake -DCMAKE_CXX_FLAGS=-std=c++1z   -DBENCHMARK_DOWNLOAD_DEPENDENCIES=TRUE   -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ../ && cmake --build .  --parallel && cmake --install .
WORKDIR "/"
RUN rm -rf benchmark

# Google Test
RUN echo "************************ Google Test ************************"
RUN git clone https://github.com/google/googletest
RUN mkdir -p googletest/build && cd googletest/build
WORKDIR "googletest/build"
RUN cmake -DCMAKE_CXX_FLAGS=-std=c++1z   -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ../ && cmake --build .  --parallel && cmake --install .
WORKDIR "/"
RUN rm -rf googletest

# Python
RUN echo "************************ Python ************************"
RUN apt-get install -y python3-pip

# PlantUML Dependencies (Java and Graphviz)
RUN echo "************************ PlantUML ************************"
RUN add-apt-repository ppa:openjdk-r/ppa
RUN apt-get install -y openjdk-11-jdk
RUN apt-get install -y graphviz

# Uninstall standard version of GCC
RUN apt-get remove -y gcc-9 g++-9
