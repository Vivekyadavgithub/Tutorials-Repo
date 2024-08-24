FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libxkbcommon-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    xorg-dev \
    libwayland-dev 

RUN git clone https://github.com/glfw/glfw.git /glfw

WORKDIR /glfw

RUN mkdir build/ 

WORKDIR /glfw/build

RUN cmake -DCMAKE_BUILD_TYPE=Release ..

RUN make && make install

WORKDIR /app



