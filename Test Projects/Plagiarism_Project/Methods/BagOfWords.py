import myunihelper
class main():
	'''***************************************************************************** 
	When main class is initialized,
	Gets all text files present in directory of .py file and prints the similarities 
	between the files.  
	*****************************************************************************'''
	def __init__(self):
		myunihelper.createLog(self.find_similarities(myunihelper.getFiles()),'Bag of Words')		
	'''***************************************************************************** 
	The actual bag of words algorithm,
		->Takes two dictionaries as input,
		->calculates the dot product between them,
		->calculates the distance between them
	returns the similarity (dot product/distance^1/2)*100
	*****************************************************************************'''
	def bag_of_words(self,d1,d2):
		dot_product,k = 0,[]
		for key in d1.keys():
			if key in d2.keys(): dot_product += d1[key]*d2[key]
		distance = 1
		for i in [d1,d2]: distance = distance * sum(value**2 for value in i.values())
		return round(dot_product/(distance**(1/2))*100,1)
	'''***************************************************************************** 
	This function creates a dictionary from a given file:
		-> removes all special characters
		-> creates a list of words
		-> calculates the frequency of words and stores in dictionary
	returns the dictionary.
	*****************************************************************************'''
	def createDictionary(self,file):
		f = open(file,'r')
		d = {}
		for line in f:
			l = line.lower().replace('\n','').strip(' ')
			for ch in "!@#$%^&*()[]{};:,./<>?\|`~-=+":
			   if ch in l:
			      l = l.replace(ch,'')
			l = l.split(' ')
			for j in l: d[j] = d[j] + 1 if j in d.keys() else 1
		return d
	'''***************************************************************************** 
	find_similarities(list of files) returns a list of tuples containing file names
	and the similarity between them using:
									bag_of_words(dictionary 1 , dictionary 2)
	*****************************************************************************'''
	def find_similarities(self,files):
		m,d_list = [],{}
		for file in files: d_list[file] = self.createDictionary(file)
		l = [i for i in d_list.keys()]
		for i in range(len(l)-1):
			for j in range(i+1,len(l)):
				m.append((l[i],l[j],self.bag_of_words(d_list[l[i]],d_list[l[j]])))
		return m
#Start Program! Print any exceptions
try: main()
except Exception as e: print(e)