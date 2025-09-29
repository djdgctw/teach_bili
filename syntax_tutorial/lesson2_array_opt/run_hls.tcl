# 删除之前运行产生的日志文件，清理工作环境
exec sh -c "rm -f flex*.log"

puts "开始综合basic版本..."
open_project matrix_prj_basic
set_top matrix_multiply_basic
add_files matrix_multiply.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp matrix_prj_basic/solution1/syn/report/csynth.rpt result/basic_csynth.rpt"
close_project

puts "开始综合partition版本..."
open_project matrix_prj_partition
set_top matrix_multiply_partition
add_files matrix_multiply.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp matrix_prj_partition/solution1/syn/report/csynth.rpt result/partition_csynth.rpt"
close_project

puts "开始综合cyclic版本..."
open_project matrix_prj_cyclic
set_top matrix_multiply_cyclic
add_files matrix_multiply.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp matrix_prj_cyclic/solution1/syn/report/csynth.rpt result/cyclic_csynth.rpt"
close_project

puts "开始综合reshape版本..."
open_project matrix_prj_reshape
set_top matrix_multiply_reshape
add_files matrix_multiply.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu9eg-ffvb1156-2-e}
create_clock -period 10 -name default
csynth_design
exec sh -c "cp matrix_prj_reshape/solution1/syn/report/csynth.rpt result/reshape_csynth.rpt"
close_project

puts "所有版本综合完成！"