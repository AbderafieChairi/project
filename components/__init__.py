from .admin import Admin,AdminForm
from .var import *
from .scoll import ScrollableFrame
from .form import FormFrame
from .menu import MenuFrame

import tkinter as tk
from tkinter import ttk,messagebox
import subprocess
root = tk.Tk()
root.title("Gestion de l'hotel")

def cmd(a,stdout=False,value=False):
	sub = subprocess.Popen(a, shell=True, stdout=subprocess.PIPE)
	if stdout:
		a=sub.stdout.read().decode('utf8').strip()
		return [i.split("\t") for i in a.split("\n")]
	if value:
		return sub.stdout.read().decode('utf8').strip()
