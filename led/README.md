# LED HLS 示例工程说明

本目录包含一个用于演示 Vitis HLS 流程的简单按键控制 LED 项目，通过 C++ 描述逻辑、自动综合并导出可复用 IP。

- `code/led.cpp`：HLS 顶层函数，读入 4 位按键信号 `key_t`，直接驱动 4 位 LED 输出 `led`，接口使用 `ap_ctrl_hs` 以生成标准 `ap_clk/ap_rst_n`。
- `build/run_hls.tcl`：自动化脚本，负责创建项目、综合、导出 IP，并将生成的压缩包解压到 `ip/<top_name>` 目录。
- `build/`：综合过程中生成的中间文件与日志。
- `ip/`：执行脚本后得到的 IP 核解压目录，可直接给后续工程引用。
- `led_key.bit`：示例比特流文件，用于在板卡上验证按键→LED 映射功能。

在当前目录执行 `vitis_hls -f build/run_hls.tcl`，即可快速重新综合并导出最新的 LED 控制 IP。
