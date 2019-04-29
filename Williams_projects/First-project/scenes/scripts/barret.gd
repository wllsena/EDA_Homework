extends Area2D

var num_bullets  = 50
var reloads      = 50
var pre_bulllet  = preload("res://scenes/bullet.tscn")

func _ready():
	pass 

func _process(delta):
	look_at(get_global_mouse_position())
	
	if Input.is_action_just_pressed("ui_shot") and num_bullets > 0:
		num_bullets -= 1
		
		var bullet = pre_bulllet.instance() 
		bullet.global_position = $position.global_position
		bullet.dir             = (get_global_mouse_position() - global_position).normalized()
		$"../../".add_child(bullet)
		
	if Input.is_action_just_pressed("ui_reload") and reloads > 0:
		reloads -= 1
		num_bullets += 5