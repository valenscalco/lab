FROM alpine

EXPOSE 5000

RUN apk update && apk add python3
RUN apk add git
RUN git clone https://github.com/valenscalco/lab.git

WORKDIR /lab/alumnos/58103-Scalco-Valentina/TP4/

CMD [ "python3", "try.py" ]
