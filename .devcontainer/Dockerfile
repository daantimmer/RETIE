FROM gcc:10

RUN apt-get --allow-releaseinfo-change update \
    # these are required to download cmake and gcc-arm-none-eabi from artifactory
    && apt-get -y --no-install-recommends install wget ca-certificates\
    # these are required to unpack/install cmake and gcc-arm-none-eabi
    && apt-get -y --no-install-recommends install lbzip2 libncurses5\
    # this is required for signing git commits
    && apt-get -y --no-install-recommends install gnupg2\
    # ninja is used as the build tool
    && apt-get -y --no-install-recommends install ninja-build \
    #  download and install cmake
    && wget -q -O /cmake-install.sh --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.24.0-rc2/cmake-3.24.0-rc2-linux-x86_64.sh \
    && chmod u+x /cmake-install.sh \
    && mkdir /usr/bin/cmake \
    && /cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
    && rm /cmake-install.sh\
    # download and unpack gcc-arm-none-eabi v10
    && wget -q -O /gcc-arm-none-eabi.tar.bz2 --no-check-certificate https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \
    && tar -xf gcc-arm-none-eabi.tar.bz2 \
    && rm /gcc-arm-none-eabi.tar.bz2 \
    # this is required for speeding up continious recompilations of the same files
    && apt-get -y --no-install-recommends install ccache \
    # remove all items that are not required while running the container
    && apt-get clean \
    && apt-get -y remove wget lbzip2 \
    && rm -rf /var/lib/apt/lists/*  \
    && rm -rf /root/.gnupg

ENV PATH "/gcc-arm-none-eabi-10.3-2021.10/bin:/usr/lib/ccache:/usr/bin/cmake/bin:$PATH"