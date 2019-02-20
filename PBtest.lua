package.path = ';/root/dbserver/opt/lua-protobuf/?.lua'
package.cpath = ';/root/dbserver/lib/?.so'


local pb = require "pb"
local protoc = require "protoc"


-- load schema from text
assert(protoc:load [[
   message Phone {
      optional string name        = 1;
      optional int64  phonenumber = 2;
   }
   message Person {
      optional string name     = 1;
      optional int32  age      = 2;
      optional string address  = 3;
      repeated Phone  contacts = 4;
   } ]])

local data = testdata
-- encode lua table data into binary format in lua string and return
local bytes = assert(pb.encode("Person", data))
print(pb.tohex(testdata))

-- and decode the binary data back into lua table
local data2 = assert(pb.decode("Person", bytes))
print(require "serpent".block(data2))
