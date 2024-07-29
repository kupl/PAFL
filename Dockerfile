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
        cmake \
        vim \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/list/*

WORKDIR /opt/PAFL
COPY build/cmake.sh build/make.sh ./build/
COPY example ./example/
COPY include ./include/
COPY src ./src/
COPY externals ./externals/
COPY CMakeLists.txt ./
RUN chmod +x ./build/cmake.sh ./build/make.sh
RUN ./build/cmake.sh && ./build/make.sh
ENV PATH="/opt/PAFL/build/release:${PATH}"

COPY docker/evaluate.py ./
RUN pip install --no-cache-dir --upgrade pip \
    && pip install --no-cache-dir \
        openpyxl \
        numpy \
        pyinstaller
RUN pyinstaller --onefile evaluate.py \
    && cp dist/evaluate ./ \
    && rm evaluate.spec evaluate.py && rm -rf dist \
    && chmod +x evaluate
ENV PATH="/opt/PAFL/:${PATH}"

COPY docker/scripts ./scripts/
RUN rm -f ./scripts/checkout_*.sh
RUN chmod +x ./scripts/*
ENV PATH="/opt/PAFL/scripts:${PATH}"

RUN mkdir --mode=777 /workspace
WORKDIR /workspace
CMD ["/bin/bash"]
