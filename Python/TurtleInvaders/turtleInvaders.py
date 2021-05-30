import turtle

stage_width = 200
stage_length = 200



ship = turtle.Turtle()
ship.penup()
ship.left(90)
ship.forward(20)

stage = turtle.Turtle()
stage.shape("classic")
stage.forward(100)
stage.left(90)
stage.forward(stage_length)
stage.left(90)
stage.forward(stage_width)
stage.left(90)
stage.forward(stage_length)
stage.left(90)
stage.forward(100)

ship_x = 0
ship_y = 0

def moveLeft():
    global ship_x
    ship_x -= 5
    ship.setx(ship_x)

def moveRight():
    global ship_x
    ship_x += 5
    ship.setx(ship_x)

def shoot():
    global stage_length
    global ship_x
    global ship_y
    fire = turtle.Turtle()
    fire.setx(ship_x)
    fire.sety(ship_y + 5)
    fire.shape("circle")
    fire.penup()
    fire.left(90)
    fire.forward(stage_length)
    fire.hideturtle()


screen = turtle.Screen()
screen.onkey(moveLeft, "Left")
screen.onkey(moveRight, "Right")
screen.onkey(shoot, "space")
screen.listen()
screen.mainloop()

