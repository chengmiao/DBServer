package.path = ';/root/dbserver/opt/lua-protobuf/?.lua'
package.cpath = ';/root/dbserver/lib/?.so'


local pb = require "pb"
local protoc = require "protoc"

local p = protoc.new()

local data = {}
local type_table = {}

p.paths[#p.paths + 1] = "/root/dbserver/proto"
--p.loadfile(filename)
p.load[filename]()

local message_name = string.sub(filename, 1, -7)

for name in pb.types() do
    table.insert(type_table, name, name)
end 

for name, type_name in pb.types() do
    if type_name == message_name then
        MakeMessageTable(name, data)
    end
end

function MakeMessageTable(field_type, main_table) 
    local message_table = {}
    for field_name, _, type in pb.fields(field_type) do
        if type_table[type] == nil then
            if type == "int32" then
                table.insert(main_table, field_name, 1024)
            elseif type == "string" then
                table.insert(main_table, field_name, "ChengMiao")
            end
        else
            local tmp = MakeMessageTable(type, message_table)
            table.insert(main_table, field_name, tmp)
        end
    end

    return main_table
end 

-- encode lua table data into binary format in lua string and return
local bytes = assert(pb.encode("Person", data))
print(pb.tohex(bytes))

-- and decode the binary data back into lua table
local data2 = assert(pb.decode("Person", bytes))
print(require "serpent".block(data2))


