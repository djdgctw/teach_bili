# 循环展开

```c++
#pragma HLS unroll factor=2   // 展开因子为2,意思是把这个循环展开为两份，同时并行，需要对应的bram也进行了分组
#pragma HLS pipeline II=1  //隔一个时钟周期就启动一次循环，可以和上面的指令一起用，达到并行效果同时减少interval
```

```c++
//循环分割，适用于大型数组的部分并行，消耗BRAM，使用该指令如果是小数组然后被分割可能导致存储资源使用不充分
#pragma HLS array_partition variable=M dim=2 cyclic factor=2  //表示对矩阵 `M` 的第二维进行循环分区，数组的每行分成两份。这有助于提高并行访问的效率。(M为二维数组)
#pragma HLS array_partition variable=V_In cyclic factor=2 //输入向量 `V_In` 进行循环分区，组的每行分成两份(V为一维数组)
#pragma HLS LOOP_TRIPCOUNT min = 1 max = MAXHEIGHT //循环最大最小

```

```c++
//array_reshape的优势:形成较大的存储块,更容易高效映射到FPGA资源
//下面的的指令是把A数组在第二维完全展开重塑，把所有东西放在同一个块，同时开行数个输出口
#pragma HLS ARRAY_RESHAPE variable=A complete dim=2
 #pragma HLS ARRAY_RESHAPE variable=B complete dim=1
//绑定URAM

#pragma HLS bind_storage variable = flow_level_1 type = FIFO impl = URAM //该指令不能指定深度，深度在命名数组时直接指定即可
```

#### 经验法则

当对多维矩阵进行分块时，应该：

1. 选择通过常量或同一变量访问的维度进行分块
2. 避免对通过不同变量访问的维度进行分块

实际应用示例

- Xilinx BRAM最小容量为**18 Kbits**
- 原始矩阵示例：[1024][4]的4-bit数组
- 不同实现方式的效果：
  - 原始方式：可放入单个BRAM（4Kbit x 4）
  - array_partition：需要4个1Kbit x 4存储单元
  - array_reshape：可优化为1Kbit x 16，适合单个BRAM

```c++
//下面的指令比较消耗LUT+FIFO，适用于小型数组,不消耗bram
#pragma HLS array_partition variable=M dim=2 complete
//表示完全分区，即将这一维的每个元素分到不同的BRAM中,例如，对于8x8的矩阵M，这条指令会将每一行的8个元素分散到8个不同的BRAM中，使得可以同时访问一行中的所有元素。
#pragma HLS array_partition variable=V_In complete
//将整个数组完全分区，即每个元素都存储在独立的寄存器中,这样可以同时访问V_In中的所有元素
int A[10][10];
#pragma HLS array_partition variable=A complete dim=0
// dim=0表示对所有维度进行完全分区,即每个元素都存储在独立的寄存器FF(触发器)中
#pragma HLS array_partition variable=<数组名> type=<分割类型> factor=<分割因子> dim=<维度>
```

```c++
// 对于已知范围的循环，限定循环最大最小数
#pragma HLS LOOP_TRIPCOUNT min=actual_min max=actual_max

```

- 有递归时使用`#pragma HLS pipeline II=S`要注意递归的加法器或者乘法器的运行时间周期，当对应S时一般才是最佳

# 流水线命令

```c++
//使用dataflow的流水线总时间间隔取决于时间最长的模块，建议主函数必须使用
#pragma HLS dataflow
//配置深度
#pragma HLS STREAM variable = strmIt depth = 64
```

- Dataflow指令：
  - 针对粗粒度操作进行流水线化
  - 通过数据握手动态控制
  - 适用于大数据块操作 
  - FIFO适用于顺序访问模式
  - 乒乓操作适用于非顺序访问模式
  - 当按**顺序生成和使用数据时，FIFO通常是最佳选择**，而当没有这种**常规数据访问模式时，用乒乓操作来缓存数据是更好的选择。**
  - `dataflow` 指令可以提高并行性，但最终性能仍然受限于最慢的部分，**可以对比较快的部分进行资源优化**，

# 先决条件指令集

```c++
#pragma HLS DEPENDENCE variable=hist inter RAW distance=2
//愿意接受附加的先决条件才行，一般，没用
#pragma HLS DEPENDENCE variable=hist intra RAW false
//false：声明这种依赖不存在
```

1. 基本组成：

- `variable=hist`：指定要处理的变量（数组）
- `inter`：指定循环迭代间的依赖关系
- `RAW`：Read After Write（写后读）依赖类型

2. 依赖类型解释：

- RAW (Read After Write)：写入后读取
- WAR (Write After Read)：读取后写入
- WAW (Write After Write)：写入后写入

3. 指令作用：

- 告诉HLS工具hist数组在不同循环迭代间没有RAW依赖
- 允许编译器进行更激进的优化

4. distance=2 的具体含义：

- 表示相隔2次循环迭代才可能出现相同地址访问
- 即第i次和第i+2次迭代才可能访问相同位置
- 连续的迭代（i和i+1）保证不会访问相同位置

5. **在同一个迭代循环中，读取和写入访问是在不同地址中进行的。**这两个地址都依赖于输入数据，因此可以指向hist数组中的任何单独像素。**因此，Vivado@HLS假定这两种访问都可以访问相同的位置**，并以交替的周期顺序对数组进行读取和写入操作，**则循环的II =2。**
   - 如果代码中没有这种情况，就可以用先决指令`#pragma HLS DEPENDENCE variable=hist intra RAW false`来加速了,此处示例为读后写

```c++
//禁止内联
#pragma HLS INLINE on
```

```c++
//禁止循环展平,当内部已经流水化时，不展开可能更好
#pragma HLS LOOP_FLATTEN OFF
```

# URAM

**当你选择使用uram，那么对应中间的数据流的就得全部使用Uram，要不然时间不一样会寄**



\# 启动时加载指定工程 

```tcl
hls -p /home/fyt/HLS_prj/optical_base/build/hls_all_build.prj &
```

