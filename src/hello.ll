declare i32 @getchar()
declare i32 @putchar(i32)
@kek = global double 0.0
@kek_1 = global double 1.2
@kappa = global i32 53
@u_know = global i32 112
@w = global i32 48
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
  store i32 %12, i32* %_res_2
  %_res_3 = alloca i32
  %13 = load i32, i32* @kappa
  %14 = load i32, i32* @u_know
  %15 = add i32 %13, %14
  store i32 %15, i32* %_res_3
  %16 = load i32, i32* %_res_1
  %17 = tail call i32 @putchar(i32 %16)
  %18 = load i32, i32* %_res_2
  %19 = tail call i32 @putchar(i32 %18)
  %20 = load i32, i32* %_res_3
  %21 = tail call i32 @putchar(i32 %20)
  %_ala_u_akbar = alloca double
  %22 = load i32, i32* @kek
  %23 = load i32, i32* @kek_1
  %24 = fadd double %22, %23
  store double %24, double* %_ala_u_akbar
  ret void
}

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
  ret double 1.0
}

define double @main() {
  %1 = add i32 0, 0
  store double %1, double* @kek
  %2 = fadd double 1.2, 0.0
  store double %2, double* @kek_1
  %3 = add i32 75, 0
  store i32 %3, i32* @kappa
  %4 = add i32 112, 0
  store i32 %4, i32* @u_know
  %5 = add i32 40, 0
  store i32 %5, i32* @w
  %6 = call double @_main()
  ret double %1
}
