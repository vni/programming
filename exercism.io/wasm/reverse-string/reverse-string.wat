(module
  (memory (export "mem") 1)

  (func (export "reverseString") (param $offset i32) (param $length i32) (result i32 i32)
    ;; set first and last index
    (local $first i32)
    (local $last i32)
    (local $temp_first i32)
    (local $temp_last i32)

    local.get $offset ;; initialize first
    local.set $first

    local.get $offset ;; initialize last
    local.get $length
    i32.add
    i32.const 1 ;; we should point to the last character, not the one past last
    i32.sub
    local.set $last

    local.get $first ;; check that $first < $last
    local.get $last
    i32.ge_u
    (if (then local.get $offset
              local.get $length
              return))

    (loop
      ;; swap byte at $first and $last
      local.get $first
      i32.load8_u
      local.set $temp_first

      local.get $last
      i32.load8_u
      local.set $temp_last

      local.get $first
      local.get $temp_last
      i32.store8

      local.get $last
      local.get $temp_first
      i32.store8

      ;; adjust $first and $last
      local.get $first
      i32.const 1
      i32.add
      local.set $first

      local.get $last
      i32.const -1
      i32.add
      local.set $last

      ;; check that $first < $last
      local.get $first
      local.get $last
      i32.lt_u
      br_if 0)

    local.get $offset
    local.get $length
  )
)
