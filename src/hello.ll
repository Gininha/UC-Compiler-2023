declare i32 @getchar()
declare i32 @putchar(i32)
@variavel_global_memo_a_bacans = global i32 0
define void @_funcao_bueda_fixe() {
  %_i = alloca i32
  %1 = add i32 0, 0
  store i32 %1, i32* %_i
  br label %L2
L2:
  %2 = load i32, i32* %_i
  %3 = add i32 10, 0
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %L2Body, label %L2End
L2Body:
  %5 = alloca i32
  %6 = load i32, i32* %_i
  %7 = add i32 10, 0
  %8 = icmp eq i32 %6, %7
  %9 = zext i1 %8 to i32
  %10 = icmp ne i32 %9, 0
  br i1 %10, label %L5then, label %L5else
L5then:
  %11 = add i32 115, 0
  %12 = tail call i32 @putchar(i32 %11)
  store i32 %12, i32* %5
  br label %L5end
L5else:
  br label %L5end
L5end:
  %13 = load i32, i32* %5
  %14 = alloca i32
  %15 = load i32, i32* %_i
  %16 = add i32 9, 0
  %17 = icmp sge i32 %15, %16
  %18 = zext i1 %17 to i32
  %19 = icmp ne i32 %18, 0
  br i1 %19, label %L14then, label %L14else
L14then:
  %20 = add i32 107, 0
  %21 = tail call i32 @putchar(i32 %20)
  store i32 %21, i32* %14
  br label %L14end
L14else:
  br label %L14end
L14end:
  %22 = load i32, i32* %14
  %23 = alloca i32
  %24 = load i32, i32* %_i
  %25 = add i32 8, 0
  %26 = icmp sgt i32 %24, %25
  %27 = zext i1 %26 to i32
  %28 = icmp ne i32 %27, 0
  br i1 %28, label %L23then, label %L23else
L23then:
  %29 = add i32 108, 0
  %30 = tail call i32 @putchar(i32 %29)
  store i32 %30, i32* %23
  br label %L23end
L23else:
  br label %L23end
L23end:
  %31 = load i32, i32* %23
  %32 = alloca i32
  %33 = load i32, i32* %_i
  %34 = add i32 7, 0
  %35 = icmp ne i32 %33, %34
  %36 = zext i1 %35 to i32
  %37 = icmp ne i32 %36, 0
  br i1 %37, label %L32then, label %L32else
L32then:
  %38 = add i32 112, 0
  %39 = tail call i32 @putchar(i32 %38)
  store i32 %39, i32* %32
  br label %L32end
L32else:
  br label %L32end
L32end:
  %40 = load i32, i32* %32
  %41 = alloca i32
  %42 = load i32, i32* %_i
  %43 = add i32 6, 0
  %44 = icmp slt i32 %42, %43
  %45 = zext i1 %44 to i32
  %46 = icmp ne i32 %45, 0
  br i1 %46, label %L41then, label %L41else
L41then:
  %47 = add i32 117, 0
  %48 = tail call i32 @putchar(i32 %47)
  store i32 %48, i32* %41
  br label %L41end
L41else:
  br label %L41end
L41end:
  %49 = load i32, i32* %41
  %50 = alloca i32
  %51 = load i32, i32* %_i
  %52 = add i32 5, 0
  %53 = icmp sle i32 %51, %52
  %54 = zext i1 %53 to i32
  %55 = icmp ne i32 %54, 0
  br i1 %55, label %L50then, label %L50else
L50then:
  %56 = add i32 108, 0
  %57 = tail call i32 @putchar(i32 %56)
  store i32 %57, i32* %50
  br label %L50end
L50else:
  br label %L50end
L50end:
  %58 = load i32, i32* %50
  %59 = load i32, i32* %_i
  %60 = add i32 1, 0
  %61 = add i32 %59, %60
  store i32 %61, i32* %_i
  br label %L2
L2End:
  %62 = add i32 10, 0
  %63 = tail call i32 @putchar(i32 %62)
  ret void
}

define void @_testezito() {
  %_b = alloca i32
  %1 = add i32 98, 0
  store i32 %1, i32* %_b
  %2 = load i32, i32* %_b
  %3 = tail call i32 @putchar(i32 %2)
  %_d = alloca i32
  %4 = load i32, i32* %_b
  %5 = add i32 10, 0
  %6 = add i32 %4, %5
  store i32 %6, i32* %_d
  %7 = load i32, i32* %_d
  %8 = tail call i32 @putchar(i32 %7)
  %9 = add i32 10, 0
  %10 = tail call i32 @putchar(i32 %9)
  ret void
}

define i32 @_teste_c(i32 %x, i32 %y) {
  %_x = alloca i32
  store i32 %x, i32* %_x
  %_y = alloca i32
  store i32 %y, i32* %_y
  %_res = alloca i32
  %1 = load i32, i32* %_x
  %2 = load i32, i32* %_y
  %3 = add i32 %1, %2
  store i32 %3, i32* %_res
  %4 = load i32, i32* %_res
  ret i32 %4
}

define i32 @_somaarg(i32 %x) {
  %_x = alloca i32
  store i32 %x, i32* %_x
  %1 = load i32, i32* %_x
  %2 = add i32 1, 0
  %3 = add i32 %1, %2
  store i32 %3, i32* %_x
  %4 = load i32, i32* %_x
  ret i32 %4
}

define i32 @_sus(i32 %x) {
  %_x = alloca i32
  store i32 %x, i32* %_x
  %1 = load i32, i32* %_x
  %2 = add i32 1, 0
  %3 = add i32 %1, %2
  ret i32 %3
}

define i32 @_main() {
  %_a = alloca i32
  %1 = add i32 50, 0
  store i32 %1, i32* %_a
  %_b = alloca i32
  %2 = add i32 0, 0
  store i32 %2, i32* %_b
  %_c = alloca i32
  %3 = add i32 0, 0
  store i32 %3, i32* %_c
  tail call void @_funcao_bueda_fixe()
  tail call void @_testezito()
  %4 = load i32, i32* %_a
  %5 = add i32 10, 0
  %6 = tail call i32 @_teste_c(i32 %4, i32 %5)
  store i32 %6, i32* %_b
  %7 = load i32, i32* %_b
  %8 = tail call i32 @putchar(i32 %7)
  %9 = add i32 45, 0
  %10 = tail call i32 @_somaarg(i32 %9)
  store i32 %10, i32* %_c
  %11 = load i32, i32* %_c
  %12 = tail call i32 @putchar(i32 %11)
  %13 = add i32 10, 0
  %14 = tail call i32 @putchar(i32 %13)
  %15 = add i32 50, 0
  %16 = tail call i32 @_sus(i32 %15)
  %17 = tail call i32 @putchar(i32 %16)
  %18 = add i32 45, 0
  store i32 %18, i32* %_b
  %19 = load i32, i32* %_b
  %20 = tail call i32 @putchar(i32 %19)
  %21 = add i32 10, 0
  %22 = tail call i32 @putchar(i32 %21)
  ret i32 1
}

define i32 @main() {
  %1 = add i32 30, 0
  store i32 %1, i32* @variavel_global_memo_a_bacans
  %2 = call i32 @_main()
  ret i32 %1
}
