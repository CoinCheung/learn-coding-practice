#/usr/bin/python
# filename:2048.py


import curses
import os
from random import randrange

#-------------------------------------------#
#classname: GameField()
# the class of Game Field, draw the game field,
# operation of moving(upward, downward, left, right) or merge, add new number for each step
# evaluate the situation (if the player win or lose)
#------------------------------------------#


class GameField():
    def __init__(self, screen):
        self.height = 4
        self.width = 4
        self.score = 0
        self.winvalue = 2048
        self.highscore = 0
        self.stdscr = screen
        self.actiondict = dict(
            zip('wsadrqWSADRQ', ('up', 'down', 'left', 'right', 'restart', 'quit')*2))

    # reset the game data without drawing the gamefield
    def reset(self):
        self.score = 0
        self.field = [[0 for i in range(self.width)]
                      for j in range(self.height)]
        self.spawn('Init')
        self.spawn('Init')

    # choose a block and fill in number
    def spawn(self, state):
        if state == 'Init':  # if the state is Init 4 or 2 is generate, otherwise 2
            num = 4 if randrange(100) > 89 else 2
        else:
            num = 2
        # find two unfilled blocks
        j = randrange(self.width)
        i = randrange(self.height)
        while self.field[i][j] != 0:
            j = randrange(self.width)
            i = randrange(self.height)
        self.field[i][j] = num

    # draw the gamefield on the screen
    def draw(self):
        HelpString1 = '(W)up (S)down (A)left (D)right'
        HelpString2 = '(R)restart (Q)quit'

        # method of drawing the horizontal separator
        def draw_hor_separator():
            line = '+------'*self.width+'+'+os.linesep
            self.stdscr.addstr(line)

        # method of drawing the row of the gamefield
        def draw_row(row):
            line = ''.join('|{:^6}'.format(num) if num >
                           0 else '|      ' for num in row)+'|'+os.linesep
            self.stdscr.addstr(line)
            print("good")

        # implementation of drawing the gamefield
        self.stdscr.clear()
        self.stdscr.addstr('SCORE: {0}      HGHSCORE: {1}'.format(
            self.score, self.highscore)+os.linesep)

        for row in self.field:
            draw_hor_separator()
            draw_row(row)

        draw_hor_separator()
        self.stdscr.addstr(HelpString1+os.linesep)
        self.stdscr.addstr(HelpString2+os.linesep)

    # get the key from the user
    def getuserkey(self):
        ch = chr(self.stdscr.getch())
        while ch not in self.actiondict:
            ch = chr(self.stdscr.getch())
        return ch

    # have the game one step further, return the result of the game
    def step(self):
        def isWin():  # check if the player win
            for token in self.field:
                if self.winvalue in token:
                    return True
                else:
                    return False

        def isOver():  # check if the player lose
            for token in self.field:
                if 0 in token:
                    return False
            return True

        key = self.getuserkey()
        if self.actiondict[key] == 'up':
            self.move('up')
        elif self.actiondict[key] == 'down':
            self.move('down')
        elif self.actiondict[key] == 'left':
            self.move('left')
        elif self.actiondict[key] == 'right':
            self.move('right')
        elif self.actiondict[key] == 'restart':
            return 'Init'
        elif self.actiondict[key] == 'quit':
            return 'Exit'

        if isWin():
            return 'Win'
        elif isOver():
            return 'Gameover'
        else:
            self.spawn('Game')
            return 'Game'

    # implement transformation of the gamefield
    def move(self, direction):
        def merge():  # operation of moving the gamefield upward
            for i in range(0, self.width):
                for j in range(0, self.height-1):
                    for k in range(j+1, self.height):
                        if self.field[k][i] == 0:
                            pass
                        elif self.field[j][i] == self.field[k][i]:
                            self.field[j][i] = self.field[j][i]+self.field[k][i]
                            self.field[k][i] = 0
                            self.score = self.score+self.field[j][i]
                            self.highscore = self.score if self.score > self.highscore else self.highscore
                            break
                        else:
                            break
                for j in range(0, self.height):  # move all the blocks up in heap
                    if self.field[j][i] == 0:
                        for k in range(j, self.height):
                            if self.field[k][i] != 0:
                                self.field[j][i] = self.field[k][i]
                                self.field[k][i] = 0
                                break

        def convertupdown():  # switch the upside blocks and the downside blocks
            self.field.reverse()
            # for i in range(0,self.height>>1):
            #	tmp=self.field[self.height-1-i]
            #	self.field[self.height-1-i]=self.field[i]
            #	self.field[i]=tmp

        def transpose():  # transpose the matrix gamefield around its diagnal line
            self.field = [[token[i] for token in self.field]
                          for i in range(0, self.width)]
            self.height = self.height ^ self.width
            self.width = self.height ^ self.width
            self.height = self.height ^ self.width

        def invert():  # transpose the matrix around its counter diagnal line
            self.field.reverse()
            self.field = [[token[i] for token in self.field]
                          for i in range(self.width-1, -1, -1)]
            self.height = self.height ^ self.width
            self.width = self.height ^ self.width
            self.height = self.height ^ self.width
        # executing the movement strategy
        if direction == 'up':
            merge()
        elif direction == 'down':
            convertupdown()
            merge()
            convertupdown()
        elif direction == 'left':
            transpose()
            merge()
            transpose()
        elif direction == 'right':
            invert()
            merge()
            invert()

    # the measures taken up when the game is over(win or lose)
    def gameover(self, state):
        if state == 'Gameover':
            self.stdscr.addstr(
                os.linesep*2+'You have lost, press R to restart or Q to Exit')
        else:
            self.stdscr.addstr(
                os.linesep*2+'Congratulatons!! You have win, press R to restart or Q to Exit')
        ch = chr(self.stdscr.getch())
        while ch not in 'rRqQ':
            ch = chr(self.stdscr.getch())
        if ch in 'rR':
            return 'Restart'
        else:
            return 'Exit'

#-------------------------------------------#
# function name: nextstate(state,gamefield)
# the state swith machine
# initialization->gamesteps->win or lose
#-------------------------------------------#


def nextstate(state, gamefield):
    # procedure of state switch
    if state == 'Init' or state == 'Restart':
        gamefield.reset()
        gamefield.draw()
        return 'Game'
    elif state == 'Game':
        s = gamefield.step()
        gamefield.draw()
        return s
    elif state == 'Gameover' or state == 'Win':
        s = gamefield.gameover(state)
        return s


#-----------------------------------------------#
# the main script
#-----------------------------------------------#
# the scenario that the file is imported, can be extanded
if __name__ != '__main__':
    print'module 2048.py is imported'

# the scenario that the file is executed directly
else:
    def fun(stdscr):
        gamefield = GameField(stdscr)

        state = 'Init'
        while state != 'Exit':
            state = nextstate(state, gamefield)

    curses.wrapper(fun)
