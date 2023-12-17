declare i32 @getchar()
declare i32 @putchar(i32)
define void @_main() {
  ret void
}

define void @main() {
  call void @_main()
  ret void
}
