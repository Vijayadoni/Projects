import os.path,subprocess
from subprocess import STDOUT,PIPE
import sys
def execute(file):
    filename,ext = os.path.splitext(file)
    cmd = ['python', file]
    proc = subprocess.Popen(cmd, stdin=PIPE, stdout=PIPE, stderr=STDOUT)
    stdout,stderr = proc.communicate()
    return stdout
print('\nBag of words------------\n')
print(execute('BagOfWords.py').decode('UTF-8').replace('\r','').rstrip())
print('\n lcs------------\n')
print(execute('lcs.py').decode('UTF-8').replace('\r','').rstrip())
print('\nFingerprinting Type 1------------\n')
print(execute('fingerprint.py').decode('UTF-8').replace('\r','').rstrip())