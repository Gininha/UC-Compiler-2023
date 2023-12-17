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
  %_x = alloca i32
  %16 = add i32 1, 0
  store i32 %16, i32* %_x
  %_y = alloca i32
  %17 = add i32 0, 0
  store i32 %17, i32* %_y
  %_z = alloca i32
  %18 = add i32 2, 0
  store i32 %18, i32* %_z
  %19 = load i32, i32* %_y
  %20 = load i32, i32* @z
  %21 = sub i32 %19, %20
  store i32 %21, i32* %_x
  %22 = load i32, i32* %_y
  %23 = load i32, i32* @z
  %24 = sdiv i32 %22, %23
  store i32 %24, i32* %_x
  %25 = load i32, i32* %_y
  %26 = load i32, i32* @z
  %27 = mul i32 %25, %26
  store i32 %27, i32* %_x
  %28 = load i32, i32* %_y
  %29 = load i32, i32* @z
  %30 = add i32 %28, %29
  store i32 %30, i32* %_x
  %31 = alloca i32
  %32 = load i32, i32* %_x
  %33 = load i32, i32* %_y
  %34 = icmp ne i32 %32, 0
  %35 = icmp ne i32 %33, 0
  %36 = or i1 %34, %35
  %37 = zext i1 %36 to i32
  %38 = icmp ne i32 %37, 0
  br i1 %38, label %L31then, label %L31else
L31then:
  %39 = alloca i32
  %40 = load i32, i32* %_x
  %41 = load i32, i32* @z
  %42 = icmp ne i32 %40, 0
  %43 = icmp ne i32 %41, 0
  %44 = and i1 %42, %43
  %45 = zext i1 %44 to i32
  %46 = icmp ne i32 %45, 0
  br i1 %46, label %L39then, label %L39else
L39then:
  %47 = alloca i32
  %48 = load i32, i32* %_y
  %49 = icmp eq i32 %48, 0
  %50 = zext i1 %49 to i32
  %51 = icmp ne i32 %50, 0
  br i1 %51, label %L47then, label %L47else
L47then:
  %52 = add i32 121, 0
  %53 = tail call i32 @putchar(i32 %52)
  store i32 %53, i32* %47
  br label %L47end
L47else:
  br label %L47end
L47end:
  %54 = load i32, i32* %47
  store i32 %54, i32* %39
  br label %L39end
L39else:
  br label %L39end
L39end:
  %55 = load i32, i32* %39
  store i32 %55, i32* %31
  br label %L31end
L31else:
  br label %L31end
L31end:
  %56 = load i32, i32* %31
  %57 = load i32, i32* %_d
  %58 = load i32, i32* @b
  %59 = load i32, i32* %_x
  %60 = add i32 122, 0
  %61 = tail call i32 @putchar(i32 %60)
  %62 = add i32 10, 0
  %63 = tail call i32 @putchar(i32 %62)
  %64 = load i32, i32* %_e
  ret i32 %64
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

define i32 @_recursion(i32 %n) {
  %_n = alloca i32
  store i32 %n, i32* %_n
  %1 = alloca i32
  %2 = load i32, i32* %_n
  %3 = add i32 1, 0
  %4 = icmp sle i32 %2, %3
  %5 = zext i1 %4 to i32
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %L1then, label %L1else
L1then:
  %7 = add i32 1, 0
  store i32 %7, i32* %1
  br label %L1end
L1else:
  br label %L1end
L1end:
  %8 = load i32, i32* %1
  %9 = load i32, i32* %_n
  %10 = load i32, i32* %_n
  %11 = add i32 1, 0
  %12 = sub i32 %10, %11
  %13 = tail call i32 @_recursion(i32 %12)
  %14 = mul i32 %9, %13
  ret i32 %14
}

define i32 @_main() {
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
  %16 = load double, double* %_a
  %17 = load double, double* %_b
  %18 = fadd double %16, %17
  store double %18, double* %_c
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
  %30 = add i32 10, 0
  %31 = tail call i32 @putchar(i32 %30)
  tail call void @_funcao_com_globais()
  tail call void @_funcao_vazia()
  %32 = tail call double @_funcao_double()
  %33 = tail call i32 @_funcao_int()
  %34 = tail call i32 @_funcao_char()
  %35 = tail call i32 @_funcao_short()
  %36 = add i32 5, 0
  %37 = tail call i32 @_recursion(i32 %36)
  ret i32 %37
}

define i32 @main() {
  %1 = add i32 0, 0
  %2 = sitofp i32 %1 to double
  store double %2, double* @kek
  %3 = fadd double 1.2, 0.0
  store double %3, double* @kek_1
  %4 = add i32 75, 0
  store i32 %4, i32* @kappa
  %5 = add i32 112, 0
  store i32 %5, i32* @u_know
  %6 = add i32 40, 0
  store i32 %6, i32* @w
  %7 = call i32 @_main()
  ret i32 %7
}
