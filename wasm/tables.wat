(module
  (table 2 funcref)
  (elem (i32.const 0) $f1 $f2)
  (func $f1 (result i32)
    i32.const 42)
  (func $f2 (result i32)
    i32.const 13)

  ;; (type $return_i32 (func (result i32)))
  ;; (func (export "callByIndex") (param $i i32) (result i32)
  ;;   local.get $i
  ;;   call_indirect (type $return_i32))

  (type (func (result i32)))
  (func (export "callByIndex") (param i32) (result i32)
    ;; local.get 0
    ;; call_indirect (type 0))

    (call_indirect (type 0) (local.get 0))
  )
)
