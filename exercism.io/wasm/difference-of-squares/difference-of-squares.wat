(module
  (func $squareOfSum (export "squareOfSum") (param $max i32) (result i32)
    (local $sum i32)
    (local $i i32)

    (local.set $sum (i32.const 0))
    (local.set $i (i32.const 1))

    (loop $loop
      (local.set $sum (i32.add (local.get $sum) (local.get $i)))
      (local.set $i (i32.add (local.get $i) (i32.const 1)))
      (br_if $loop (i32.le_s (local.get $i) (local.get $max)))
    )

    (i32.mul (local.get $sum) (local.get $sum))
  )

  (func $sumOfSquares (export "sumOfSquares") (param $max i32) (result i32)
    (local $sum i32)
    (local $i i32)

    i32.const 0
    local.set $sum

    i32.const 1
    local.set $i

    (loop
      local.get $i ;; $i * $i
      local.get $i
      i32.mul

      local.get $sum ;; sum += i^2
      i32.add
      local.set $sum

      local.get $i ;; increment $i
      i32.const 1
      i32.add
      local.set $i

      local.get $i ;; $i < $max
      local.get $max
      i32.le_s

      br_if 0)

    local.get $sum
  )

  (func (export "difference") (param $max i32) (result i32)
    (call $squareOfSum (local.get $max))
    (call $sumOfSquares (local.get $max))
    i32.sub
  )
)
