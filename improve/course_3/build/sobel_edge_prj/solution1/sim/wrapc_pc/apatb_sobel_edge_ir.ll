; ModuleID = '/home/fyt/teach_bili/course_3/build/sobel_edge_prj/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_uint<8>" = type { %"struct.ap_int_base<8, false>" }
%"struct.ap_int_base<8, false>" = type { %"struct.ssdm_int<8, false>" }
%"struct.ssdm_int<8, false>" = type { i8 }

; Function Attrs: noinline
define void @apatb_sobel_edge_ir(%"struct.ap_uint<8>"* noalias nocapture nonnull readonly %input, %"struct.ap_uint<8>"* noalias nocapture nonnull %output, i32 %rows, i32 %cols) local_unnamed_addr #0 {
entry:
  %malloccall = call i8* @malloc(i64 4096)
  %input_copy = bitcast i8* %malloccall to [4096 x i8]*
  %malloccall1 = call i8* @malloc(i64 4096)
  %output_copy = bitcast i8* %malloccall1 to [4096 x i8]*
  %0 = bitcast %"struct.ap_uint<8>"* %input to [4096 x %"struct.ap_uint<8>"]*
  %1 = bitcast %"struct.ap_uint<8>"* %output to [4096 x %"struct.ap_uint<8>"]*
  call fastcc void @copy_in([4096 x %"struct.ap_uint<8>"]* nonnull %0, [4096 x i8]* %input_copy, [4096 x %"struct.ap_uint<8>"]* nonnull %1, [4096 x i8]* %output_copy)
  call void @apatb_sobel_edge_hw(i8* %malloccall, i8* %malloccall1, i32 %rows, i32 %cols)
  call void @copy_back([4096 x %"struct.ap_uint<8>"]* %0, [4096 x i8]* %input_copy, [4096 x %"struct.ap_uint<8>"]* %1, [4096 x i8]* %output_copy)
  call void @free(i8* %malloccall)
  call void @free(i8* %malloccall1)
  ret void
}

declare noalias i8* @malloc(i64) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([4096 x %"struct.ap_uint<8>"]* noalias readonly "unpacked"="0", [4096 x i8]* noalias nocapture "unpacked"="1.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias readonly "unpacked"="2", [4096 x i8]* noalias nocapture "unpacked"="3.0.0.0") unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>.9.13"([4096 x i8]* %1, [4096 x %"struct.ap_uint<8>"]* %0)
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>.9.13"([4096 x i8]* %3, [4096 x %"struct.ap_uint<8>"]* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="0", [4096 x i8]* noalias nocapture readonly "unpacked"="1.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="2", [4096 x i8]* noalias nocapture readonly "unpacked"="3.0.0.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>"([4096 x %"struct.ap_uint<8>"]* %0, [4096 x i8]* %1)
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>"([4096 x %"struct.ap_uint<8>"]* %2, [4096 x i8]* %3)
  ret void
}

declare void @free(i8*) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>"([4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="0", [4096 x i8]* noalias nocapture readonly "unpacked"="1.0.0.0") unnamed_addr #3 {
entry:
  %2 = icmp eq [4096 x %"struct.ap_uint<8>"]* %0, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [4096 x i8], [4096 x i8]* %1, i64 0, i64 %for.loop.idx1
  %dst.addr.0.0.06 = getelementptr [4096 x %"struct.ap_uint<8>"], [4096 x %"struct.ap_uint<8>"]* %0, i64 0, i64 %for.loop.idx1, i32 0, i32 0, i32 0
  %3 = load i8, i8* %src.addr.0.0.05, align 1
  store i8 %3, i8* %dst.addr.0.0.06, align 1
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4096
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>.9.13"([4096 x i8]* noalias nocapture "unpacked"="0.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias readonly "unpacked"="1") unnamed_addr #3 {
entry:
  %2 = icmp eq [4096 x %"struct.ap_uint<8>"]* %1, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [4096 x %"struct.ap_uint<8>"], [4096 x %"struct.ap_uint<8>"]* %1, i64 0, i64 %for.loop.idx1, i32 0, i32 0, i32 0
  %dst.addr.0.0.06 = getelementptr [4096 x i8], [4096 x i8]* %0, i64 0, i64 %for.loop.idx1
  %3 = load i8, i8* %src.addr.0.0.05, align 1
  store i8 %3, i8* %dst.addr.0.0.06, align 1
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4096
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

declare void @apatb_sobel_edge_hw(i8*, i8*, i32, i32)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="0", [4096 x i8]* noalias nocapture readonly "unpacked"="1.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="2", [4096 x i8]* noalias nocapture readonly "unpacked"="3.0.0.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>"([4096 x %"struct.ap_uint<8>"]* %2, [4096 x i8]* %3)
  ret void
}

define void @sobel_edge_hw_stub_wrapper(i8*, i8*, i32, i32) #4 {
entry:
  %malloccall = tail call i8* @malloc(i64 4096)
  %4 = bitcast i8* %malloccall to [4096 x %"struct.ap_uint<8>"]*
  %malloccall1 = tail call i8* @malloc(i64 4096)
  %5 = bitcast i8* %malloccall1 to [4096 x %"struct.ap_uint<8>"]*
  %6 = bitcast i8* %0 to [4096 x i8]*
  %7 = bitcast i8* %1 to [4096 x i8]*
  call void @copy_out([4096 x %"struct.ap_uint<8>"]* %4, [4096 x i8]* %6, [4096 x %"struct.ap_uint<8>"]* %5, [4096 x i8]* %7)
  %8 = bitcast [4096 x %"struct.ap_uint<8>"]* %4 to %"struct.ap_uint<8>"*
  %9 = bitcast [4096 x %"struct.ap_uint<8>"]* %5 to %"struct.ap_uint<8>"*
  call void @sobel_edge_hw_stub(%"struct.ap_uint<8>"* %8, %"struct.ap_uint<8>"* %9, i32 %2, i32 %3)
  call void @copy_in([4096 x %"struct.ap_uint<8>"]* %4, [4096 x i8]* %6, [4096 x %"struct.ap_uint<8>"]* %5, [4096 x i8]* %7)
  ret void
}

declare void @sobel_edge_hw_stub(%"struct.ap_uint<8>"*, %"struct.ap_uint<8>"*, i32, i32)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
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
