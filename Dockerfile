FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y \
        build-essential \
        clang \
        vim \
        python3 \
        python3-pip \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/list/*

WORKDIR /opt/pafl
ENV PATH="/opt/pafl/bin:${PATH}"
COPY docker/* Makefile pytree.py ./
COPY include ./include/
COPY src ./src/
COPY externals ./externals/
RUN make release

RUN pip install --no-cache-dir --upgrade pip \
    && pip install --no-cache-dir openpyxl numpy pyinstaller
RUN pyinstaller --onefile cov_eval.py \
    && cp dist/cov_eval ./bin/ \
    && rm cov_eval.spec cov_eval.py && rm -rf dist \
    && chmod +x bin/cov_eval

RUN mkdir --mode=777 /workspace
WORKDIR /workspace
RUN ln -s /workspace/coverage /opt/pafl/coverage \
    && ln -s /workspace/log /opt/pafl/log \
    && ln -s /workspace/cache /opt/pafl/cache
CMD ["/bin/bash"]
