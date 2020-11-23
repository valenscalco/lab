FROM python:3.7

RUN git clone https://github.com/valenscalco/lab.git
COPY requirements.txt /comp2/lab/alumnoc/58103-Scalco-Valentina/TP4
WORKDIR /comp2/lab/alumnoc/58103-Scalco-Valentina/TP4


RUN pip install -r requirements.txt
RUN pip install parameterized

CMD [ "python3.7", "try.py"]