extends Area2D

var vel  = 500
var dir  = Vector2(1, 1) setget set_dir

func _ready():
	#look_at(get_global_mouse_position())
	pass

func _process(delta):
	translate(dir * vel * delta)

func _on_notifier_screen_exited():
	queue_free()
	
func set_dir(val):
	dir      = val
	rotation = dir.angle()