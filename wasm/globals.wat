(module
  (global (import "js" "global") (mut i32))
  (func (export "getGlobal") (result i32)
    (global.get 0))
  (func (export "incGlobal")
    (global.set 0
      (i32.add (global.get 0) (i32.const 4))))
  (func (export "incGlobal2")
    (global.get 0)
    (i32.const 10)
    (i32.add)
    (global.set 0)
  )
)






(;
(module
   (global $g (import "js" "global") (mut i32))
   (func (export "getGlobal") (result i32)
        (global.get $g))
   (func (export "incGlobal")
        (global.set $g
            (i32.add (global.get $g) (i32.const 1))))
)
;)
