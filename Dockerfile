FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y \
        build-essential \
        clang \
        vim \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/list/*

WORKDIR /opt/pafl
ENV PATH="/opt/pafl/bin:${PATH}"
COPY ./docker/* ./
COPY Makefile ./
COPY include ./include/
COPY src ./src/
COPY externals ./externals/
RUN make \
    && mkdir -p /opt/pafl/bin \
    && cp main /opt/pafl/bin/pafl

RUN mkdir --mode=777 /workspace
WORKDIR /workspace
CMD ["/bin/bash"]
