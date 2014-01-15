#!/usr/bin/env lua

lib = require("ch28")

t = { 10, 20, 30, 40 }
lib.map(t, function(arg) return arg/10 end)

for _,v in ipairs(t) do
	print(v)
end

print("\nlib.upper(\"Hello world\"):")
print(lib.upper("Hello world"))
