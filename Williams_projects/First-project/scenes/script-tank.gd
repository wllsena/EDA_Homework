extends KinematicBody2D

var speed = 10
var aceler = Vector2(0, 0)
var pre_bulllet = preload("res://scenes/bullet.tscn")

func _ready():
	pass 

func _process(delta):
	
	var vec  = Vector2(0,0)
	
	if Input.is_action_pressed("ui_right"):
		vec += Vector2(1,0)
	if Input.is_action_pressed("ui_left"):
		vec -= Vector2(1,0)
	if Input.is_action_pressed("ui_up"):
		vec -= Vector2(0,1)
	if Input.is_action_pressed("ui_down"):
		vec += Vector2(0,1)
		
	aceler = 0.99*(aceler+vec*delta)
	translate(aceler*speed)
	rotation = -aceler.angle_to(Vector2(0,-1))
		
	if Input.is_action_just_pressed("ui_shot"):
		print("booom")
		var bullet = pre_bulllet.instance()
		bullet.global_position = $Berrel/lugar.global_position
		get_parent().add_child(bullet)
	

	
	