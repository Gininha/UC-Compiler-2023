declare i32 @getchar()
declare i32 @putchar(i32)
@global_char = global i32 0
@global_char1 = global i32 255
@global_char2 = global i32 4
@global_char3 = global i32 36
@global_char4 = global i32 228
@global_a = global i32 65
@global_b = global i32 66
@global_c = global i32 67
@global_d = global double 4.0
define i32 @_main() {
  %a = alloca i32
  store i32 68, i32* %a
  %b = alloca i32
  store i32 69, i32* %b
  %c = alloca i32
  store i32 70, i32* %c
  %d = alloca double
  store double 4.0, double* %d
  %temp = alloca i32

-->Minus
  store i32 %-1, i32* %temp

-->Minus
  store i32 %-1, i32* %temp
  %1 = load i32, i32* %a
  store i32 %1, i32* %temp
  %2 = load i32, i32* %global_a
  store i32 %2, i32* %a

-->Minus
  %3 = tail call i32 @putchar(i32 %-1)
  %4 = load i32, i32* %temp
  store i32 %4, i32* %a
  %5 = load i32, i32* %b
  store i32 %5, i32* %temp
  %6 = load i32, i32* %global_b
  store i32 %6, i32* %b
  %7 = load i32, i32* %b
  %8 = tail call i32 @putchar(i32 %7)
  %9 = load i32, i32* %temp
  store i32 %9, i32* %b
  %10 = load i32, i32* %c
  store i32 %10, i32* %temp
  %11 = load i32, i32* %global_c
  store i32 %11, i32* %c

-->Minus
  %12 = tail call i32 @putchar(i32 %-1)
  %13 = load i32, i32* %temp
  store i32 %13, i32* %c
  %14 = load i32, i32* %a
  %15 = tail call i32 @putchar(i32 %14)
  %16 = load i32, i32* %b
  %17 = tail call i32 @putchar(i32 %16)
  %18 = load i32, i32* %c
  %19 = tail call i32 @putchar(i32 %18)
  %20 = load i32, i32* %a
  store i32 %20, i32* %a

-->Minus
  store i32 %-1, i32* %b

-->Minus
  store i32 %-1, i32* %c
  %21 = load i32, i32* %a
  %22 = tail call i32 @putchar(i32 %21)

-->Minus
  %23 = tail call i32 @putchar(i32 %-1)

-->Minus
  %24 = tail call i32 @putchar(i32 %-1)

-->Minus
  %25 = tail call i32 @putchar(i32 %-1)

-->Minus
  %26 = tail call i32 @putchar(i32 %-1)
  %27 = alloca i32
  store i32 10, i32* %27
  %28 = load i32, i32* %27
  %29 = tail call i32 @putchar(i32 %28)

-->Minus
  ret i32 %-1
}

define i32 @main() {
  %1 = call i32 @_main()
  ret i32 %1
}
