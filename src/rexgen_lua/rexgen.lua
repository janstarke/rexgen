#!/usr/local/bin/lua

package.cpath = '/usr/local/lib/librexgen-lua.dylib'
local rexgen = require 'rexgen-lua'

if (#arg ~= 1) then
  print 'Usage: rexgen.lua <regex>'
  return
end

local regex = arg[1];
local words = rexgen.parse_regex(regex)

for word in words do
  print(word)
end
