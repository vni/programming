#!/usr/bin/env lua

lib = require("ch27lib")

print("summation")
print(lib.summation()) --> 0
print(lib.summation(2.3, 5.4)) --> 7.7
print(lib.summation(2.3, 5.4, -34)) --> -26.3
--print(lib.summation(2.3, 5.4, {})) --> error

print("\nmypack")
t = lib.mypack("a", 20, true, function() return 42 end)
for k,v in pairs(t) do
	print(k,v)
end

print("\nreverse")
print(lib.reverse(1, "hello", 20)) --> 20	hello	1

print("\nforeach")
lib.foreach({x = 10, y = 20}, print)

print("\nDONE")
