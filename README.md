<div align="center">

# KernelCjson

[简体中文](README-zh.md) or [English](README.md)  

This project was modifyed by [Cjson](https://github.com/DaveGamble/cJSON).

That is a good json library.

## Then now,The cjson can running on kernel!

</div>

## notice
### not support float
- The KernelCjson can't parse float something of json.

  Because the operation float number in kernel is danger
  
  I was remove anything about float operation in cjson.

- The anything greater than maximum of int of number was be saved in cJSON->valuedouble.
  
  I was modifyed the member valuedouble to valueulong(he's type is unsigned long long).

### not enough security
- Don't to use this lib direct.

- I was not test something modifyed functions of KernelCjson.

- I don't promise it is stable,But i'm using good now.(xixi)

## thank for
- https://github.com/sidyhe/dxx/blob/master/kcrt/kcrtc.c
- https://github.com/kouzhudong/kwinjson
