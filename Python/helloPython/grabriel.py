# Catch me if you want!
import turtle
import random

# Choose the difficulty level
print("What difficulty level do you want to play?")
chosen_level = input()

# Create Gabriel - The Player
gabriel = turtle.Turtle()
gabriel.color('green')
gabriel.penup()
gabriel.forward(100)
gabriel.shape('square')

# Johannes draws field
johannes = turtle.Turtle()
johannes.color('green')
johannes.speed(20)

field_width = 200
field_long = 180

johannes.forward(field_width)
johannes.left(90)
johannes.forward(field_long)
johannes.left(90)
johannes.forward(field_width)
johannes.left(90)
johannes.forward(field_long)

# Keyboard settings 
def move_forward():
  gabriel.forward(5)

def move_backward():
  gabriel.backward(5)

def turn_left():
  gabriel.left(5)

def turn_right():
  gabriel.right(5)

wn = turtle.Screen()
wn.onkey(move_forward, "Right")
wn.onkey(move_backward, "Left")
wn.listen()
wn.mainloop()


while True:
  george = turtle.Turtle()
  george.color('orange')

  # Set the speed levels
  if chosen_level == "very easy":
    george.speed(1)
   
  if chosen_level == 'easy':
    george.speed(2)

  if chosen_level == 'normal':
    george.speed(4)

  if chosen_level == 'hard':
    george.speed(6)

  if chosen_level == 'very hard':
    george.speed(8)

  if chosen_level == 'godly':
    george.speed(10)

  if chosen_level == 'very very very very very very very very insaneeeeee':
    george.speed(0)

  # Create George - the target
  george.shape('circle')
  george.penup()
  george.left(90)
  george.forward(field_long)
  george.right(90)

  george.forward(random.randint(0, 200))
  george.left(90)
  george.backward(180)
  george.hideturtle()