FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y \
        build-essential \
        clang \
        g++
RUN apt-get install -y \
        python3 \
        python3-pip
RUN apt-get install -y \
        vim \
        cmake \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/list/*

WORKDIR /opt/pafl
ENV PATH="/opt/pafl/build/release:${PATH}"
COPY build/cmake.sh build/make.sh ./build/
COPY docker/* CMakeLists.txt ./
COPY include ./include/
COPY src ./src/
COPY externals ./externals/

RUN chmod +x ./build/cmake.sh ./build/make.sh
RUN ./build/cmake.sh && ./build/make.sh

RUN pip install --no-cache-dir --upgrade pip \
    && pip install --no-cache-dir openpyxl numpy pyinstaller
RUN pyinstaller --onefile evaluate.py \
    && cp dist/evaluate ./ \
    && rm evaluate.spec evaluate.py && rm -rf dist \
    && chmod +x evaluate

RUN mkdir --mode=777 /workspace
WORKDIR /workspace
# RUN ln -s /workspace/profile /opt/pafl/profile
CMD ["/bin/bash"]
