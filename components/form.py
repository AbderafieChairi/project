from tkinter import ttk
import tkinter as tk
from math import *
# root = tk.Tk()

# root.title('Listbox')


class FormFrame(ttk.Frame):
	title="default form"
	# data={}
	T=["default field"]
	btn="default btn"
	def __init__(self, container, *args, **kwargs):
		self.data={}
		super().__init__(container, *args, **kwargs)
		tk.Label(self,text=self.title).grid(row=0, column=2)
		for i in range(len(self.T)):
			tk.Label(self,text=self.T[i],padx=10).grid(row=2*i+1, column=1)
			self.data[self.T[i]]=tk.Entry(self)
			self.data[self.T[i]].grid(row=2*i+2,column=2,ipadx="50")
		tk.Label(self,text="   ").grid(row=2*(len(self.T))+1, column=2)
		tk.Button(self,text=self.btn,command=self.dec(self.handle),padx=10).grid(row=2*(len(self.T))+2, column=2)
	def handle(self):
		print("default button click")
	
	def dec(self,f):
		def g():
			return f([self.data[i].get() for i in self.data])

		return g

# FormFrame(root).pack()
# the good dector



# class Form(FormFrame):
# 	title="verification de l'admin"
# 	T=["mot de pass"]
# 	btn="Verifier"
# 	def handle(self):
# 		TT=[self.data[i].get() for i in self.data]
# 		print(TT[0]=="botato")
# 		# f=eval("lambda x:"+TT[0])
# 		# print(Newton())
	

# Form(root).pack(padx=60,pady=60)




# root.mainloop()

