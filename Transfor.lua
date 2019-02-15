package.path = ';/root/dbserver/opt/lua-protobuf/?.lua'
package.cpath = ';/root/dbserver/lib/?.so'


local pb = require "pb"
local protoc = require "protoc"

local p = protoc.new()

local data = {}
local type_table = {}

p.paths[#p.paths + 1] = "/root/dbserver/proto"
p.loadfile(filename)

local message_name = string.sub(filename, 1, -5)

for name in pb.types() do
    table.insert(type_table, name, name)
end 

for name, type_name in pb.types() do
    if type_name == message_name then
        MakeMessageTable(name)
    end
end

function MakeMessageTable(field_type) 
    for field_name, _, type in pb.fields(field_type) do
        if tmp[type] == nil then
            if type == "int32" then
                table.insert(data, field_name, 1024)
            else if type == "string" then
                table.insert(data, field_name, "ChengMiao")
            end
        else
            local message_table = MakeMessageTable(type)
            table.insert(data, field_name, message_table)
        end
    end
end 

-- encode lua table data into binary format in lua string and return
local bytes = assert(pb.encode("Person", data))
print(pb.tohex(bytes))

-- and decode the binary data back into lua table
local data2 = assert(pb.decode("Person", bytes))
print(require "serpent".block(data2))


