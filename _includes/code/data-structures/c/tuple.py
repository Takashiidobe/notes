#!/usr/bin/env python3

types = [
    "bool",
    "int",
    "size_t",
    "float",
    "char",
    "string",
    "signed char",
    "unsigned char",
    "signed short" ,
    "unsigned short",
    "long long int",
    "long double",
]

with open('tuple_dec.h', 'w+') as f:
    for i in range(len(types)):
        for j in range(len(types)):
            f.write(f"tuple({types[i]}, {types[j]});\n")
