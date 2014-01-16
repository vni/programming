#!/usr/bin/env lua

tuple = require("tuple")

x = tuple.new(10, "hi", {}, 3)
print(x(1))
print(x(2))
print(x())
