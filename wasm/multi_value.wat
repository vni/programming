(module
  (func (result i32 i32 i32)
    i32.const 15
    i32.const 20
    i32.const 25
  )

  (func (export "add_two_numbers") (result i32)
    call 0
    i32.add
    i32.add
  )
)

;; (module
;;   (func $get_two_numbers (result i32 i32)
;;     i32.const 1
;;     i32.const 2
;;   )
;;   (func (export "add_two_numbers") (result i32)
;;     call $get_two_numbers
;;     i32.add
;;   )
;; )
