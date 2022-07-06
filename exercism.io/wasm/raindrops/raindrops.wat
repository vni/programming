(module
  (memory (export "mem") 1)

  (func $reverse (param $end i32)
    (local $lo i32)
    (local $hi i32)
    (local $t_lo i32)
    (local $t_hi i32)

    (local.set $lo (i32.const 0))
    (local.set $hi (i32.sub (local.get $end)
                            (i32.const 1)))

    (loop
      (if (i32.ge_u (local.get $lo) (local.get $hi))
          (then (return)))

      local.get $lo
      i32.load8_u
      local.set $t_lo

      local.get $hi
      i32.load8_u
      local.set $t_hi

      local.get $lo
      local.get $t_hi
      i32.store8

      local.get $hi
      local.get $t_lo
      i32.store8

      local.get $lo
      i32.const 1
      i32.add
      local.set $lo

      local.get $hi
      i32.const -1
      i32.add
      local.set $hi

      br 0)
  )

  (func $number_to_string (param $num i32) (result i32) ;; offset
    (local $cursor i32)
    (local $t i32)

    (local.set $cursor (i32.const 0))

    loop
      local.get $cursor
      local.get $num
      i32.const 10
      i32.rem_u
      i32.const 48 ;; 0x30 ;; convert digit to ascii_digit
      i32.add
      i32.store8

      local.get $cursor
      i32.const 1
      i32.add
      local.set $cursor

      local.get $num
      i32.const 10
      i32.div_u
      local.tee $num
      i32.const 0
      i32.ne
      br_if 0
    end

    local.get $cursor
    call $reverse

    local.get $cursor
  )

  (func $store_and_advance (param $cursor i32) (param $char i32) (result i32)
          local.get $cursor
          local.get $char
          i32.store8

          local.get $cursor
          i32.const 1
          i32.add
  )

  (func (export "convert") (param $input i32) (result i32 i32)
    (local $cursor i32)
    (local $convert_to_numbers i32) ;; bool

    (local.set $cursor (i32.const 0))
    (local.set $convert_to_numbers (i32.const 0))

    (if (i32.eq (i32.rem_u (local.get $input) (i32.const 3)) (i32.const 0))
        (then ;; Pling
          (local.set $convert_to_numbers (i32.const 1))

          local.get $cursor
          i32.const 80 ;; 'P'
          call $store_and_advance
          local.tee $cursor

          i32.const 108 ;; 'l'
          call $store_and_advance
          local.tee $cursor

          i32.const 105 ;; 'i'
          call $store_and_advance
          local.tee $cursor

          i32.const 110 ;; 'n'
          call $store_and_advance
          local.tee $cursor

          i32.const 103 ;; 'g'
          call $store_and_advance
          local.set $cursor))

    (if (i32.eq (i32.rem_u (local.get $input) (i32.const 5)) (i32.const 0))
        (then ;; Plang
          (local.set $convert_to_numbers (i32.const 1))

          local.get $cursor
          i32.const 80 ;; 'P'
          call $store_and_advance
          local.tee $cursor

          i32.const 108 ;; 'l'
          call $store_and_advance
          local.tee $cursor

          i32.const 97 ;; 'a'
          call $store_and_advance
          local.tee $cursor

          i32.const 110 ;; 'n'
          call $store_and_advance
          local.tee $cursor

          i32.const 103 ;; 'g'
          call $store_and_advance
          local.set $cursor))

    (if (i32.eq (i32.rem_u (local.get $input) (i32.const 7)) (i32.const 0))
        (then ;; Plong
          (local.set $convert_to_numbers (i32.const 1))

          local.get $cursor
          i32.const 80 ;; 'P'
          call $store_and_advance
          local.tee $cursor

          i32.const 108 ;; 'l'
          call $store_and_advance
          local.tee $cursor

          i32.const 111 ;; 'o'
          call $store_and_advance
          local.tee $cursor

          i32.const 110 ;; 'n'
          call $store_and_advance
          local.tee $cursor

          i32.const 103 ;; 'g'
          call $store_and_advance
          local.set $cursor))

    (if (i32.eqz (local.get $convert_to_numbers))
        (then local.get $input
              call $number_to_string
              local.set $cursor))

    (return (i32.const 0) (local.get $cursor))
  )
)
