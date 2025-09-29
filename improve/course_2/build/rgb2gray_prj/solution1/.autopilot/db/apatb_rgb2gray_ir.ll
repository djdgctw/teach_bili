; ModuleID = '/home/fyt/A/teach_bili/improve/course_2/build/rgb2gray_prj/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_uint<24>" = type { %"struct.ap_int_base<24, false>" }
%"struct.ap_int_base<24, false>" = type { %"struct.ssdm_int<24, false>" }
%"struct.ssdm_int<24, false>" = type { i24 }
%"struct.ap_uint<8>" = type { %"struct.ap_int_base<8, false>" }
%"struct.ap_int_base<8, false>" = type { %"struct.ssdm_int<8, false>" }
%"struct.ssdm_int<8, false>" = type { i8 }

; Function Attrs: noinline
define void @apatb_rgb2gray_ir(%"struct.ap_uint<24>"* noalias nonnull %rgb, %"struct.ap_uint<8>"* noalias nocapture nonnull %gray, i32 %size) local_unnamed_addr #0 {
entry:
  %malloccall = call i8* @malloc(i64 16384)
  %rgb_copy = bitcast i8* %malloccall to [4096 x i24]*
  %malloccall1 = call i8* @malloc(i64 4096)
  %gray_copy = bitcast i8* %malloccall1 to [4096 x i8]*
  %0 = bitcast %"struct.ap_uint<24>"* %rgb to [4096 x %"struct.ap_uint<24>"]*
  %1 = bitcast %"struct.ap_uint<8>"* %gray to [4096 x %"struct.ap_uint<8>"]*
  call fastcc void @copy_in([4096 x %"struct.ap_uint<24>"]* nonnull %0, [4096 x i24]* %rgb_copy, [4096 x %"struct.ap_uint<8>"]* nonnull %1, [4096 x i8]* %gray_copy)
  %2 = getelementptr [4096 x i24], [4096 x i24]* %rgb_copy, i32 0, i32 0
  call void @apatb_rgb2gray_hw(i24* %2, i8* %malloccall1, i32 %size)
  call void @copy_back([4096 x %"struct.ap_uint<24>"]* %0, [4096 x i24]* %rgb_copy, [4096 x %"struct.ap_uint<8>"]* %1, [4096 x i8]* %gray_copy)
  call void @free(i8* %malloccall)
  call void @free(i8* %malloccall1)
  ret void
}

declare noalias i8* @malloc(i64) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([4096 x %"struct.ap_uint<24>"]* noalias readonly "unpacked"="0", [4096 x i24]* noalias nocapture "unpacked"="1.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias readonly "unpacked"="2", [4096 x i8]* noalias nocapture "unpacked"="3.0.0.0") unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<24>.29"([4096 x i24]* %1, [4096 x %"struct.ap_uint<24>"]* %0)
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>"([4096 x i8]* %3, [4096 x %"struct.ap_uint<8>"]* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([4096 x %"struct.ap_uint<24>"]* noalias "unpacked"="0", [4096 x i24]* noalias nocapture readonly "unpacked"="1.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="2", [4096 x i8]* noalias nocapture readonly "unpacked"="3.0.0.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<24>"([4096 x %"struct.ap_uint<24>"]* %0, [4096 x i24]* %1)
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>.5"([4096 x %"struct.ap_uint<8>"]* %2, [4096 x i8]* %3)
  ret void
}

declare void @free(i8*) local_unnamed_addr

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>.5"([4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="0", [4096 x i8]* noalias nocapture readonly "unpacked"="1.0.0.0") unnamed_addr #3 {
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
define internal fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>"([4096 x i8]* noalias nocapture "unpacked"="0.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias readonly "unpacked"="1") unnamed_addr #3 {
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

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<24>.29"([4096 x i24]* noalias nocapture "unpacked"="0.0.0.0", [4096 x %"struct.ap_uint<24>"]* noalias readonly "unpacked"="1") unnamed_addr #3 {
entry:
  %2 = icmp eq [4096 x %"struct.ap_uint<24>"]* %1, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [4096 x %"struct.ap_uint<24>"], [4096 x %"struct.ap_uint<24>"]* %1, i64 0, i64 %for.loop.idx1, i32 0, i32 0, i32 0
  %dst.addr.0.0.06 = getelementptr [4096 x i24], [4096 x i24]* %0, i64 0, i64 %for.loop.idx1
  %3 = load i24, i24* %src.addr.0.0.05, align 4
  store i24 %3, i24* %dst.addr.0.0.06, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4096
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<24>"([4096 x %"struct.ap_uint<24>"]* noalias "unpacked"="0", [4096 x i24]* noalias nocapture readonly "unpacked"="1.0.0.0") unnamed_addr #3 {
entry:
  %2 = icmp eq [4096 x %"struct.ap_uint<24>"]* %0, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %src.addr.0.0.05 = getelementptr [4096 x i24], [4096 x i24]* %1, i64 0, i64 %for.loop.idx1
  %dst.addr.0.0.06 = getelementptr [4096 x %"struct.ap_uint<24>"], [4096 x %"struct.ap_uint<24>"]* %0, i64 0, i64 %for.loop.idx1, i32 0, i32 0, i32 0
  %3 = load i24, i24* %src.addr.0.0.05, align 4
  store i24 %3, i24* %dst.addr.0.0.06, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4096
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

declare void @apatb_rgb2gray_hw(i24*, i8*, i32)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([4096 x %"struct.ap_uint<24>"]* noalias "unpacked"="0", [4096 x i24]* noalias nocapture readonly "unpacked"="1.0.0.0", [4096 x %"struct.ap_uint<8>"]* noalias "unpacked"="2", [4096 x i8]* noalias nocapture readonly "unpacked"="3.0.0.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<24>"([4096 x %"struct.ap_uint<24>"]* %0, [4096 x i24]* %1)
  call fastcc void @"onebyonecpy_hls.p0a4096struct.ap_uint<8>.5"([4096 x %"struct.ap_uint<8>"]* %2, [4096 x i8]* %3)
  ret void
}

define void @rgb2gray_hw_stub_wrapper(i24*, i8*, i32) #4 {
entry:
  %malloccall = tail call i8* @malloc(i64 16384)
  %3 = bitcast i8* %malloccall to [4096 x %"struct.ap_uint<24>"]*
  %malloccall1 = tail call i8* @malloc(i64 4096)
  %4 = bitcast i8* %malloccall1 to [4096 x %"struct.ap_uint<8>"]*
  %5 = bitcast i24* %0 to [4096 x i24]*
  %6 = bitcast i8* %1 to [4096 x i8]*
  call void @copy_out([4096 x %"struct.ap_uint<24>"]* %3, [4096 x i24]* %5, [4096 x %"struct.ap_uint<8>"]* %4, [4096 x i8]* %6)
  %7 = bitcast [4096 x %"struct.ap_uint<24>"]* %3 to %"struct.ap_uint<24>"*
  %8 = bitcast [4096 x %"struct.ap_uint<8>"]* %4 to %"struct.ap_uint<8>"*
  call void @rgb2gray_hw_stub(%"struct.ap_uint<24>"* %7, %"struct.ap_uint<8>"* %8, i32 %2)
  call void @copy_in([4096 x %"struct.ap_uint<24>"]* %3, [4096 x i24]* %5, [4096 x %"struct.ap_uint<8>"]* %4, [4096 x i8]* %6)
  ret void
}

declare void @rgb2gray_hw_stub(%"struct.ap_uint<24>"*, %"struct.ap_uint<8>"*, i32)

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
