declare i32 @getchar()
declare i32 @putchar(i32)
define void @_main() {
  ret void
}

define i32 @main() {
  %1 = call i32 @_main()
  ret i32 %1
}
