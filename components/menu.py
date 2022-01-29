from tkinter import ttk
import tkinter as tk


class MenuFrame(ttk.Frame):
	title="default form"
	T=["default field"]

	def __init__(self, container, *args, **kwargs):
		self.m=max([len(i) for i in self.T])
		self.data={}
		super().__init__(container, *args, **kwargs)
		tk.Label(self,text=self.title).grid(row=0, column=2)
		for i in range(len(self.T)):
			tk.Label(self,text="   ").grid(row=2*i+1, column=2)
			tk.Button(self,text=self.T[i],command=self.dec(eval(f"self.handle{i}")),padx=3*(self.m-len(self.T[i]))).grid(row=2*i+2, column=2)
	def handle0(self):
		print("hhhh")
	def handle1(self):
		pass
	def handle2(self):
		pass
	def handle3(self):
		pass
	def handle4(self):
		pass
	def handle5(self):
		pass
	#@decorators
	def dec(self,f):
		def g():
			self.forget()
			return f()
		return g









