declare i32 @getchar()
declare i32 @putchar(i32)
define i32 @_main() {
  %_i = alloca i32
  %1 = add i32 65, 0
  store i32 %1, i32* %_i
  br label %L2
L2:
  %2 = load i32, i32* %_i
  %3 = add i32 90, 0
  %4 = icmp sle i32 %2, %3
  %5 = zext i1 %4 to i32
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %L2Body, label %L2End
L2Body:
  %7 = load i32, i32* %_i
  %8 = tail call i32 @putchar(i32 %7)
  %9 = load i32, i32* %_i
  %10 = add i32 1, 0
  %11 = add i32 %9, %10
  store i32 %11, i32* %_i
  br label %L2
L2End:
  %12 = add i32 0, 0
  ret i32 %12
}

define i32 @main() {
  %1 = call i32 @_main()
  ret i32 %1
}
