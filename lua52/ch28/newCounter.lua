#!/usr/bin/env lua

function newCounter()
	local v = 0
	return function()
					v=v+1
					return v
				end
end

c = newCounter()
print(c)
print("c: ", c())
print("c: ", c())
print("c: ", c())

d = newCounter()
print(d)
print("d: ", d())
print("d: ", d())
print("d: ", d())

print("=========")
print(c(), d())
print("c: ", c())
print("c: ", c())
print("=========")
print(c(), d())

e = newCounter()
print("=================")
print(c(), d(), e())
