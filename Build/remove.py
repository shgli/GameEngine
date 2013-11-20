#!/usr/bin/env python
import os
import sys
import subprocess
import shutil
exclude = ['build.py','remove.py','.svn']
files = os.listdir('.')
for f in files:
    if f not in exclude:
        if os.path.isfile(f):
            os.remove(f)
        else:
            shutil.rmtree(f)
            
           
        
