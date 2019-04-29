extends KinematicBody2D

var speed = 25
var brake = 0.95
var acceleration = Vector2(0, 0)
var pre_bulllet = preload("res://scenes/bullet.tscn")

func _ready():
	pass 

func _process(delta):
	
	var vector  = Vector2(0,0)
	
	if Input.is_action_pressed("ui_right"):
		vector += Vector2(1,0)
	if Input.is_action_pressed("ui_left"):
		vector -= Vector2(1,0)
	if Input.is_action_pressed("ui_up"):
		vector -= Vector2(0,1)
	if Input.is_action_pressed("ui_down"):
		vector += Vector2(0,1)
		
	acceleration = brake*(acceleration+vector*delta)
	translate(acceleration*speed)
	#rotation = -acceleration.angle_to(Vector2(0,-1))
		
	if Input.is_action_just_pressed("ui_shot"):
		print("booom")
		var bullet = pre_bulllet.instance()
		bullet.global_position = $Berrel/lugar.global_position
		get_parent().add_child(bullet)
	

	
	