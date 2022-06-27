(module
  ;; squareNum is signed
  ;; Result is unsigned
  (func $square (export "square") (param $squareNum i32) (result i64)
    (if (i32.or
          (i32.lt_s (local.get $squareNum) (i32.const 1))
          (i32.gt_s (local.get $squareNum) (i32.const 64)))
      (then (return (i64.const 0))))

    (i64.shl (i64.const 1)
      (i64.sub (i64.extend_i32_s (local.get $squareNum)) (i64.const 1)))
  )

  ;; Result is unsigned
  (func (export "total") (result i64)
    (return (i64.const 0xFFFFFFFFFFFFFFFF))
  )
)
