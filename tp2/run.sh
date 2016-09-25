#!/bin/bash

make -C backend

echo "Iniciando..."

./backend/backend 4 5 | sed -e 's/^/[Backend] /' &
python2 ./frontend/frontend.py 2>&1 | sed -e 's/^/[Frontend] /'

