# HLS优化教程(二) - 数组优化

## 1. 课程目标
- 理解HLS中数组优化的必要性
- 掌握Array Partition的三种模式
- 学会分析和解决内存访问瓶颈

## 2. 基础知识
### 2.1 为什么需要数组优化
- BRAM的端口限制
- 并行访问的需求
- 内存带宽瓶颈

### 2.2 Array Partition的三种模式
1. **Block**: 按块分割
2. **Cyclic**: 循环分割
3. **Complete**: 完全分割为寄存器

## 3. 实战案例 - 矩阵乘法
基础实现:
```cpp
void matrix_multiply(data_t A[SIZE][SIZE], data_t B[SIZE][SIZE], 
                    data_t C[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            data_t sum = 0;
            for(int k = 0; k < SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}
```

### 3.1 性能瓶颈分析
- 内存访问模式
- 端口数量限制
- 并行化机会

### 3.2 Block分割优化
```cpp
void matrix_multiply_block(data_t A[SIZE][SIZE], data_t B[SIZE][SIZE], 
                         data_t C[SIZE][SIZE]) {
    #pragma HLS ARRAY_PARTITION variable=A dim=2 type=block factor=4
    #pragma HLS ARRAY_PARTITION variable=B dim=1 type=block factor=4
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            #pragma HLS PIPELINE II=1
            data_t sum = 0;
            for(int k = 0; k < SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}
```

### 3.3 Cyclic分割优化
```cpp
void matrix_multiply_cyclic(data_t A[SIZE][SIZE], data_t B[SIZE][SIZE], 
                          data_t C[SIZE][SIZE]) {
    #pragma HLS ARRAY_PARTITION variable=A dim=2 type=cyclic factor=4
    #pragma HLS ARRAY_PARTITION variable=B dim=1 type=cyclic factor=4
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            #pragma HLS PIPELINE II=1
            data_t sum = 0;
            for(int k = 0; k < SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}
```

## 4. 优化策略指导
### 4.1 选择分割模式
1. **Block模式**:
   - 适合局部性强的访问模式
   - 减少地址计算开销
   - 适合大规模数组

2. **Cyclic模式**:
   - 适合跨步访问模式
   - 有利于负载均衡
   - 适合规则的访问模式

3. **Complete模式**:
   - 最大化并行性
   - 适合小规模数组
   - 转换为寄存器实现

### 4.2 分析和优化步骤
1. 分析内存访问模式
2. 确定瓶颈位置
3. 选择合适的分割方式
4. 验证性能提升

## 5. 常见问题与解决方案
### 5.1 资源使用过高
- 降低分割因子
- 使用Block而非Complete
- 只对关键数组进行分割

### 5.2 性能提升不明显
- 检查访问模式是否匹配
- 确认是否有其他瓶颈
- 考虑组合其他优化手段

## 6. 实验结果对比
| 优化方式 | Latency | II | BRAM | DSP | LUT | FF |
|---------|---------|-------|------|-----|-----|-------|
| 基础版本 | 16384 | 4 | 3 | 4 | 200 | 300 |
| Block(4) | 4096 | 1 | 12 | 16 | 600 | 800 |
| Cyclic(4)| 4096 | 1 | 12 | 16 | 650 | 850 |

## 7. 总结
1. Array Partition是解决内存访问瓶颈的关键优化手段
2. 需要根据访问模式选择合适的分割方式
3. 注意权衡资源使用和性能提升
4. 通常需要配合Pipeline等其他优化指令使用

## 8. 课后练习
1. 修改矩阵乘法示例,尝试不同的分割因子
2. 对比Block和Cyclic模式在不同场景下的效果
3. 尝试完全分割小规模数组,观察资源使用变化