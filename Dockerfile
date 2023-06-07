FROM ubuntu:18.04

LABEL author="Ushakoff Matvey 221-329"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qt5-default qtbase5-dev qt5-qmake -y
RUN apt-get install build-essential -y
RUN apt-get install cmake -y

WORKDIR /Ushakoff_221-329
COPY *.cpp ./
COPY *.h ./
COPY *.txt ./

WORKDIR /Ushakoff_221-329/build
RUN cmake ..
RUN make
WORKDIR /Ushakoff_221-329

ENTRYPOINT ["./hallServer"]
