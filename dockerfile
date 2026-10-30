
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libxfixes-dev \
    libxss-dev \
    libxkbcommon-dev \
    libwayland-dev \
    libdecor-0-dev \
    libasound2-dev \
    libpulse-dev \
    libudev-dev \
    libdbus-1-dev \
    libibus-1.0-dev \
    libdrm-dev \
    libgbm-dev \
    libpipewire-0.3-dev \
    libusb-1.0-0-dev \
    libfreetype-dev \
    && rm -rf /var/lib/apt/lists/*

# Baixar, compilar e instalar SDL3
RUN git clone --depth 1 \
    https://github.com/libsdl-org/SDL.git /tmp/SDL \
    && cmake -S /tmp/SDL -B /tmp/SDL/build \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DSDL_SHARED=ON \
        -DSDL_STATIC=OFF \
        -DSDL_X11=ON \
        -DSDL_WAYLAND=ON \
        -DSDL_TESTS=OFF \
        -DSDL_EXAMPLES=OFF \
        -DSDL_X11_XTEST=OFF \
    && cmake --build /tmp/SDL/build \
    && cmake --install /tmp/SDL/build \
    && rm -rf /tmp/SDL

RUN ldconfig

WORKDIR /workspace

CMD ["bash"]
