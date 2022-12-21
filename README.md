<div align="center">

# KernelCjson

[简体中文](README-zh.md) or [English](README.md)  

The modifyed [cjson](https://github.com/DaveGamble/cJSON) that can running on windows kernel

</div>

## notice
### no support float
- The KernelCjson can't parse float something of json.

  Because the operation float number in kernel is danger.
  
  I was remove anything about float operation in cjson.

- Remove valueint and valuedouble of members in cJSON* 

  The valueulong(type is unsigned long long) replaced the above members

### no enough security
- Don't use this lib direct.

- I was not test something modifyed functions of KernelCjson.

- I don't promise it is stable,But i'm using good now.(xixi)

## thank for
- https://github.com/sidyhe/dxx/blob/master/kcrt/kcrtc.c
- https://github.com/kouzhudong/kwinjson
