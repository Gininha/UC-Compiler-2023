declare i32 @getchar()
declare i32 @putchar(i32)
@kek = global double 0.0
@kek_1 = global double 1.2
@kappa = global i32 53
@u_know = global i32 112
@w = global i32 48
define void @_funcao_vazia() {
  ret void
}

define double @_funcao_double() {
  %1 = fadd double 64.5, 0.0
  ret double %1
}

define i32 @_funcao_int() {
  %1 = add i32 0, 0
  ret i32 %1
}

define i32 @_funcao_char() {
  %1 = add i32 1, 0
  ret i32 %1
}

define i32 @_funcao_short() {
  %1 = add i32 2, 0
  ret i32 %1
}

define void @_funcao_com_globais() {
  %1 = load i32, i32* @w
  %2 = tail call i32 @putchar(i32 %1)
  %3 = load i32, i32* @u_know
  %4 = tail call i32 @putchar(i32 %3)
  %5 = load i32, i32* @kappa
  %6 = tail call i32 @putchar(i32 %5)
  %_res_1 = alloca i32
  %7 = load i32, i32* @kappa
  %8 = load i32, i32* @w
  %9 = add i32 %7, %8
  store i32 %9, i32* %_res_1
  %_res_2 = alloca i32
  %10 = load i32, i32* @u_know
  %11 = load i32, i32* @w
  %12 = add i32 %10, %11
  %13 = add i32 100, 0
  %14 = sub i32 %12, %13
  store i32 %14, i32* %_res_2
  %_res_3 = alloca i32
  %15 = load i32, i32* @kappa
  %16 = load i32, i32* @u_know
  %17 = add i32 %15, %16
  %18 = add i32 100, 0
  %19 = sub i32 %17, %18
  store i32 %19, i32* %_res_3
  %20 = load i32, i32* %_res_1
  %21 = tail call i32 @putchar(i32 %20)
  %22 = load i32, i32* %_res_2
  %23 = tail call i32 @putchar(i32 %22)
  %24 = load i32, i32* %_res_3
  %25 = tail call i32 @putchar(i32 %24)
  %_ala_u_akbar = alloca double
  %26 = load double, double* @kek
  %27 = load double, double* @kek_1
  %28 = fadd double %26, %27
  store double %28, double* %_ala_u_akbar
  %29 = add i32 10, 0
  %30 = tail call i32 @putchar(i32 %29)
  ret void
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
