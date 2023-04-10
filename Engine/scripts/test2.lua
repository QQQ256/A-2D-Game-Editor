local input = engine.get_horizontal_input();
local position = engine.get_transform_component().position;
local speed = 5;
position.x = position.x + (speed * input);