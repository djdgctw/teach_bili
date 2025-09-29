# 数组优化示例说明

本示例展示了HLS中数组优化指令的使用方法和效果，主要包括array_partition和array_reshape两种优化方式。

## 主要优化指令

### 1. 数组分区（ARRAY_PARTITION）

```c++
#pragma HLS ARRAY_PARTITION variable=array_name dim=N complete
#pragma HLS ARRAY_PARTITION variable=array_name dim=N cyclic factor=F
```

#### 分区类型
1. **完全分区（complete）**
   - 将数组完全分解为独立元素
   - 最大化并行访问能力
   - 消耗更多FPGA资源（FF/LUT）

2. **循环分区（cyclic）**
   - 按指定因子循环分组
   - 在并行度和资源之间平衡
   - 适用于部分并行化需求

### 2. 数组重构（ARRAY_RESHAPE）

```c++
#pragma HLS ARRAY_RESHAPE variable=array_name dim=N complete
#pragma HLS ARRAY_RESHAPE variable=array_name dim=N cyclic factor=F
```

#### 重构特点
- 合并存储块，保持数据位宽
- 提供多个并行访问端口
- 更好地映射到FPGA资源

## 优化策略选择

### 何时使用ARRAY_PARTITION
1. 需要最大并行访问能力
2. 资源充足
3. 小型数组或关键路径数据

### 何时使用ARRAY_RESHAPE
1. 需要在存储效率和访问并行性之间平衡
2. BRAM资源受限
3. 大型数组优化

## BRAM使用考虑

### Xilinx BRAM特点
- 最小容量：18 Kbits
- 双端口访问
- 可配置位宽

### 优化建议
1. 根据数组大小选择合适策略
2. 考虑BRAM利用率
3. 注意访问模式

## 示例代码说明

### matrix_multiply_basic
- 基础实现，无优化
- 用作对比基准

### matrix_multiply_partition
- 使用完全分区
- 最大化并行访问

### matrix_multiply_cyclic
- 使用循环分区
- 平衡资源和性能

### matrix_multiply_reshape
- 使用数组重构
- 优化存储器使用

## 性能分析

针对8x8矩阵乘法：

1. 基础版本
   - 延迟：O(N³)
   - BRAM：最小使用

2. 完全分区版本
   - 最大并行度
   - 高资源消耗
   - 最低延迟

3. 循环分区版本
   - 部分并行
   - 中等资源消耗
   - 平衡的性能

4. 重构版本
   - 高效BRAM使用
   - 多端口访问
   - 优化的存储结构

## 使用说明

1. 运行HLS综合：
```bash
vitis_hls run_hls.tcl
```

2. 分析优化效果：
   - 查看资源报告
   - 比较延迟数据
   - 检查BRAM使用情况