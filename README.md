<div align="center">

# KernelCjson

[简体中文](README-zh.md) or [English](README.md)  

The modifyed [cjson](https://github.com/DaveGamble/cJSON) that able to running on windows kernel

</div>

## notice
### no support float
- The KernelCjson can't parse float something of json.

  Because the operation of float number in kernel is danger.
  
  I was removed anything about float operation in cjson.

- Remove valueint and valuedouble of members in cJSON*.

  The valueulong(type is unsigned long long) replaced the above members.

- If your Driver used C++, please disable C++ release.

  Otherwise,Your Driver will be crash Unscheduled!

## tested
- Win7 [enabled verifier]
- Win10 1903 [enabled verifier]
- Win10 ltsc 2021 [enabled verifier]

## thanks for
- https://github.com/sidyhe/dxx/blob/master/kcrt/kcrtc.c
- https://github.com/kouzhudong/kwinjson
