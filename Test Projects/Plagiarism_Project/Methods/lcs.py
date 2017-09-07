import myunihelper
class main():
	'''***************************************************************************** 
	When main class is initialized,
	Gets all text files present in directory of .py file and prints the similarities 
	between the files.  
	*****************************************************************************'''
	def __init__(self):
		myunihelper.createLog(self.find_similarities(myunihelper.getFiles()),'LargestCommonSequence')
	'''***************************************************************************** 
	formatFile takes file name as arguement, and returns the list of all sentences in 
	the document.
		-> A sentence is any string which ends before a special character 
	*****************************************************************************'''
	def formatFile(self,file):
		l=[]
		l.append([file])
		f = open(file,'r')
		r = f.read().strip().lower()
		r.replace('\n',' ').replace('\t',' ')
		for ch in "!@#$%^&*()[]{};:,./<>?\|`~-=+":
			if ch in r:
				r = r.replace(ch,'@ ')
		r = r.split('@')
		l.append(r)
		return l
	'''***************************************************************************** 
	The actual lcs algorithm,
			->Takes two sentences (str1,str2)
			->returns the maximum possible common sequence
					For Example: sentence 1: I have a pen 
								 sentence 2: have a party
								 Here 'have a p' is the longest possible sequence!
	*****************************************************************************'''
	def lcs(self,str1,str2):
		max_lcs = []
		for j in range(len(str1)):	
			for i in range(len(str1)):
				if str1[j] == ' ' and str1[j:len(str1)-i] in str2 :
					max_lcs.append(len(str1[j:len(str1)-i].strip()))
					j += 1
					break
				elif str1[j] != ' ': break
			if len(max_lcs)>0 and max(max_lcs) > len(str1)/2-1:break 
		return max(max_lcs)
	'''***************************************************************************** 
	Find similarities between all files and return a list of tuple containing file 
	names and the similarity.
		-> calculates max possible lcs for a sentence with all other sentences of
		other doc.
	*****************************************************************************'''
	def find_similarities(self,files):
		m,l=[],[]
		for i in files: l.append(self.formatFile(i))
		for i in range(len(l)-1):
			for j in range(i + 1,len(l)):
				total_count,lcs_count = 0,0
				max_lcs = [0]
				for k in l[i][1]: total_count += len(k.strip())
				for k in l[j][1]: total_count +=len(k.strip())
				for k in l[i][1]:
					lcs_count += max(max_lcs) # store the max lcs in a particular file
					max_lcs = [0]
					for t in l[j][1]:
						max_lcs.append(self.lcs(' '+k,' '+t))
				lcs_count += max(max_lcs)
				m.append((l[i][0][0],l[j][0][0],round(((lcs_count*2)/total_count)*100,1)))
		return m	
#Start Program! Print any exceptions
try: main()
except Exception as e: print(e)