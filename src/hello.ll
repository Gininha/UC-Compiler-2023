declare i32 @getchar()
declare i32 @putchar(i32)
define double @_main() {
  %_a = alloca double
  %1 = add i32 0, 0
  %2 = sitofp i32 %1 to double
  store double %2, double* %_a
  %_b = alloca double
  %3 = fadd double 0.2, 0.0
  store double %3, double* %_b
  %_c = alloca double
  %_d = alloca i32
  %_e = alloca i32
  %4 = add i32 0, 0
  store i32 %4, i32* %_e
  %5 = load i32, i32* %_e
  %6 = add i32 10, 0
  %7 = add i32 %5, %6
  store i32 %7, i32* %_d
  %8 = alloca i32
  %9 = load i32, i32* %_d
  %10 = load i32, i32* %_e
  %11 = icmp slt i32 %9, %10
  %12 = zext i1 %11 to i32
  %13 = icmp ne i32 %12, 0
  br i1 %13, label %L8then, label %L8else
L8then:
  %14 = add i32 99, 0
  %15 = tail call i32 @putchar(i32 %14)
  store i32 %15, i32* %8
  br label %L8end
L8else:
  %16 = load i32, i32* %_a
  %17 = load i32, i32* %_b
  %18 = add i32 %16, %17
  store i32 %18, i32* %_c
  br label %L19
L19:
  %19 = load i32, i32* %_d
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %L19Body, label %L19End
L19Body:
  %21 = load i32, i32* %_d
  %22 = add i32 50, 0
  %23 = add i32 %21, %22
  store i32 %23, i32* %_e
  %24 = load i32, i32* %_e
  %25 = tail call i32 @putchar(i32 %24)
  %26 = load i32, i32* %_d
  %27 = add i32 1, 0
  %28 = sub i32 %26, %27
  store i32 %28, i32* %_d
  br label %L19
L19End:
  br label %L8end
L8end:
  %29 = load i32, i32* %8
  ret double 1
}

define i32 @main() {
  %1 = call i32 @_main()
  ret i32 %1
}
