declare i32 @getchar()
declare i32 @putchar(i32)
@a = global double 12.456
@b = global i32 52
@z = global i32 110
define i32 @_par(i32 %x) {
  %_x = alloca i32
  store i32 %x, i32* %_x
  %1 = alloca i32
  %2 = load i32, i32* %_x
  %3 = add i32 2, 0
  %4 = srem i32 %2, %3
  %5 = add i32 0, 0
  %6 = icmp eq i32 %4, %5
  %7 = zext i1 %6 to i32
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %L1then, label %L1else
L1then:
  %9 = add i32 1, 0
  store i32 %9, i32* %1
  br label %L1end
L1else:
  %10 = add i32 0, 0
  store i32 %10, i32* %1
  br label %L1end
L1end:
  %11 = load i32, i32* %1
  ret i32 %11
}

define i32 @_main() {
  %_d = alloca i32
  %1 = load i32, i32* @b
  %2 = add i32 51, 0
  %3 = add i32 %1, %2
  store i32 %3, i32* %_d
  %_e = alloca i32
  %4 = load i32, i32* %_d
  %5 = tail call i32 @_par(i32 %4)
  store i32 %5, i32* %_e
  %6 = alloca i32
  %7 = load i32, i32* %_e
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %L6then, label %L6else
L6then:
  %9 = add i32 115, 0
  %10 = tail call i32 @putchar(i32 %9)
  store i32 %10, i32* %6
  br label %L6end
L6else:
  %11 = load i32, i32* @z
  %12 = tail call i32 @putchar(i32 %11)
  store i32 %12, i32* %6
  br label %L6end
L6end:
  %13 = load i32, i32* %6
  %14 = add i32 10, 0
  %15 = tail call i32 @putchar(i32 %14)
  %16 = load i32, i32* %_e
  ret i32 %16
}

define i32 @main() {
  %1 = fadd double 12.456, 0.0
  store double %1, double* @a
  %2 = add i32 14, 0
  store i32 %2, i32* @b
  %3 = add i32 110, 0
  store i32 %3, i32* @z
  %4 = call i32 @_main()
  ret i32 %4
}
