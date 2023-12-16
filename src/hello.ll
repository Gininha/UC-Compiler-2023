declare i32 @getchar()
declare i32 @putchar(i32)
define i32 @_main() {
  %i = alloca i32
  store i32 0, i32* %i
  br label %L1
L1:
  %1 = load i32, i32* %i
  %2 = add i32 10, 0
  %3 = icmp slt i32 %1, %2
  br i1 %3, label %L1Body, label %L1End
L1Body:
  %4 = alloca i32
  %5 = load i32, i32* %i
  %6 = add i32 10, 0
  %7 = icmp eq i32 %5, %6
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %L4then, label %L4else
L4then:
  %9 = alloca i32
  store i32 115, i32* %9
  %10 = load i32, i32* %9
  %11 = tail call i32 @putchar(i32 %10)
  store i32 %11, i32* %4
  br label %L4end
L4else:
  store i32 %-1, i32* %4
  br label %L4end
L4end:
  %12 = load i32, i32* %4
  %13 = alloca i32
  %14 = load i32, i32* %i
  %15 = add i32 9, 0
  %16 = icmp sge i32 %14, %15
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %L13then, label %L13else
L13then:
  %18 = alloca i32
  store i32 107, i32* %18
  %19 = load i32, i32* %18
  %20 = tail call i32 @putchar(i32 %19)
  store i32 %20, i32* %13
  br label %L13end
L13else:
  store i32 %-1, i32* %13
  br label %L13end
L13end:
  %21 = load i32, i32* %13
  %22 = alloca i32
  %23 = load i32, i32* %i
  %24 = add i32 8, 0
  %25 = icmp sgt i32 %23, %24
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %L22then, label %L22else
L22then:
  %27 = alloca i32
  store i32 108, i32* %27
  %28 = load i32, i32* %27
  %29 = tail call i32 @putchar(i32 %28)
  store i32 %29, i32* %22
  br label %L22end
L22else:
  store i32 %-1, i32* %22
  br label %L22end
L22end:
  %30 = load i32, i32* %22
  %31 = alloca i32
  %32 = load i32, i32* %i
  %33 = add i32 7, 0
  %34 = icmp ne i32 %32, %33
  %35 = icmp ne i32 %34, 0
  br i1 %35, label %L31then, label %L31else
L31then:
  %36 = alloca i32
  store i32 112, i32* %36
  %37 = load i32, i32* %36
  %38 = tail call i32 @putchar(i32 %37)
  store i32 %38, i32* %31
  br label %L31end
L31else:
  store i32 %-1, i32* %31
  br label %L31end
L31end:
  %39 = load i32, i32* %31
  %40 = alloca i32
  %41 = load i32, i32* %i
  %42 = add i32 6, 0
  %43 = icmp slt i32 %41, %42
  %44 = icmp ne i32 %43, 0
  br i1 %44, label %L40then, label %L40else
L40then:
  %45 = alloca i32
  store i32 117, i32* %45
  %46 = load i32, i32* %45
  %47 = tail call i32 @putchar(i32 %46)
  store i32 %47, i32* %40
  br label %L40end
L40else:
  store i32 %-1, i32* %40
  br label %L40end
L40end:
  %48 = load i32, i32* %40
  %49 = alloca i32
  %50 = load i32, i32* %i
  %51 = add i32 5, 0
  %52 = icmp sle i32 %50, %51
  %53 = icmp ne i32 %52, 0
  br i1 %53, label %L49then, label %L49else
L49then:
  %54 = alloca i32
  store i32 108, i32* %54
  %55 = load i32, i32* %54
  %56 = tail call i32 @putchar(i32 %55)
  store i32 %56, i32* %49
  br label %L49end
L49else:
  store i32 %-1, i32* %49
  br label %L49end
L49end:
  %57 = load i32, i32* %49
  br label %L1
L1End:
  %58 = add i32 0, 0
  ret i32 %58
}

define i32 @main() {
  %1 = call i32 @_main()
  ret i32 %1
}
