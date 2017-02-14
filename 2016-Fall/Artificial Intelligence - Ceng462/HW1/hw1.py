#from Queue import PriorityQueue
from copy import deepcopy
import heapq
import time
from math import sqrt
class PriorityQueue:
    def __init__(self):
        self._queue = []
        self._index = 0

    def put(self, item, priority):
        heapq.heappush(self._queue, (priority, self._index, item))
        self._index += 1

    def get(self):
        return heapq.heappop(self._queue)[2]
    def find(self,item):
        for i in range(0, len(self._queue)):
            if self._queue[i][2] == item:
                return item
        return 0
class Piece:
	def __init__(self, pGrid, piece_id):
		self.cur_row= 0
		self.cur_col= 0
		self.height = 0
		self.width = 0
		self.parent = pGrid
		self.piece_id = piece_id

	def __eq__(self, other):
		return self.cur_row == other.cur_row and self.cur_col == other.cur_col 
		

	def move(self,direction):
		valid = 1
		if direction == "left":
			if(self.cur_col-1 >=0):
				for i in range(0,self.height):
					if(self.parent.grid[self.cur_row+i][self.cur_col-1] != 0):
						valid = 0
				if valid:
					for i in range(0,self.height):
						self.parent.grid[self.cur_row+i][self.cur_col-1] = self.piece_id
						self.parent.grid[self.cur_row+i][self.cur_col+self.width-1] = 0
					self.cur_col -=1
			else:
				valid = 0
		elif direction == "right":
			if(self.cur_col + self.width < self.parent.col_count):
				for i in range(0,self.height):
					if(self.parent.grid[self.cur_row+i][self.cur_col+self.width] != 0):
						valid = 0
				if valid:
					for i in range(0,self.height):
						self.parent.grid[self.cur_row+i][self.cur_col+self.width] = self.piece_id
						self.parent.grid[self.cur_row+i][self.cur_col] = 0	
					self.cur_col += 1
			else:
				valid = 0		
		elif direction == "up":
			if(self.cur_row-1 >=0):
				for i in range(0,self.width):
					if(self.parent.grid[self.cur_row-1][self.cur_col+i] != 0):
						valid = 0
				if valid:
					for i in range(0,self.width):
						self.parent.grid[self.cur_row-1][self.cur_col+i] = self.piece_id
						self.parent.grid[self.cur_row+self.height-1][self.cur_col+i] = 0
					self.cur_row -=1
			else:
				valid = 0
		elif direction == "down":
			if(self.cur_row+self.height<self.parent.row_count):
				for i in range(0,self.width):
					if(self.parent.grid[self.cur_row+self.height][self.cur_col+i] != 0):
						valid = 0
				if valid:
					for i in range(0,self.width):
						self.parent.grid[self.cur_row+self.height][self.cur_col+i] = self.piece_id
						self.parent.grid[self.cur_row][self.cur_col+i] = 0
					self.cur_row +=1
			else:
				valid = 0
		return valid



class Grid:
	def __init__(self, row_count,col_count,piece_count):
		self.row_count = row_count
		self.col_count = col_count
		self.piece_count = piece_count
		self.grid = [[0 for i in range(0, col_count)] for i in range(0, row_count)]
		self.not_detected = [i for i in range(1,piece_count+1)]
		self.pieces = [Piece(self,i) for i in range(0,piece_count+1)]
	def displayGrid(self):
		for i in range (0,self.row_count):
			for j in range(0, self.col_count):
				print self.grid[i][j],
			else:
				print 

		print
		"""for pi in self.pieces:
				print "id " + str(pi.piece_id)
				print "col "+str(pi.cur_col)
				print "row "+str(pi.cur_row)
				print "width "+str(pi.width)
				print "height "+str(pi.height)"""

	def __eq__(self, other):
		for i in range(1,self.piece_count+1):
			if not(self.pieces[i] == other.pieces[i] ):
				return False
		return True	

	def detect_pieces(self):
		for i in range(0,self.row_count):
			for j in range (0,self.col_count):
				if self.grid[i][j] != 0 and (self.grid[i][j] in self.not_detected):
					k=j
					while k<self.col_count and self.grid[i][k] == self.grid[i][j]:
						k+=1
						#print k
					l=i
					while l<self.row_count and self.grid[l][j] == self.grid[i][j] :
						l+=1
					#print"hey"+ str(self.grid[i][j])
					#print len(self.pieces)
					self.pieces[self.grid[i][j]].cur_col = j
					self.pieces[self.grid[i][j]].cur_row = i
					self.pieces[self.grid[i][j]].width = k-j
					self.pieces[self.grid[i][j]].height = l-i	
					self.not_detected.remove(self.grid[i][j])				
class Node:
	def __init__(self,grid,f,g,parent, heuristic_mode):
		self.grid = grid
		self.h = self.heuristic(heuristic_mode, final_states[0])
		if parent == 0:
			self.g = 0
		else:
			self.g = 1 + parent.g
		self.f = self.h + self.g
		self.parent = parent
		self.children=[]
		self.heuristic_mode = heuristic_mode
	def update_cost(self):
		mini = 100000
		for state in final_states:
			temp = self.heuristic(heuristic_mode, state)
			if temp < mini:
				mini = temp
		self.h = mini
		if self.parent == 0:
			self.g = 1
		else:
			self.g = 1 + self.parent.g
		self.f = self.h + self.g

	def __eq__(self, other):
		if other == 0:
			return False
		for i in range(1,self.grid.piece_count+1):
			if not(self.grid.pieces[i] == other.grid.pieces[i] ):
				return False
		return True		

	def heuristic(self,heuristic_mode,state):
		h = 100000
		if heuristic_mode == 0:
			#manhattan distance
				temp = 0
				for i in range (1,self.grid.piece_count+1):
					temp += abs(state.pieces[i].cur_row - self.grid.pieces[i].cur_row) + abs(state.pieces[i].cur_col - self.grid.pieces[i].cur_col)
			#print str(temp) +"teeeeeeeeeeeeeempppp"	
		elif heuristic_mode == 1:
			#mine
				temp = 0
				for i in range (1,self.grid.piece_count+1):
					temp += sqrt((state.pieces[i].cur_row - self.grid.pieces[i].cur_row)**2 + (state.pieces[i].cur_col - self.grid.pieces[i].cur_col)**2)
					#if (state.pieces[i].cur_row != self.grid.pieces[i].cur_row) or (state.pieces[i].cur_col != self.grid.pieces[i].cur_col):
					#	temp += 1

		return temp

	def gen_heuristic(self):
		h = 100000

		if self.heuristic_mode == 0:
			#manhattan distance
				temp = 0
				for state in final_states:
					for i in range (1,self.grid.piece_count+1):
						temp += abs(state.pieces[i].cur_row - self.grid.pieces[i].cur_row) + abs(state.pieces[i].cur_col - self.grid.pieces[i].cur_col)
					if temp < h:
						h = temp
			#print str(temp) +"teeeeeeeeeeeeeempppp"	
		elif self.heuristic_mode == 1:
			#mine
				temp = 0
				for state in final_states:
					for i in range (1,self.grid.piece_count+1):
						temp += sqrt((state.pieces[i].cur_row - self.grid.pieces[i].cur_row)**2 + (state.pieces[i].cur_col - self.grid.pieces[i].cur_col)**2)
						#if (state.pieces[i].cur_row != self.grid.pieces[i].cur_row) or (state.pieces[i].cur_col != self.grid.pieces[i].cur_col):
						#	temp += 1
					if temp < h:
						h = temp

		return h

def solve(startNode, final_states):
	frontier = PriorityQueue()
	explored = []
	frontier.put(startNode,startNode.h)
	while 1:
		if (not frontier):
			return 0
		#print frontier.get().grid.displayGrid()

		temp_node = frontier.get()
		#print str(temp_node.f) + " fcost"
		#print str(temp_node.g) + " gcost"
		#print str(temp_node.h) + " hcost"
		#temp_node.grid.displayGrid()
		for state in final_states:
			if temp_node.grid == state:
				return temp_node

		is_explored = 0
		prev_node = deepcopy(temp_node)

		for k in range(0,len(explored)):
			if  (temp_node == explored[k] and temp_node.f < explored[k].f):
				is_explored =1
				break
	

		if  (is_explored == 0):
			explored.append(temp_node)
			for i in range (1,temp_node.grid.piece_count+1):
				for direction in ["left","right","up","down"]:
					valid = 0
					new_node = deepcopy(temp_node)
					valid = new_node.grid.pieces[i].move(direction)
					#print i, valid, direction, new_node.grid.pieces[i].cur_row, new_node.grid.pieces[i].cur_col
					if valid:
						if new_node in explored:
							continue
						elif (frontier.find(new_node) != 0):
							continue
						else:
							new_node.parent = temp_node
							new_node.update_cost()

							#if new_node.parent != 0:
							#	new_node.g = new_node.parent.g + 1
							#else:
							#	new_node.g = 1
							#new_node.h = new_node.gen_heuristic()
							#new_node.f = new_node.g + new_node.h


							frontier.put(new_node,new_node.f)


		else:
			continue

		




f = open('hw1.inp', 'r')
number_of_tasks = int(f.readline())
final_states=[]

templist=0
heuristic_mode = int(f.readline())
for i in range(0,number_of_tasks):
	final_states=[]
	templist =f.readline()
	templist = templist.split()
	row_count = int(templist[0]) 
	col_count = int(templist[1] )
	piece_count = int(templist[2])
	final_state_count = int(templist[3]) 
	while True:
   		line = f.readline()
   		if (not line):
   			break
   		elif('S' in line):
   			puzzle = Grid(row_count,col_count,piece_count)
   			final= Grid(row_count,col_count,piece_count)
   			for i in range (0,row_count):
   				templine = f.readline()
   				templine = templine.split()
   				for j in range (0,col_count):
   					puzzle.grid[i][j] = int(templine[j])
   			continue 
   		elif ('F' in line):
			for i in range (0,row_count):
				templine = f.readline()
				templine = templine.split()
				for j in range (0,col_count):
					final.grid[i][j] = int(templine[j])
			final_states.append(final)	
			continue
		elif (('0' in line) or ('1' in line)):
				heuristic_mode = int(line)
				break
	while True:
	    dummy = raw_input("")+'\n'
	    if dummy=='\n':
		break



	puzzle.detect_pieces()
	for state in final_states:
		state.detect_pieces()

	startNode = Node(puzzle,0,0,0,heuristic_mode)
	finalNode = solve(startNode, final_states)
	result = []

	while not(startNode.grid == finalNode.grid ):
		result.append(finalNode)
		finalNode = finalNode.parent
	result.append(deepcopy(startNode))
	i =len(result)-1
	while i>=0:
		result[i].grid.displayGrid()
		#print result[i].f
		#print result[i].g
		#print result[i].h
		i-=1


