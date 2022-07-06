(module
  (memory (export "mem") 1)

  (func (export "toRna") (param $offset i32) (param $length i32) (result i32 i32)
    (local $p i32)
    (local $end i32)
    (local $t i32)

    (local.set $p (local.get $offset)) ;; initialize $p
    (local.set $end (i32.add (local.get $offset)
                             (local.get $length))) ;; initialize $end

    ;; 65 'A' -> 'U' 85
    ;; 67 'C' -> 'G' 71
    ;; 71 'G' -> 'C' 67
    ;; 84 'T' -> 'A' 65

    (loop
      (local.set $t (i32.load8_u (local.get $p)))

      (if (i32.eq (local.get $t) (i32.const 65 (;'A';)))
          (then local.get $p
                i32.const 85 ;; 'U'
                i32.store8))

      (if (i32.eq (local.get $t) (i32.const 67 (;'C';)))
          (then local.get $p
                i32.const 71 ;; 'G'
                i32.store8))

      (if (i32.eq (local.get $t) (i32.const 71 (;'G';)))
          (then local.get $p
                i32.const 67 ;; 'C'
                i32.store8))

      (if (i32.eq (local.get $t) (i32.const 84 (;'T';)))
          (then local.get $p
                i32.const 65 ;; 'A'
                i32.store8))

      ;; ++$p < $end
      (i32.lt_u (local.tee $p (i32.add (local.get $p) (i32.const 1)))
                (local.get $end))
      br_if 0)

    (return (local.get $offset) (local.get $length))
  )
)
