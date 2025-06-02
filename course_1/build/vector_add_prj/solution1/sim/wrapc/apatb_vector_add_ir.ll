; ModuleID = '/home/fyt/teach_bili/course_1/build/vector_add_prj/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_uint<32>" = type { %"struct.ap_int_base<32, false>" }
%"struct.ap_int_base<32, false>" = type { %"struct.ssdm_int<32, false>" }
%"struct.ssdm_int<32, false>" = type { i32 }

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_vector_add_ir(%"struct.ap_uint<32>"* noalias nocapture nonnull readonly %a, %"struct.ap_uint<32>"* noalias nocapture nonnull %c, i32 %size) local_unnamed_addr #0 {
entry:
  %a_copy = alloca [256 x i32], align 512
  %c_copy = alloca [256 x i32], align 512
  %0 = bitcast %"struct.ap_uint<32>"* %a to [256 x %"struct.ap_uint<32>"]*
  %1 = bitcast %"struct.ap_uint<32>"* %c to [256 x %"struct.ap_uint<32>"]*
  call fastcc void @copy_in([256 x %"struct.ap_uint<32>"]* nonnull %0, [256 x i32]* nonnull align 512 %a_copy, [256 x %"struct.ap_uint<32>"]* nonnull %1, [256 x i32]* nonnull align 512 %c_copy)
  %2 = getelementptr [256 x i32], [256 x i32]* %a_copy, i32 0, i32 0
  %3 = getelementptr [256 x i32], [256 x i32]* %c_copy, i32 0, i32 0
  call void @apatb_vector_add_hw(i32* %2, i32* %3, i32 %size)
  call void @copy_back([256 x %"struct.ap_uint<32>"]* %0, [256 x i32]* %a_copy, [256 x %"struct.ap_uint<32>"]* %1, [256 x i32]* %c_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([256 x %"struct.ap_uint<32>"]* noalias readonly "unpacked"="0", [256 x i32]* noalias nocapture align 512 "unpacked"="1.0.0.0", [256 x %"struct.ap_uint<32>"]* noalias readonly "unpacked"="2", [256 x i32]* noalias nocapture align 512 "unpacked"="3.0.0.0") unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a256struct.ap_uint<32>.9.13"([256 x i32]* align 512 %1, [256 x %"struct.ap_uint<32>"]* %0)
  call fastcc void @"onebyonecpy_hls.p0a256struct.ap_uint<32>.9.13"([256 x i32]* align 512 %3, [256 x %"struct.ap_uint<32>"]* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([256 x %"struct.ap_uint<32>"]* noalias "unpacked"="0", [256 x i32]* noalias nocapture readonly align 512 "unpacked"="1.0.0.0", [256 x %"struct.ap_uint<32>"]* noalias "unpacked"="2", [256 x i32]* noalias nocapture readonly align 512 "unpacked"="3.0.0.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a256struct.ap_uint<32>"([256 x %"struct.ap_uint<32>"]* %0, [256 x i32]* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0a256struct.ap_uint<32>"([256 x %"struct.ap_uint<32>"]* %2, [256 x i32]* align 512 %3)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0a256struct.ap_uint<32>"([256 x %"struct.ap_uint<32>"]* noalias "unpacked"="0", [256 x i32]* noalias nocapture readonly align 512 "unpacked"="1.0.0.0") unnamed_addr #3 {
entry:
  %2 = icmp eq [256 x %"struct.ap_uint<32>"]* %0, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [256 x i32], [256 x i32]* %1, i64 0, i64 %for.loop.idx1
  %dst.addr.0.0.06 = getelementptr [256 x %"struct.ap_uint<32>"], [256 x %"struct.ap_uint<32>"]* %0, i64 0, i64 %for.loop.idx1, i32 0, i32 0, i32 0
  %3 = load i32, i32* %src.addr.0.0.05, align 4
  store i32 %3, i32* %dst.addr.0.0.06, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 256
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0a256struct.ap_uint<32>.9.13"([256 x i32]* noalias nocapture align 512 "unpacked"="0.0.0.0", [256 x %"struct.ap_uint<32>"]* noalias readonly "unpacked"="1") unnamed_addr #3 {
entry:
  %2 = icmp eq [256 x %"struct.ap_uint<32>"]* %1, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [256 x %"struct.ap_uint<32>"], [256 x %"struct.ap_uint<32>"]* %1, i64 0, i64 %for.loop.idx1, i32 0, i32 0, i32 0
  %dst.addr.0.0.06 = getelementptr [256 x i32], [256 x i32]* %0, i64 0, i64 %for.loop.idx1
  %3 = load i32, i32* %src.addr.0.0.05, align 4
  store i32 %3, i32* %dst.addr.0.0.06, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 256
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

declare void @apatb_vector_add_hw(i32*, i32*, i32)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([256 x %"struct.ap_uint<32>"]* noalias "unpacked"="0", [256 x i32]* noalias nocapture readonly align 512 "unpacked"="1.0.0.0", [256 x %"struct.ap_uint<32>"]* noalias "unpacked"="2", [256 x i32]* noalias nocapture readonly align 512 "unpacked"="3.0.0.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a256struct.ap_uint<32>"([256 x %"struct.ap_uint<32>"]* %2, [256 x i32]* align 512 %3)
  ret void
}

define void @vector_add_hw_stub_wrapper(i32*, i32*, i32) #4 {
entry:
  %3 = alloca [256 x %"struct.ap_uint<32>"]
  %4 = alloca [256 x %"struct.ap_uint<32>"]
  %5 = bitcast i32* %0 to [256 x i32]*
  %6 = bitcast i32* %1 to [256 x i32]*
  call void @copy_out([256 x %"struct.ap_uint<32>"]* %3, [256 x i32]* %5, [256 x %"struct.ap_uint<32>"]* %4, [256 x i32]* %6)
  %7 = bitcast [256 x %"struct.ap_uint<32>"]* %3 to %"struct.ap_uint<32>"*
  %8 = bitcast [256 x %"struct.ap_uint<32>"]* %4 to %"struct.ap_uint<32>"*
  call void @vector_add_hw_stub(%"struct.ap_uint<32>"* %7, %"struct.ap_uint<32>"* %8, i32 %2)
  call void @copy_in([256 x %"struct.ap_uint<32>"]* %3, [256 x i32]* %5, [256 x %"struct.ap_uint<32>"]* %4, [256 x i32]* %6)
  ret void
}

declare void @vector_add_hw_stub(%"struct.ap_uint<32>"*, %"struct.ap_uint<32>"*, i32)

attributes #0 = { inaccessiblemem_or_argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
