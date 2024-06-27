extends Node2D

@export var PADDLE_SPEED : int=600

@onready var score_label = $HUD/Control/MarginContainer/VBoxContainer/PlayerScore
@onready var maxScore_label = $HUD/Control/MarginContainer/VBoxContainer/MaxScore
@onready var timer = $BallTimer

var win_size : Vector2
const START_SPEED : int = 500
const ACCEL : int = 25
var speed : int
var dir : Vector2
var score := [0]
var max = 0

func _on_ball_timer_timeout():
	$Ball.new_ball()

func _on_score_body_entered(body):
	score[0] = 0
	max = 0
	score_label.text = "Score: " + str(score[0])
	$BallTimer.start()

func _on_wall_body_entered(body):
	score[0] += 1
	score_label.text = "Score: " + str(score[0])
