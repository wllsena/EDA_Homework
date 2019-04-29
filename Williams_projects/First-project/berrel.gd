extends Node2D

var num_bullets  = 3
var reloads      = 5 
var pre_bulllet  = preload("res://scenes/bullet.tscn")

func _ready():
	pass 

func _process(delta):
	look_at(get_global_mouse_position())
	global_position = $"../tank"/position.global_position
	
	if Input.is_action_just_pressed("ui_shot") and num_bullets > 0:
		#if get_tree().get_nodes_in_group("cannon_bullets").size() < 3:
		var bullet = pre_bulllet.instance() 
		bullet.global_position = position.global_position
		$"../".add_child(bullet)
		num_bullets -= 1
		
	if Input.is_action_just_pressed("ui_reload") and reloads > 0:
		num_bullets += 3
		reloads -= 1