(module
  (import "console" "log" (func $log (param i32 i32)))
  (import "js" "mem" (memory 1))
  (data (i32.const 120) "Hello, world!11223344")
  (func (export "writeHello")
    i32.const 120
    i32.const 21
    call 0))





(;
 ;(module
 ;  (import "console" "log" (func $log (param i32 i32)))
 ;  (import "js" "mem" (memory 1))
 ;  (data (i32.const 0) "Hi")
 ;  (func (export "writeHi")
 ;    i32.const 0  ;; pass offset 0 to log
 ;    i32.const 2  ;; pass length 2 to log
 ;    call $log))
 ;
 ;)
