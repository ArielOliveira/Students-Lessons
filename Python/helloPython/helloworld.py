# Turtle Race - Project1
import turtle

joe = turtle.Turtle()
joe.color("green")
joe.speed(12)

# Joe draws the Race Track
# Variables
turns = 90
straights = 300
small_forwards = 150
joe.forward(straights)
joe.left(turns)
joe.forward(small_forwards)
joe.left(turns)
joe.forward(straights)
joe.left(turns)
joe.forward(small_forwards)

# Racing turtles
roger = turtle.Turtle()
roger.shape("turtle")
roger.color("brown")
roger.left(90)
roger.forward(90)
roger.right(90)

luke = turtle.Turtle()
luke.shape("turtle")
luke.color('red')
luke.left(90)
luke.forward(45)
luke.right(90)

steven = turtle.Turtle()
steven.shape("turtle")
steven.color("blue")
steven.left(90)
steven.forward(128)
steven.right(90)

# Choose random speeds for turtles and let them race
import random

random_speed_luke = random.randint(10, 1000)
random_speed_roger = random.randint(10, 1000)
random_speed_steven = random.randint(10, 1000)

roger.speed(random_speed_roger)
roger.forward(straights)
roger.write(random_speed_roger)

luke.speed(random_speed_luke)
luke.forward(straights)
luke.write(random_speed_luke)

steven.speed(random_speed_steven)
steven.forward(straights)
steven.write(random_speed_steven)
joe.forward(30)


# Roger wins
if random_speed_roger > random_speed_steven and random_speed_roger > random_speed_luke:
  joe.write("   Roger wins! He is the brown one.")

# Steven wins
if random_speed_steven > random_speed_luke and random_speed_steven > random_speed_roger:
  joe.write("   Steven wins! He is the blue one.")
  
# Luke wins
if random_speed_luke > random_speed_roger and random_speed_luke > random_speed_roger:
  joe.write("   Luke wins! He is the red one.")

screen = turtle.Screen()

def GetOut():
    screen.bye()

screen.onkey(GetOut, "Escape")
screen.listen()
screen.mainloop()