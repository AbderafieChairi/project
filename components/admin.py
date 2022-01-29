import tkinter as tk
from .form import FormFrame
from tkinter import ttk
from .var import *
# root = tk.Tk()
# imagine dragon
class AdminForm(FormFrame):


	def __init__(self,mainFrame, container,typ,name,T,proc, *args, **kwargs):
		self.btn=typ
		self.T=T
		self.title=typ+' '+name
		super().__init__(container, *args, **kwargs)
		self.mainFrame=mainFrame
		self.admin_handle=proc

	def handle(self):
		self.admin_handle(self.data)
		self.mainFrame.pack(padx=10,pady=10)
		self.forget()	

	def _pack(self):
		self.pack(padx=10,pady=10)
		self.mainFrame.forget()	

class Admin(ttk.Frame):	
	def __init__(self, container, *args, **kwargs):
		self.container=container
		super().__init__(container, *args, **kwargs)
		ajouter=AdminForm(self,self.master,typ="Ajouter",name=self.name,T=self.T,proc=self.dec(self.handle_ajoute))
		update=AdminForm(self,self.master,typ="Modifier",name=self.name,T=["id"]+self.T,proc=self.dec(self.handle_update))
		delete=AdminForm(self,self.master,typ="Supprimer",name=self.name,T=["id"],proc=self.dec(self.handle_delete))
		tk.Label(self,text="Gestion des "+self.name).pack(pady=5,padx=100)
		tk.Button(master=self,text="Ajouter     ",command=ajouter._pack).pack(pady=5)
		tk.Button(master=self,text="Modifier   ",command=update._pack).pack(pady=5)
		tk.Button(master=self,text="Supprimer",command=delete._pack).pack(pady=5)
		tk.Button(master=self,text="List",command=self.show_list,padx=20).pack(pady=5)
		tk.Button(master=self,text="Retour",command=self.retour,padx=12).pack(pady=5)

	def handle_ajoute(self,T):
		pass
	def handle_update(self,T):
		pass
	def handle_delete(self,T):
		pass
	def show_list(self):
		pass
	def retour(self):
		pass

	#@decorators
	def dec(self,f):
		def g():
			return f([self.data[i].get() for i in data])

		return g

# class User(Admin):	
# 	T=user_admin
# 	name="User"
# 	def __init__(self, container, *args, **kwargs):
# 		super().__init__(container, *args, **kwargs)
# 	def handle_ajoute(self,data):
# 		print([data[i].get() for i in data])


# User(root).pack()


# root.mainloop()