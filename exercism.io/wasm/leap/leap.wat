(module
  ;; Returns 1 if leap year, 0 otherwise
  (func (export "isLeap") (param $year i32) (result i32)
    (if ;; % 400
      (i32.eqz
        (i32.rem_u
          (local.get $year)
          (i32.const 400)))
      (then
        i32.const 1
        return))

    (if ;; % 100
      (i32.eqz
        (i32.rem_u
          (local.get $year)
          (i32.const 100)))
      (then
         i32.const 0
         return))

    (if ;; % 4
      (i32.eqz
        (i32.rem_u
          (local.get $year)
          (i32.const 4)))
      (then
         i32.const 1
         return))

    (i32.const 0)
  )
)
