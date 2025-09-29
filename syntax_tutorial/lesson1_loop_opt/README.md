# 循环优化示例说明

本示例展示了HLS中常用的循环优化指令的使用方法和效果。

## 主要优化指令

### 1. 循环展开（UNROLL）
```c++
#pragma HLS UNROLL factor=N
```
- 作用：将循环展开N倍，实现并行执行
- 特点：
  - 增加硬件资源使用
  - 提高并行度
  - 需要相应的数组分割支持

### 2. 循环流水线（PIPELINE）
```c++
#pragma HLS PIPELINE II=N
```
- 作用：实现循环的流水线执行
- 特点：
  - II值表示启动间隔
  - 降低延迟
  - 提高吞吐量

### 3. 组合优化
- 展开+流水线可以同时使用
- 需要注意资源使用和时序约束

## 示例代码说明

### vector_add_basic
- 基础实现，无优化
- 用作对比基准

### vector_add_unroll
- 使用循环展开优化
- factor=2展示适度并行
- 配合数组分割使用

### vector_add_pipeline
- 使用流水线优化
- II=1实现最大吞吐量

### vector_add_optimized
- 组合使用展开和流水线
- 展示优化叠加效果

## 性能对比

各版本的预期性能：
1. Basic: 延迟 = 1024 周期
2. Unroll: 延迟 ≈ 512 周期
3. Pipeline: 延迟 ≈ 1024+II 周期
4. Optimized: 最佳性能

## 使用说明

1. 运行HLS综合：
```bash
vitis_hls run_hls.tcl
```

2. 查看各版本的性能报告：
- 检查延迟
- 比较资源使用
- 分析优化效果