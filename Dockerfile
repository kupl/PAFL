FROM ubuntu:22.04

RUN apt-get update \
    && apt-get install -y \
    build-essential \
    clang \
    g++
RUN apt-get install -y \
    cmake \
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

RUN apt-get install -y \
    python3 \
    python3-pip

COPY docker/* ./
RUN pip install --no-cache-dir --upgrade pip \
    && pip install --no-cache-dir \
    pyinstaller

RUN pyinstaller --onefile evaluate.py
RUN pyinstaller --onefile train_and_run.py
RUN pyinstaller --onefile robustness.py
RUN pyinstaller --onefile evalDLFL.py
RUN pyinstaller --onefile makeXLSX.py

RUN cp dist/evaluate dist/train_and_run dist/robustness dist/evalDLFL dist/makeXLSX ./
RUN rm evaluate.spec train_and_run.spec robustness.spec evalDLFL.spec makeXLSX.spec \
    evaluate.py train_and_run.py robustness.py evalDLFL.py makeXLSX.py
RUN rm -rf dist && chmod +x \
    evaluate train_and_run robustness evalDLFL makeXLSX

RUN mkdir --mode=777 /workspace
WORKDIR /workspace
CMD ["/bin/bash"]