# 删除之前运行产生的日志文件，清理工作环境
exec sh -c "rm -f flex*.log"

puts "开始综合basic版本..."
open_project stream_prj_basic
set_top process_data_basic
add_files stream_process.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp stream_prj_basic/solution1/syn/report/csynth.rpt result/basic_csynth.rpt"
close_project

puts "开始综合dataflow版本..."
open_project stream_prj_dataflow
set_top process_data_dataflow
add_files stream_process.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp stream_prj_dataflow/solution1/syn/report/csynth.rpt result/dataflow_csynth.rpt"
close_project



puts "所有版本综合完成！"