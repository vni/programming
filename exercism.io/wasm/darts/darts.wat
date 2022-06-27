(module
  (func (export "score") (param $x f32) (param $y f32) (result i32)
    (local $d f32) ;; $distance
    (f32.sqrt (f32.add (f32.mul (local.get $x) (local.get $x))
                       (f32.mul (local.get $y) (local.get $y))))
    (local.tee $d)

    (if (f32.le (local.get $d) (f32.const 1.0))
      (then (return (i32.const 10))))

    (if (f32.le (local.get $d) (f32.const 5.0))
      (then (return (i32.const 5))))

    (if (f32.le (local.get $d) (f32.const 10.0))
      (then (return (i32.const 1))))

    (return (i32.const 0))
  )
)
