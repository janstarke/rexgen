#!d:\Program Files (x86)\Lua\5.1\lua.exe
package.cpath = 'C:/Program Files/librexgen/lib/rexgen-0.1.0.dll'
local rexgen = require 'rexgen'

if (#arg ~= 1 and #arg ~= 2) then
  print 'Usage: rexgen.lua [-i] <regex>'
  return
end

if (arg[1] == "-i" and #arg < 2) then
  print 'Usage: rexgen.lua [-i] <regex>'
  return
end


local regex;
local ignoreCase = false;
if (arg[1] == "-i") then
  ignoreCase = true
  regex = arg[2]
else
  ignoreCase = false
  regex = arg[1]
end


local words, tree = rexgen.parse_regex(regex, ignoreCase)

--[[
print(tree)
--]]

for word in words do
  print(word)
end
