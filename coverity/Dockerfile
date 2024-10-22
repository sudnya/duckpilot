# Base container name
ARG BASE_NAME=python:3.11

FROM $BASE_NAME as base

ARG PACKAGE_NAME="duckpilot-coverity"

# Install python packages
WORKDIR /app/${PACKAGE_NAME}
COPY ./requirements.txt /app/${PACKAGE_NAME}/requirements.txt

RUN pip install -r requirements.txt

# Copy all files to the container
COPY scripts /app/${PACKAGE_NAME}/scripts
COPY eval /app/${PACKAGE_NAME}/eval
COPY dataset /app/${PACKAGE_NAME}/dataset
COPY dataprep /app/${PACKAGE_NAME}/dataprep
COPY visualize /app/${PACKAGE_NAME}/visualize
COPY train /app/${PACKAGE_NAME}/train
#COPY rag /app/${PACKAGE_NAME}/rag
#COPY reasoning /app/${PACKAGE_NAME}/reasoning

WORKDIR /app/${PACKAGE_NAME}



