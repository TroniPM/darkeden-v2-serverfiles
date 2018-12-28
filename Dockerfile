##########################################################################
########################                         #########################
######################## DOCKER FILE DARKEDEN V2 #########################
########################                         #########################
##########################################################################

# WRITTEN BY: TroniPM
# CONTRIBUTIONS: Softon, and no one yet.
# DATE: 19/12/2018

##########################################################################
##################################      ##################################
################################## INIT ##################################
##################################      ##################################
##########################################################################
#it's really important image be i386/32 bits architecture
FROM i386/ubuntu:18.04

LABEL maintainer="paulomatew@gmail.com"

RUN apt update && apt install -y \
    --no-install-recommends \
    gcc \
    lua5.1 \
    build-essential \
    libcppunit-dev \
    zlib1g \
    libxerces-c-dev \
    #libstdc++6-4.7-dev \
    #libstdc++-4.8-dev \
    #nano \
    locate \
    && rm -rf /var/lib/apt/lists/* 

COPY vs.tar.xz /home/

RUN mkdir /home/darkeden && tar -xJf /home/vs.tar.xz -C /home/darkeden && rm /home/vs.tar.xz

#CHAMAR OS MAKE
#CMD cd /home/darkeden && make && /bin/bash



