local rexgen = require 'rexgen'

if (#arg ~= 1) then
  print 'Usage: rexgen.lua <regex>'
  return
end

local words, tree = rexgen.parse_regex(arg[1])

--[[
print(tree)
--]]

for word in words do
  print(word)
end