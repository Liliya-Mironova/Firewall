#!/bin/bash

sudo fuser -k 80/tcp

sudo /opt/nginx-1.13.9/sbin/nginx
