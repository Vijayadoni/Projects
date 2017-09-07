import myunihelper
class main():
	'''***************************************************************************** 
	When main class is initialized,
	Gets all text files present in directory of .py file and prints the similarities 
	between the files.  
	*****************************************************************************'''
	def __init__(self):
		self.k = 5
		myunihelper.createLog(self.find_similarity(myunihelper.getFiles()),'Fingerprinting-Type1')
	'''***************************************************************************** 
	converts a file into a string without spaces or special characters
	*****************************************************************************'''
	def convert(self,file):
		f = open(file,'r')
		r = f.read().strip()
		r.replace('\n','').replace('\t','')
		for ch in "!@#$%^&*()[]{};:,./<>?\|`~-=+":
			if ch in r:
				r = r.replace(ch,' ') # replace each special character
		r = r.replace(' ','')
		return r
	'''***************************************************************************** 
	Splits a given string str into a list of words each of length k.
	*****************************************************************************'''
	def splitstrings(self,str):
		l=[]
		for i in range(len(str)-self.k+1):
			l.append(str[i:i+self.k])
		return l
	'''***************************************************************************** 
	Converts a list of words into a dictionary containing hash value as key and word
	as value,
				hash value = sum of ascii value(letter in word) * k^position 
	*****************************************************************************'''
	def convHash(self,l):
		f = [self.k**0,self.k**1,self.k**2,self.k**3,self.k**4]
		d = {}
		for i in l: d[(sum(list(map(lambda x,y: x*ord(y),f,i))))%143111] = i
		return d
	'''***************************************************************************** 
	find_similarities(list of files) returns a list of tuples containing file names
	and the similarity between them using:
							2 * matched fingerprints / (total fingerprints) * 100
	*****************************************************************************'''
	def find_similarity(self,files):
		m=[]
		for i in range(len(files)-1):
			for j in range(i+1,len(files)): 
				d1 = self.convHash(self.splitstrings(self.convert(files[i])))
				d2 = self.convHash(self.splitstrings(self.convert(files[j])))
				match = 0
				for key in d1.keys(): 
					if key in d2.keys(): match += 1 
				m.append((files[i],files[j],round(2*match/(len(d1)+len(d2))*100,1)))
		return m	
#Start Program! Print any exceptions
try:main()
except Exception as e: print(e)