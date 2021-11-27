#adventure story
import time #delays will be added for dramatic effect

ready=input("Welcome to The Hero of Avalon, ready to play?\n")
if ready.capitalize()=="Yes":
    print("Ok, let's go!")
    time.sleep(1)
    print("3") #countdown to start the game
    time.sleep(1)
    print("2")
    time.sleep(1)
    print("1\n\n")
    time.sleep(2)
    print("My name is Peregrin, and I will be your squire on this journey") #Peregrin will narrate the story
    name=input("What is your name?\n") #store user's name
    print("Welcome,", name)
    print("You must help Avalon! The evil wizard Grendel has seized") #story background
    print("the castle and has captured the King and Queen. Suit up")
    print("and get ready to save the city!\n")
    time.sleep(4)
    print("Here. I've laid out some weapons for you. Choose your weapons:")
    weapons=["sword", "axe", "hammer", "crossbow", "flail"] #weapons on table
    yourWeapons=[]
    for weapon in weapons:
        choice=input("Would you like a "+weapon+"?\n")
        if choice.capitalize()=="Yes":
            yourWeapons.append(weapon) #each weapon chosen will be added to the empty list
    print("Ok, here are your weapons:")
    print(yourWeapons)
    time.sleep(1)
    print("You look ready! There are four ways to get to the castle: through")
    print("the raging river, the high hills, the vicious valley, or the dark forest\n")
    time.sleep(1)
    choice2=input("Which way would you like to go? River, hills, valley, or forest?\n")
    while choice2.capitalize()!="Forest": #if the user picks anything other than forest, they will be asked to pick again
        print("Uh oh! That doesn't sound like a good idea, pick again.")
        time.sleep(1)
        choice2=input("Which way would you like to go? River, hills, valley, or forest?\n")
    print("Good choice! Let's go through the forest.\n")
    time.sleep(1)
    print("Oh no! I see one of Grendel's minions up ahead!")
    choice4=input("Would you like to fight or retreat?\n")
    if choice4.capitalize()=="Retreat":
        print("Ok, let's retreat")
        print("I see an opening through the woods, let's sneak around the minion.")
        print("Shhhh, be really quiet!")
        time.sleep(1)
    elif choice4.capitalize()=="Fight":
        print(yourWeapons)
        print("Quick! Choose a weapon: Enter the index of the weapon you'd like to use.")
        choice3=eval(input("What weapon do you choose?\n")) #user chooses a weapon from his list of weapons by using the index
        print("Good luck!\n")
        print(".\n") #dramatic pauses as fight takes place
        time.sleep(.5)
        print(".\n")
        time.sleep(.5)
        print(".\n")
        time.sleep(.5)
        print("You've slayed the minion with your "+yourWeapons[choice3]+", nice job!")
        print("Let's keep moving...\n")
        time.sleep(1)
    print("We've made it through the forest! I can see the castle!")
    while True: #infinite loop until user enter an acceptable input
        choice5=input("Should we enter through the front gates or sneak around back?\n")
        if choice5.capitalize()=="Front gates":
            print("Ok,",name,"lets enter through the front gates.\n")
            print("Oh no! Grendel has spotted us!\n")
            time.sleep(3)
            print("Grendel sends a fire ball towards you, knocking you to the ground")
            print("His minions capture you and tie you up with the King and Queen\n\n")
            time.sleep(4)
            print("Sorry, you lose! Better luck next time!") #user choses front gates, loses
            break
        elif choice5.capitalize()=="Sneak around back":
            print("Ok,", name+", let's sneak around back.")
            time.sleep(1)
            print("You enter a back door to the castle, entering a room and see")
            print("two of Grendel's minions... oh wait! It's the King and Queen!")
            time.sleep(2)
            choice6=input("Should we save them?\n")
            if choice6.capitalize()=="No":
                print("You run passed the King and Queen to the main hall\n")
            elif choice6.capitalize()=="Yes":
                print("You break the chains that tie up the King and Queen")
                print("They thank you endlessly and promise you mounds of gold if")
                print("you can defeat Grendel and get their castle back.\n")
                time.sleep(5)
            print("You enter the main hall of the castle and see the evil wizard Grendel")
            print("sitting on the throne. You notice the magic fire stone around his neck, from")
            print("which he draws all of his power. He spots you and sends a fireball your way.")
            time.sleep(5)
            choice7=input("What do you do? Block or dodge?\n")
            if choice7.capitalize()=="Block":
                print("You get out your shield to block the fireball, but it")
                print("is too powerful and hits you, knocking you to the ground.\n")
                time.sleep(4)
                print("Sorry, you lose! Better luck next time!") #user choses to block the fireball, loses
                break
            elif choice7.capitalize()=="Dodge":
                print("You dodge the fireball and approach the evil wizard")
                print("You draw your", yourWeapons[0]+"...\n")
                time.sleep(3)
                print("Grendel draws his sword and swings at you, but you")
                print("quickly sidestep and swing your", yourWeapons[0]+",\n")
                time.sleep(3)
                print("Grendel falls, and you take away the magic fire stone.\n")
                time.sleep(2)
                print("Congrats!! You've defeated the evil wizard Grendel and saved Avalon!!")
                break
        else:
            print("Please enter front gates or sneak around back")
else:
    print("Ok, come back soon!")
