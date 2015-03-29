FROM ubuntu:14.10

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get upgrade -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y clang git unzip wget libc++-dev binutils make automake libtool subversion cmake curl

RUN git config --global user.email "docker@example.com"
RUN git config --global user.name docker

ADD documentation/ /opt/principia/documentation/

WORKDIR /opt/principia/
RUN git clone "https://github.com/google/protobuf.git" --depth 1 -b "v3.0.0-alpha-1"
WORKDIR /opt/principia/protobuf
RUN git am "../documentation/Setup Files/protobuf.patch"
RUN ./autogen.sh
RUN ./configure CC=clang CXX=clang++ CXXFLAGS='-fPIC -m64 -std=c++11 -stdlib=libc++ -O3 -g' LDFLAGS='-stdlib=libc++'
RUN make -j 8

WORKDIR /opt/principia/
RUN git clone https://github.com/Norgg/glog
WORKDIR /opt/principia/glog
# RUN patch -p 1 -i "../documentation/Setup Files/glog.patch"; true
RUN ./configure CC=clang CXX=clang++ CXXFLAGS='-fPIC -m64 -std=c++11 -stdlib=libc++ -O3 -g' LDFLAGS='-stdlib=libc++'
RUN make -j 8

WORKDIR /opt/principia/
RUN svn checkout http://googlemock.googlecode.com/svn/trunk/ gmock
RUN svn checkout http://googletest.googlecode.com/svn/trunk/ gtest

WORKDIR /opt/principia/gtest/
RUN wget "https://googletest.googlecode.com/issues/attachment?aid=4640000000&name=GetThreadCountForLinux.patch&token=ABZ6GAdR6MB7HLYD00TNsyrZ2EonGnqpWQ%3A1427585369726" -O thread_count.patch
RUN patch -p 0 -i thread_count.patch

WORKDIR /opt/principia/gmock
RUN patch -p 1 -i "../documentation/Setup Files/gmock.patch"; true

WORKDIR /opt/principia
RUN git clone https://github.com/pleroy/benchmark
WORKDIR /opt/principia/benchmark
RUN cmake .
RUN make

WORKDIR /opt/principia
RUN git clone "https://chromium.googlesource.com/chromium/src.git" chromium -n --depth 1 -b "40.0.2193.1"
# $GitPromptSettings.RepositoriesInWhichToDisableFileStatus += join-path  (gi -path .).FullName chromium
WORKDIR /opt/principia/chromium
RUN git config core.sparsecheckout true
RUN cp "../documentation/Setup Files/chromium_sparse_checkout.txt" .git/info/sparse-checkout
RUN git checkout
RUN git am "../documentation/Setup Files/chromium.patch"

ENV ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-3.5

WORKDIR /opt/principia/src
CMD make -j4 DEP_DIR=..
