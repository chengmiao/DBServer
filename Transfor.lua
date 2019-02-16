package.path = ';/root/dbserver/opt/lua-protobuf/?.lua'
package.cpath = ';/root/dbserver/lib/?.so'


local pb = require "pb"
local protoc = require "protoc"

local p = protoc.new()

local data = {}
local type_table = {}
local tmp = {}

protoc.paths[#protoc.paths + 1] = "/root/dbserver/proto"
--p.loadfile(filename)
protoc:loadfile(filename)

local message_name = string.sub(filename, 1, -7)
local g_type_name

for name in pb.types() do
    --table.insert(type_table, name, name)
    type_table[name] = name
end 

function MakeMessageTable(field_type, main_table) 
    for field_name, _, type in pb.fields(field_type) do
        if type_table[type] == nil then
            if type == "int32" then
                --table.insert(main_table, field_name, 1024)
                main_table[field_name] = 1024
            elseif type == "string" then
                --table.insert(main_table, field_name, "ChengMiao")
                main_table[field_name] = "ChengMiao"
            end
        else
            --table.insert(main_table, field_name, tmp)
            main_table[field_name] = {}
            main_table[field_name][1] = MakeMessageTable(type, tmp)
        end
    end

    return main_table
end 

for name, type_name in pb.types() do
    if type_name == message_name then
        g_type_name = name
        MakeMessageTable(name, data)
    end
end

-- encode lua table data into binary format in lua string and return
local bytes = assert(pb.encode(g_type_name, data))
--print(pb.tohex(bytes))

-- and decode the binary data back into lua table
local data2 = assert(pb.decode(g_type_name, bytes))
--print(require "serpent".block(data2))
print(require "serpent".block(type_table))


