FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y \
        build-essential \
        clang \
        vim \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/list/*

WORKDIR /opt/pafl
ENV PATH="/workspace/pafl/bin:${PATH}"
COPY ./docker/config ./docker/methods Makefile ./
COPY include ./include/
COPY src ./src/
COPY externals ./externals/
RUN make release

RUN mkdir --mode=777 /workspace
WORKDIR /workspace
RUN mkdir --mode=777 /workspace/coverage /workspace/log
RUN mkdir /opt/pafl/coverage /opt/pafl/log
RUN ln -s /opt/pafl/coverage /workspace/coverage
RUN ln -s /opt/pafl/log /workspace/log
CMD ["/bin/bash"]
