#!/usr/bin/env lua

supval = require("shared_upvalues")

print("a()", supval.a())
print("a()", supval.a())
print("b()", supval.b())
print("b()", supval.b())
print("c()", supval.c())
print("c()", supval.c())

print("=====================================")
print("a()", supval.a())
print("b()", supval.b())
print("c()", supval.c())
