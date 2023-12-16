declare i32 @getchar()
declare i32 @putchar(i32)
define i32 @_main() {
  %i = alloca i32
  store i32 0, i32* %i
  %j = alloca i32
  br label %L1
L1:
  %1 = load i32, i32* %i
  %2 = add i32 32, 0
  %3 = icmp slt i32 %1, %2
  br i1 %3, label %L1Body, label %L1End
L1Body:
  %4 = add i32 0, 0
  store i32 %4, i32* %j
  br label %L5
L5:
  %5 = load i32, i32* %j
  %6 = add i32 32, 0
  %7 = icmp slt i32 %5, %6
  br i1 %7, label %L5Body, label %L5End
L5Body:
  %8 = alloca i32
  %9 = load i32, i32* %i
  %10 = load i32, i32* %j
  %11 = and i32 %9, %10
  %12 = icmp ne i32 %11, 0
  br i1 %12, label %L8then, label %L8else
L8then:
  %13 = alloca i32
  store i32 32, i32* %13
  %14 = load i32, i32* %13
  %15 = tail call i32 @putchar(i32 %14)
  store i32 %15, i32* %8
  br label %L8end
L8else:
  %16 = alloca i32
  store i32 43, i32* %16
  %17 = load i32, i32* %16
  %18 = tail call i32 @putchar(i32 %17)
  store i32 %18, i32* %8
  br label %L8end
L8end:
  %19 = load i32, i32* %8
  %20 = load i32, i32* %j
  %21 = add i32 1, 0
  %22 = add i32 %20, %21
  store i32 %22, i32* %j
  br label %L5
L5End:
  %23 = load i32, i32* %i
  %24 = add i32 1, 0
  %25 = add i32 %23, %24
  store i32 %25, i32* %i
  %26 = alloca i32
  store i32 10, i32* %26
  %27 = load i32, i32* %26
  %28 = tail call i32 @putchar(i32 %27)
  br label %L1
L1End:
  %29 = add i32 0, 0
  ret i32 %29
}

define i32 @main() {
  %1 = call i32 @_main()
  ret i32 %1
}
