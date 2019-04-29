extends KinematicBody2D

var speed      = 15
var brake      = 0.95
var accelr     = Vector2(3, 0)
var speed_rot  = 0.15
var brake_rot  = 0.95
var accelr_rot = 0

func _ready():
	pass 

func _process(delta):
	
	var move   = 0
	var angle  = 0
	
	if Input.is_action_pressed("ui_right"):
		angle += 1
	if Input.is_action_pressed("ui_left"):
		angle -= 1
	if Input.is_action_pressed("ui_up"):
		move  -= 1
	if Input.is_action_pressed("ui_down"):
		move  += 1
	if Input.is_action_just_pressed("ui_shot"):
		move  += 10
		
	accelr_rot   = brake_rot*(accelr_rot+angle*delta)
	rotation    += accelr_rot*speed_rot
	accelr       = brake*(accelr+Vector2(cos(rotation), sin(rotation))*move*delta)
	translate(accelr*speed)
