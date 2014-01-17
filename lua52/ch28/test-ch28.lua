#!/usr/bin/env lua

lib = require("ch28")

t = { 10, 20, 30, 40 }
lib.map(t, function(arg) return arg/10 end)

for _,v in ipairs(t) do
	print(v)
end

print("\nlib.upper(\"Hello world\"):")
print(lib.upper("Hello world"))

print("\nlib.concat({10, \"hello\", \"world\", 20})")
print(lib.concat({10, "hello", "world", 20}))

print("\nlib.newCounter():")
c = lib.newCounter()
print(c())
print(c())
print(c())
