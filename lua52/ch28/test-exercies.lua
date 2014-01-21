#!/usr/bin/env lua

ex = require("exercies")

t = ex.filter({1, 3, 20, -4, 5}, function(x) return x < 5 end)
for i=1,#t do
	io.write(t[i], '    ')
end
io.write('\n')

t = ex.filter({"hello", "hi", "bye", "Good bye", "end"}, function(x) return #x > 3 end)
for i=1,#t do
	io.write(t[i], '    ')
end
io.write('\n')

print("ex.split(\"hi\\0001:ho\\00023333:there\", \":\")")
t = ex.split("hi\0001:ho\00023333:there", ":")
for i=1,#t do
	io.write(t[i], '\t')
	--print(#t[i], t[i]) 
end
io.write('\n')

print("ex.split(\"hi\\0ho\\0there\\0\", \"\\0\")")
t = ex.split("hi\0ho\0there\0", "\0")
for i=1,#t do
	--io.write(t[i], '\t')
	print(#t[i], t[i]) 
end
--io.write('\n')
