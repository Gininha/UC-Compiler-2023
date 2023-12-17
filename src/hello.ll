declare i32 @getchar()
declare i32 @putchar(i32)
@global_char = global i32 0
@global_char1 = global i32 0
@global_char2 = global i32 0
@global_char3 = global i32 0
@global_char4 = global i32 0
@global_a = global i32 0
@global_b = global i32 0
@global_c = global i32 0
@global_d = global double 0
define i32 @_main() {
  %_a = alloca i32
  %1 = add i32 68, 0
  store i32 %1, i32* %_a
  %_b = alloca i32
  %2 = add i32 69, 0
  store i32 %2, i32* %_b
  %_c = alloca i32
  %3 = add i32 70, 0
  store i32 %3, i32* %_c
  %_d = alloca double
  %4 = fadd double 4.0, 0.0
  store double %4, double* %_d
  %_temp = alloca i32
  %5 = add i32 2147483648, 0
  %6 = sub i32 0, %5
  %7 = sub i32 0, %6
  store i32 %7, i32* %_temp
  %8 = add i32 2147483648, 0
  %9 = sub i32 0, %8
  store i32 %9, i32* %_temp
  %10 = load i32, i32* %_a
  store i32 %10, i32* %_temp
  %11 = load i32, i32* @global_a
  store i32 %11, i32* %_a
  %12 = load i32, i32* %_a
  %13 = sub i32 0, %12
  %14 = sub i32 0, %13
  %15 = sub i32 0, %14
  %16 = sub i32 0, %15
  %17 = tail call i32 @putchar(i32 %16)
  %18 = load i32, i32* %_temp
  store i32 %18, i32* %_a
  %19 = load i32, i32* %_b
  store i32 %19, i32* %_temp
  %20 = load i32, i32* @global_b
  store i32 %20, i32* %_b
  %21 = load i32, i32* %_b
  %22 = tail call i32 @putchar(i32 %21)
  %23 = load i32, i32* %_temp
  store i32 %23, i32* %_b
  %24 = load i32, i32* %_c
  store i32 %24, i32* %_temp
  %25 = load i32, i32* @global_c
  store i32 %25, i32* %_c
  %26 = load i32, i32* %_c
  %27 = sub i32 0, %26
  %28 = sub i32 0, %27
  %29 = tail call i32 @putchar(i32 %28)
  %30 = load i32, i32* %_temp
  store i32 %30, i32* %_c
  %31 = load i32, i32* %_a
  %32 = tail call i32 @putchar(i32 %31)
  %33 = load i32, i32* %_b
  %34 = tail call i32 @putchar(i32 %33)
  %35 = load i32, i32* %_c
  %36 = tail call i32 @putchar(i32 %35)
  %37 = load i32, i32* %_a
  store i32 %37, i32* %_a
  %38 = add i32 66, 0
  %39 = sub i32 0, %38
  store i32 %39, i32* %_b
  %40 = load i32, i32* %_a
  %41 = sub i32 0, %40
  store i32 %41, i32* %_c
  %42 = load i32, i32* %_a
  %43 = tail call i32 @putchar(i32 %42)
  %44 = load i32, i32* %_b
  %45 = sub i32 0, %44
  %46 = tail call i32 @putchar(i32 %45)
  %47 = add i32 66, 0
  %48 = sub i32 0, %47
  %49 = sub i32 0, %48
  %50 = sub i32 0, %49
  %51 = sub i32 0, %50
  %52 = sub i32 0, %51
  %53 = sub i32 0, %52
  %54 = tail call i32 @putchar(i32 %53)
  %55 = add i32 66, 0
  %56 = sub i32 0, %55
  %57 = sub i32 0, %56
  %58 = sub i32 0, %57
  %59 = sub i32 0, %58
  %60 = tail call i32 @putchar(i32 %59)
  %61 = load i32, i32* %_c
  %62 = sub i32 0, %61
  %63 = sub i32 0, %62
  %64 = sub i32 0, %63
  %65 = sub i32 0, %64
  %66 = sub i32 0, %65
  %67 = sub i32 0, %66
  %68 = sub i32 0, %67
  %69 = tail call i32 @putchar(i32 %68)
  %70 = add i32 10, 0
  %71 = tail call i32 @putchar(i32 %70)
  %72 = load i32, i32* %_c
  %73 = sub i32 0, %72
  %74 = sub i32 0, %73
  %75 = sub i32 0, %74
  ret i32 %75
}

define i32 @main() {
  %1 = add i32 0, 0
  store i32 %1, i32* @global_char
  %2 = add i32 -1, 0
  store i32 %2, i32* @global_char1
  %3 = add i32 4, 0
  store i32 %3, i32* @global_char2
  %4 = add i32 36, 0
  store i32 %4, i32* @global_char3
  %5 = add i32 -28, 0
  store i32 %5, i32* @global_char4
  %6 = add i32 65, 0
  store i32 %6, i32* @global_a
  %7 = add i32 66, 0
  store i32 %7, i32* @global_b
  %8 = add i32 67, 0
  store i32 %8, i32* @global_c
  %9 = fadd double 4.0, 0.0
  store double %9, double* @global_d
  %10 = call i32 @_main()
  ret i32 %1
}
