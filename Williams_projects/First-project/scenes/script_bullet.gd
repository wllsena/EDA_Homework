extends Area2D

var vel  = 1000
var dir  = Vector2(0, -1)

func _ready():
	pass

func _process(delta):
	translate(dir * vel * delta)