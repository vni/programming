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
