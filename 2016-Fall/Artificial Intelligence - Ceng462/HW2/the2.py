from copy import deepcopy
#import time

def custom_split(line):
		templist = []
		opened = 0
		closed = 0
		lastcut = 0
		size = len(line)
		for i in range(0,size):
			if line[i] == '(':
				opened+=1
			elif (line[i] == ')'):
				closed+=1
			elif line[i] ==',' and closed == opened:
				templist.append(line[lastcut:i])
				lastcut = i+1
		if lastcut  < size:
			templist.append(line[lastcut:])
		return templist

class Literal :
	
	def __init__(self,line,parent):
		self.parent = parent
		self.elements = []
		self.isnegated = False
		self.type = 'x'
		self.name = "leblebi"
		templist = custom_split(line)

		for item in templist:
			size = len(item)
			if item[0] == '~':
				self.isnegated = True
				item = item[1:]				
			else:
				self.isnegated = False

			if item[0].isupper():
				self.type = 'c'
				self.name = item[0]
				if size>1 and item[1] == ',':
					self.parent.elements.append(Literal(item))			
			else:
				self.name = item[0]
				if size>1 and item[1] == '(':
					self.type = 'f'
					item = item[2:size-1]
					for piece in custom_split(item):
						self.elements.append(Literal(piece,self.elements))
				elif size>1 and item[1] == ',':
					self.type = 'v'
					item = item[2:]
					self.parent.elements.append(Literal(item,self.parent))
				else:
					self.type = 'v'
					self.name = item[0]
		return
	
	def __eq__(self, other):
		if self.name != other.name:
			return False
		if self.isnegated != other.isnegated:
			return False
		if self.type != other.type:
			return False
		size = len(self.elements)		
		if size != len(other.elements):
			return False
		else:	
			for i in range(0,size):
					if not (self.elements[i] == other.elements[i]):
						return False
					else :
						continue
			return True
	
	def reseq(self, other):
		if self.name != other.name:
			return False
		if self.isnegated == other.isnegated:
			return False
		if self.type != other.type:
			return False
		size = len(self.elements)
		if size != len(other.elements):
			return False
		else:
			for i in range(0,size):
					if not (self.elements[i]== other.elements[i]):
						return False
					else :
						continue
			return True
				
	def makestr(self):
		templist = ""
		templist = templist + self.name
		for item in self.elements:
			templist = templist + item.makestr()			
		return templist
	
	def printLiteral(self):
		resstr = ""
		if self.isnegated:
			resstr += '~'
		resstr += self.name
		if self.elements != []:
			resstr += '('		
		size = len(self.elements)
		for i in range (0,size):
			resstr += self.elements[i].printLiteral()
			if i+1<size:
				resstr +=','
		if self.elements != []:
			resstr +=')'
		return resstr

class Clause:
	
	def __init__(self,line):
		self.parent1 = None
		self.parent2 = None
		self.literal_array = []
		self.litnamear = line
		templist = custom_split(line)
		for item in templist:
			templiteral = Literal(item,self.literal_array)
			self.literal_array.append(templiteral)
		self.num_of_literals = len(self.literal_array)
	
	def __eq__(self, other):

		if self.num_of_literals !=other.num_of_literals:
			return False
		else:
			for i in range (0,self.num_of_literals):
				if not self.literal_array[i] in other.literal_array:
					return False		
			return True
	
	def printClause(self):
		resstr = ""
		for i in range (0,self.num_of_literals):
			resstr += self.literal_array[i].printLiteral()
			if i+1<self.num_of_literals:
				resstr += ','
		return resstr

def istautology(list1):
	todel = []
	size = len(list1)
	for i in range(0,size):
		for j in range(i,size):
			if i==j:
				continue
			else:
				if list1[i].reseq(list1[j]):
					todel.append(i)
					todel.append(j)
					i=size
					break
	if todel : 
		return True
	return False	

def eliminatesublit(literal1,literal2):
	size1 = len(literal1.elements)
	size2 = len(literal2.elements)
	if size1 == 0 or size2 == 0:
		res = unify([(literal1)],[(literal2)])
	if  literal1.name == literal2.name and literal1 == literal2:
		return True
	if literal1.name == literal2.name:
		if size1 == size2:
			if literal1.isnegated == literal2.isnegated:
				result = unify((literal1.elements),(literal2.elements))
				return result
			else:
				return False
		else:
			return False
	else:
		return False

def eliminatesub(clause1,clause2):
	size1 = len(clause1.literal_array)
	size2 = len(clause2.literal_array)
	flag = False
	trueforall=True
	issubset = True
	rule = ""
	for i in range (0,size1):
		literal1 = clause1.literal_array[i]
		name = literal1.name
		for j in range (0,size2):	
			literal2 = clause2.literal_array[j]
			#if  name in clause2.litnamear:
			result = eliminatesublit(literal1,literal2)

			if result == False:
				trueforall=False
				continue
			elif result == True:
				continue
			else:
				rule = rule + result
				flag = True
			#else: 
			#	continue
	if flag == False:
		return False #no subsumption
	elif trueforall == True :
		return True #equal, delete anyone
	elif flag == True and not rule == "":
		temp = deepcopy(clause1)
		temp.literal_array = applyuni(temp.literal_array,rule)
		if temp == clause1:
			return "first"
		elif temp == clause2:
			return "second"
		else:
			return False
			
def applyuni(t1,z1):
	#t1 is literal array
	#z1 is unification rules
	#print z1
	size1= len(t1)
	for i in range(0,size1):
		lit = t1[i]
		if len(lit.elements) == 0:
			if lit.name in z1 :
				index = z1.find(lit.name)
				if z1[index+1] == '/' and index+3<len(z1):
					if z1[index+3] == '(':
						tmpstr = ""
						k = index+2
						while k < len(z1)and k != ',':
							tmpstr += z1[k]
							k+=1
						t1[i] = Literal(tmpstr,None)
					else:
						lit.name = z1[index+2]
						if z1[index+2].isupper():
							lit.type = 'c'
						else:
							lit.type = 'v'
				else:
					continue
			else:
				continue			
		else:
			size2 = len(lit.elements)
			for j in range (0,size2):
				litj = lit.elements[j]
				if litj.type != 'f':
					if litj.name in z1 :
						index = z1.find(litj.name)
						if z1[index+1] == '/' and index+3<len(z1) :
							if z1[index+3] == '(':
								tmpstr = ""
								k = index+2
								while k < len(z1) and k != ',':
									tmpstr += z1[k]
									k+=1
								t1[i].elements[j] = Literal(tmpstr,None)
							else:
								litj.name = z1[index+2]
								if z1[index+2].isupper():
									litj.type = 'c'
								else:
									litj.type = 'v'
						else:
							continue
					else:
						continue
				else:
					applyuni(litj.elements,z1)			
	return t1

def unify(list1,list2):
	if list1 and list2:
		size1= len(list1)
		size2= len(list2)
		if size2 == 1 or size1 == 1:
			if size2 == 1:
				temp = list1
				list1 = list2
				list2 = temp
			equal = True
			for i in range (0,size1):
				if not list1[i]==list2[i]:
					equal = False
					break
			if equal and size1 == size2:
				return True	
			l1 = list1[0]
			l2 = list2[0]			
			if size1 == 1 and l1.type == 'v':
				if l1.name in l2.printLiteral():
					return False		
			if size1 == 1 and l1.type == 'f' and size2 == 1 and l2.type == 'f':
					if l1.name == l2.name:
						return unify(l1.elements, l2.elements)
					else:
						return False
			elif size1 == 1 and l1.type == 'f' and size2 == 1 and l2.type == 'v':
						return ","+l2.name+"/"+l1.printLiteral()+","

			elif size1 == 1 and l1.type == 'v' and size2 == 1 and l2.type == 'f':
						return ","+l1.name+"/"+l2.printLiteral()+","				
			
			if size1 == 1 and l1.type == 'v':
					return ","+l1.name+"/"+l2.name+","
			if size2 == 1 and l2.type == 'v':
					return ","+l2.name+"/"+l1.name+","			
			else :
				return False
		else:
			f1 = [list1[0]]
			t1 = list1[1:]
			f2 = [list2[0]]
			t2 = list2[1:]
			z1 = unify(f1,f2)
			if z1 == False :
				return False
			if z1 == True:
				z2 = unify(t1,t2)				
				if z2 == False :
					return False
				if z2 == True :
					return z1
				else:
					return z2						
			else:
				g1 = applyuni(deepcopy(t1),z1)
				g2 = applyuni(deepcopy(t2),z1)
				z2 = unifydeep(g1,g2)
				if z2 == False :
					return False
				if z2 == True :
					return z1
				else:
					return z1 + z2

def unifydeep(list1,list2):
	if list1 and list2:
		size1= len(list1)
		size2= len(list2)
		if size2 == 1 or size1 == 1:
			if size2 == 1:
				temp = list1
				list1 = list2
				list2 = temp
			equal = True
			for i in range (0,size1):
				if not list1[i]==list2[i]:
					equal = False
					break
			if equal and size1 == size2:
				return True	
			l1 = list1[0]
			l2 = list2[0]			
			if size1 == 1 and l1.type == 'v':
				if l1.name in l2.printLiteral():
					return False
			if size2 == 1 and l2.type == 'v':
					return ","+l2.name+"/"+l1.name+","		
			elif size1 == 1 and l1.type == 'f' and size2 == 1 and l2.type == 'f':
					if l1.name == l2.name:
						return unifydeep(l1.elements, l2.elements)
					else:
						return False
			elif size1 == 1 and l1.type == 'f' and size2 == 1 and l2.type == 'v':
						return ","+l2.name+"/"+l1.printLiteral()+","

			elif size1 == 1 and l1.type == 'v' and size2 == 1 and l2.type == 'f':
						return ","+l1.name+"/"+l2.printLiteral()+","				
			
			if size1 == 1 and l1.type == 'v':
					return ","+l1.name+"/"+l2.name+","			
			else :
				return False
		else:
			f1 = [list1[0]]
			t1 = list1[1:]
			f2 = [list2[0]]
			t2 = list2[1:]
			z1 = unifydeep(f1,f2)
			if z1 == False :
				return False
			if z1 == True:
				z2 = unifydeep(t1,t2)				
				if z2 == False :
					return False
				if z2 == True :
					return z1
				else:
					return z2						
			else:
				g1 = applyuni(t1,z1)
				g2 = applyuni(t2,z1)
				z2 = unifydeep(g1,g2)
				if z2 == False :
					return False
				if z2 == True :
					return z1
				else:
					return z1 + z2

def lit_resolve(literal1, literal2):
	size1 = len(literal1.elements)
	size2 = len(literal2.elements)
	if  size1 == 0 or size2 == 0:
		unify([(literal1)],[(literal2)])
	if literal1.name == literal2.name:
		if size1 == size2:
			if literal1.isnegated != literal2.isnegated:
				temp1 = (literal1.elements)
				temp2 =(literal2.elements)
				result = unify(temp1, temp2)
				return result
			else:
				return False
		else:
			return False
	else:
		return False

def eliminaterealdups(list1):
	todel = []
	size = len(list1)
	for i in range(0,size):
		for j in range(i,size):
			if i==j:
				continue
			else:
				if list1[i] ==list1[j]:
					todel.append(j)
	if todel : 
		todel = list(set(todel))
		todel.sort()
		for i in range(0,len(todel)):
			del list1[todel[i]-i]
	return list1	

def eliminatedups(list1):
	todel = []
	size = len(list1)
	for i in range(0,size):
		for j in range(i,size):
			if i==j:
				continue
			else:
				if list1[i].reseq(list1[j]):
					todel.append(i)
					todel.append(j)
	if todel : 
		del list1[todel[0]]
		del list1[todel[1]-1]
	return list1

def pl_resolve(clause1, clause2,resolvents):
	templist = []
	rule = ""
	flag = False
	tempclause = Clause("")
	for i in range(0,clause1.num_of_literals):
		name = clause1.literal_array[i].name
		for j in range(0,clause2.num_of_literals):
			if  name in clause2.litnamear:
				result = lit_resolve(clause1.literal_array[i], clause2.literal_array[j])
				if result == True :
					templist =  templist + clause1.literal_array + clause2.literal_array
					templist = eliminatedups(templist)
					if templist ==[]:
						return None
					tempclause.literal_array = templist		
					tempclause.parent1 = clause1
					tempclause.parent2 = clause2
					tempclause.num_of_literals = len(tempclause.literal_array)				
					tempclause.literal_array = eliminaterealdups(tempclause.literal_array)
					tempclause.num_of_literals = len(tempclause.literal_array)
					tempclause.litnamear = tempclause.printClause()
					if not istautology(tempclause.literal_array):
						if tempclause not in resolvents:
							resolvents.append(tempclause)	
							#print tempclause.printClause()
				elif result != False:
					rule = rule + result
					flag = True
			else:
				continue
	if flag:
		templist = eliminatedups(   applyuni(    deepcopy(clause1.literal_array) +  deepcopy(clause2.literal_array) ,rule))
		tempclause.literal_array = templist 
		if templist ==[]:
			return None		
		tempclause.parent1 = clause1
		tempclause.parent2 = clause2			
		tempclause.num_of_literals = len(tempclause.literal_array)		
		tempclause.literal_array = eliminaterealdups(tempclause.literal_array)
		tempclause.num_of_literals = len(tempclause.literal_array)
		tempclause.litnamear = tempclause.printClause()
		if not istautology(tempclause.literal_array):
			if tempclause not in resolvents:
				resolvents.append(tempclause)	
				#print tempclause.printClause()
				return True
		return True
	else:
		return flag

def resolve(b_set,g_set):
	new = []
	resolvents = []
	clauses = b_set+g_set
	size2 = len(b_set)
	size1 = len(g_set)
	while 1:
		size3 = len (clauses)
		#print size3
		for i in range(size2,size3):
			ar1 = clauses[i]
			for j in range(0,size3):
				if i == j:
					continue
				else:
					ar2 = clauses[j]
					if ar1 and ar2:
						#print "to resolve clauses"
						#print ar1.printClause()
						#print ar2.printClause()
						result = pl_resolve(ar1, ar2,resolvents)
					if result == None:
						#print size3 + len(resolvents)
						return (ar1,ar2)
		del_list=[]
		size_resolvents=len(resolvents)
		for m in range(0,size_resolvents):
			for n in range(m+1,size_resolvents):
				if resolvents[m].num_of_literals == 1 and resolvents[m].literal_array[0] in resolvents[n].literal_array:
					del_list.append(n)
				else:
					res = eliminatesub(resolvents[m], resolvents[n])
					if res == False:
						continue
					elif res == True:
						del_list.append(n)
					elif res == "first":
						del_list.append(m)
						break
					elif res == "second":
						del_list.append(n)
		del_list = list(set(del_list))
		del_list.sort()
		for m in range(0,len(del_list)):
			del resolvents[del_list[m]-m]	

		for item in resolvents:
			if item not in new:
				new.append(item)							

		subset = True
		for item in new:
			if item not in clauses:
				subset = False
		if subset :
			fr.write( "no\n")
			return (False,False)
		for item in new:
			if item not in clauses:
				clauses.append(item)

def printparents(clause,printlist):

	str1 = ""
	str2 = ""
	if clause.parent1:
		str1 = clause.parent1.printClause()
		str2 = clause.parent2.printClause()
		str3 = clause.printClause()
		printlist.append( str1 + '$' + str2 + '$' + str3 )	
		printparents(clause.parent1,printlist)
		printparents(clause.parent2,printlist)		

#start_time = time.time()
f = open('hard.txt', 'r')
fr = open('output.txt', 'w')
number_of_tasks = int(f.readline())
templist=0

for i in range(0,number_of_tasks):
	b_set=[]
	g_set=[]
	templist =f.readline()
	templist = templist.split()

	n = int(templist[0]) 
	m = int(templist[1] )

	for j in range(2,n+1):
		clause_line = f.readline()
		clause_line = ''.join(clause_line.split())
		temp_clause = Clause(clause_line)
		b_set.append(temp_clause)

	for j in range(n+2,n+2+m+1):
		clause_line = f.readline()
		clause_line = ''.join(clause_line.split())
		temp_clause = Clause(clause_line)
		g_set.append(temp_clause)

	clauses = b_set + g_set
	(last1,last2) =	resolve(b_set,g_set)

	if last1:
		printlist = []
		printparents(last1,printlist)
		printparents(last2,printlist)

		fr.write( "yes\n")
		size = len(printlist)
		i = size-1
		while i>0:
			fr.write( printlist[i])
			fr.write('\n')
			i -= 1
		fr.write( printlist[0])
		fr.write('\n')
		str1 = last1.printClause()
		str2 = last2.printClause()	
		str3 = "empty_clause"
		fr.write( str1 + '$' + str2 + '$' + str3)
		fr.write('\n')
fr.close()

#elapsed_time = time.time() - start_time
#print elapsed_time
