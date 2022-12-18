<div align="center">

# KernelCjson

[简体中文](README-zh.md) or [English](README.md)  

魔改版[Cjson](https://github.com/DaveGamble/cJSON),可以运行在Windows内核中

</div>

## 注意
### 不支持浮点数
- KernelCjson不支持解析json中的浮点数数据

  因为在驱动中操作浮点数还是有点危险的
  
  所以我移除了cjson中所有关于浮点数的操作

- cjson中超过int最大界限的数值会保存为浮点数，即保存在cJSON->valuedouble
  
  所以我经过了些修改讲这个成员修改成cJSON->valueulong（虽然叫ulong但他是unisgned long long 类型 = =）

### 不够安全
- 不要直接挪用此库

- 有些修改过的函数我并没有测试

- 所以我不保证可以稳定执行，虽然我自己用着是挺稳定的（嘻嘻）

## 感谢
- https://github.com/sidyhe/dxx/blob/master/kcrt/kcrtc.c
- https://github.com/kouzhudong/kwinjson
