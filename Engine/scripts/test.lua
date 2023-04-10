-- print("enter test.lua")
local position = engine.get_transform_component().position;
local speed = 1;
-- print("[Lua] position.x " .. position.x)
position.x = position.x + speed;
-- print("[Lua] new position.x " .. position.x)

-- get the Transform component of the second test entity
local entity2 = engine.get_entity_by_name("test2")
local trans2 = engine.get_transform_component(entity2);
local positon2 = trans2.position;
print("[Lua] position2.x " .. position.x)
positon2.x = positon2.x + speed; 