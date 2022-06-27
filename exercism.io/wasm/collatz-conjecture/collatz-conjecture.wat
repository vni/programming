(module
  (func (export "steps") (param $n i32) (result i32)
    (if
      (i32.le_s (local.get $n) (i32.const 0))
      (then
        i32.const -1
        return))

    local.get $n
    i32.const 0
    call $helper)

  (func $helper (param $n i32) (param $steps_already i32) (result i32)
    (if
      (i32.eq (local.get $n) (i32.const 1))
      (then
        local.get $steps_already
        return))

    (if
      (i32.and (local.get $n) (i32.const 1)) ;; odd
      (then
        local.get $n
        i32.const 3
        i32.mul
        i32.const 1
        i32.add

        local.get $steps_already
        i32.const 1
        i32.add

        call $helper
        return))

    ;; even
    local.get $n
    i32.const 2
    i32.div_s

    local.get $steps_already
    i32.const 1
    i32.add

    call $helper
    return;;))
  )
)
