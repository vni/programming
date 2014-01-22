#!/usr/bin/env lua

trans = require("registry_transliterate")

trans.settrans({a="b", b="c", c="d", d=false})

input = 'abcd xyz abcd'
print(input)
res = trans.transliterate(input)
print(res)

t = trans.gettrans()
print("transliterate table:")
for k,v in pairs(t) do
	print(k,v)
end
