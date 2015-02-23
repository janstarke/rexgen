#!${LUA_BINARY}
package.cpath = '${CMAKE_INSTALL_PREFIX}/lib/${librexgen-lua}${CMAKE_SHARED_LIBRARY_SUFFIX}'
local rexgen = require '${prj}-lua'

if (#arg ~= 1) then
  print 'Usage: rexgen.lua <regex>'
  return
end

local regex = arg[1];
local words = rexgen.parse_regex(regex)

for word in words do
  print(word)
end
