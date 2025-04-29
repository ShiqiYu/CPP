class Animal:
		def __init__(self, name):
			self.name = name

class Duck(Animal):
		def __init__(self, name):
			super(Duck, self).__init__(name)
		def Speak(self):
			print(self.name, ' Quack')

class Dog(Animal):
		def __init__(self, name):
			super(Dog, self).__init__(name)
		def Speak(self):
			print(self.name, ' Quack')
class Robot:
    def __init__(self, name):
       self.name = name       
    def Speak(self): 
        print(self.name, 'Beep')   
   
def testSpeak(duck):
	duck.Speak()

if __name__ == "__main__":
    duck = Duck('Tommy')
    dog = Dog('Fox')
    robot = Robot('Wall-E')
    testSpeak(duck)
    testSpeak(dog)
    testSpeak(robot)
      		
