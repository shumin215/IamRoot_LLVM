; ModuleID = 'ch12_eh.bc'
target datalayout = "E-m:m-p:32:32-i8:8:32-i16:16:32-i64:64-n32-S64"
target triple = "mips-unknown-linux-gnu"

%class.Ex1 = type { i8 }

$_ZTS3Ex1 = comdat any

$_ZTI3Ex1 = comdat any

@_ZTVN10__cxxabiv117__class_type_infoE = external global i8*
@_ZTS3Ex1 = linkonce_odr constant [5 x i8] c"3Ex1\00", comdat
@_ZTI3Ex1 = linkonce_odr constant { i8*, i8* } { i8* bitcast (i8** getelementptr
 inbounds (i8*, i8** @_ZTVN10__cxxabiv117__class_type_infoE, i32 2) to i8*), i8*
 getelementptr inbounds ([5 x i8], [5 x i8]* @_ZTS3Ex1, i32 0, i32 0) }, comdat

define void @_Z15throw_exceptionii(i32 signext %a, i32 signext %b) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %ex1 = alloca %class.Ex1, align 1
  store i32 %a, i32* %1, align 4
  store i32 %b, i32* %2, align 4
  %3 = load i32, i32* %1, align 4
  %4 = load i32, i32* %2, align 4
  %5 = icmp sgt i32 %3, %4
  br i1 %5, label %6, label %9

; <label>:6                                       ; preds = %0
  %7 = call i8* @__cxa_allocate_exception(i32 1) #1
  %8 = bitcast i8* %7 to %class.Ex1*
  call void @__cxa_throw(i8* %7, i8* bitcast ({ i8*, i8* }* @_ZTI3Ex1 to i8*), i
8* null) #2
  unreachable

; <label>:9                                       ; preds = %0
  ret void
}

declare i8* @__cxa_allocate_exception(i32)

declare void @__cxa_throw(i8*, i8*, i8*)

define i32 @_Z14test_try_catchv() #0 personality i8* bitcast (i32 (...)* @__gxx_
personality_v0 to i8*) {
  %1 = alloca i32, align 4
  %2 = alloca i8*
  %3 = alloca i32
  %4 = alloca i32
  invoke void @_Z15throw_exceptionii(i32 signext 2, i32 signext 1)
          to label %5 unwind label %6

; <label>:5                                       ; preds = %0
  br label %13

; <label>:6                                       ; preds = %0
  %7 = landingpad { i8*, i32 }
          catch i8* null
  %8 = extractvalue { i8*, i32 } %7, 0
  store i8* %8, i8** %2
  %9 = extractvalue { i8*, i32 } %7, 1
  store i32 %9, i32* %3
  br label %10

; <label>:10                                      ; preds = %6
  %11 = load i8*, i8** %2
  %12 = call i8* @__cxa_begin_catch(i8* %11) #1
  store i32 1, i32* %1
  store i32 1, i32* %4
  call void @__cxa_end_catch()
  br label %14

; <label>:13                                      ; preds = %5
  store i32 0, i32* %1
  br label %14

; <label>:14                                      ; preds = %13, %10
  %15 = load i32, i32* %1
  ret i32 %15
}

declare i32 @__gxx_personality_v0(...)

declare i8* @__cxa_begin_catch(i8*)

declare void @__cxa_end_catch()

attributes #0 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "n
o-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="fals
e" "stack-protector-buffer-size"="8" "target-cpu"="mips32r2" "target-features"="
+mips32r2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { noreturn }

!llvm.ident = !{!0}

!0 = !{!"Apple LLVM version 7.0.0 (clang-700.1.76)"}
