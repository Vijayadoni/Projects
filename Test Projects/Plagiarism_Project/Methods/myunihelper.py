import glob
import datetime
import inspect
#create log if printMatrix is called or if execution failed
def createLog(data,prog):
	file = open('log.txt','a+')
	file.write('\n\n**************************'+prog+'***************************\n\n')
	for i in data:
		file.write(i[0][12:-4]+' and '+i[1][12:-4]+' are '+str(i[2])+' % plagiarised!\n')
	file.write('\n'+str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')))
	printMatrix(data)
#return a list of .txt extension files 
def getFiles():
   	if len(glob.glob1('./Text_Files','*.txt')) < 6: return glob.glob('.\Text_Files\*.txt')
   	else: raise Exception('Too many files!!')
#print data into a matrix format
def printMatrix(data): 
	for i in data: print(i[0][12:-4],'and',i[1][12:-4],'are',str(i[2])+'% plagiarised!')