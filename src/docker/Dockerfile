FROM docker.io/ubuntu:18.04
MAINTAINER Jan Starke <jan.starke@outofbed.org>

COPY neo /root/neo

RUN apt-get -y update ; apt-get install -y --allow-unauthenticated gpg; \
    echo "deb http://ppa.launchpad.net/ocl-dev/intel-opencl/ubuntu bionic main" >> /etc/apt/sources.list; \
    apt-key adv --keyserver keyserver.ubuntu.com --recv-keys C3086B78CC05B8B1; \
    apt-get -y update ; apt-get install -y --allow-unauthenticated cmake git pkg-config ninja-build intel-igc-opencl-dev intel-gmmlib-dev clang-6.0
RUN mkdir /root/build; cd /root/build ; cmake -G Ninja -DBUILD_TYPE=Release -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang-6.0 -DCMAKE_CXX_COMPILER=clang++-6.0 \
    -DDO_NOT_RUN_AUB_TESTS=1 -DDONT_CARE_OF_VIRTUALS=1 ../neo ; ninja -j `nproc`
RUN git clone https://github.com/teeshop/rexgen.git
RUN cd rexgen; git checkout feature/libFuzzer; mkdir build; cd build; cmake .. -DCMAKE_BUILD_TYPE=libFuzzer; make
CMD ["/rexgen/build/src/rexgen/rexgen"]