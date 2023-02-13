(module
  ;; (func <signature> <locals> <body>)
  (func (param i32) (param i32) (result f64)
    ;; here goes some local variable
    (local i32)
    ;; some func body
  )

  ;; local.get <local_index>, local.set <local_index>

  (func (param i32) (param f32) (local f64)
    local.get 0
    local.get 1
    local.get 2
  )

  (func (param $p1 i32) (param $p2 f32) (local $loc f64)
    local.get $p1
    local.get $p2
    local.get $loc

    ;; ...
  )

  (func (param $p i32) (result i32)
    local.get $p
    local.get $p
    i32.add
  )
)
