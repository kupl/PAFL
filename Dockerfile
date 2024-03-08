FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y \
        build-essential \
        clang \
        vim \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/list/*

RUN mkdir --mode=777 /workspace
WORKDIR /workspace/pafl
ENV PATH="/workspace/pafl/bin:${PATH}"
COPY ./docker/config ./docker/methods Makefile ./
COPY include ./include/
COPY src ./src/
COPY externals ./externals/
RUN make release
CMD ["/bin/bash"]
