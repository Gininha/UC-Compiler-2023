#!/bin/sh
./build.sh
./uccompiler < teste_bonk.c > teste_bonk.ll
lli teste_bonk.ll
