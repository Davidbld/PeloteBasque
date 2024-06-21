extends Node2D

var win_size : Vector2
const START_SPEED : int = 500
const ACCEL : int = 25
var speed : int
var dir : Vector2
var score := [0]

const PADDLE_SPEED : int=400

func _on_ball_timer_timeout():
	$Ball.new_ball()

func _on_score_body_entered(body):
	score[0] = 0
	$HUD/PlayerScore.text = str(score[0])
	$HUD/BallTimer.start()


func _on_wall_body_entered(body):
	score[0] += 1
	$HUD/PlayerScore.text = str(score[0])
