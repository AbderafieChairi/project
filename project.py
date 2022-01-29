from components import *

#-----------------------------------Menu---------------------------------------#
#------------------------Main Menu------------------------------#
class Main_menu(MenuFrame):
	T,title=main_menu
	handle0=lambda self:	chambre.Liste(Main_menu)
	handle1=lambda self:	service.Liste(Main_menu)
	handle2=lambda self:	LoginForm(root).pack(padx=80,pady=60)
	handle3=lambda self:	signup(root).pack(padx=50,pady=50)

#------------------------User Menu------------------------------#
class User_menu(MenuFrame):
	T,title=user_menu
	def __init__(self, container,user=None, *args, **kwargs):
		print(user)
		self.user=user
		super().__init__(container, *args, **kwargs)
	handle0=lambda self:	chambre.Liste(User_menu)
	handle1=lambda self:	service.Liste(User_menu)
	handle2=lambda self:	AjouteChambreForm(root,self.user).pack(padx=80,pady=60)
	handle3=lambda self:	AjouteServiceForm(root,self.user).pack(padx=50,pady=50)
	handle4=lambda self:	Main_menu(root).pack(padx=150,pady=50)

#------------------------Admin menu-------------------------------#
class Admin_menu(MenuFrame):
	T,title=admin_menu
	handle0=lambda self:	User_(root).pack(padx=80,pady=60)
	handle1=lambda self:	Chambre(root).pack(padx=80,pady=60)
	handle2=lambda self:	Service(root).pack(padx=80,pady=60)
	handle3=lambda self:	Main_menu(root).pack(padx=150,pady=50)

#----------------------------------Forms-----------------------------------------#
#------------------------Login Forms------------------------------#
class LoginForm(FormFrame):
	user_id=7
	T,title,btn=login_user
	def __init__(self, container, *args, **kwargs):
		super().__init__(container, *args, **kwargs)

	def handle(self,T):
		user_id=cmd(f"client -c {T[0]} {T[1]}",value=True)
		if int(user_id)==0:
			self.forget()
			Main_menu(root).pack(padx=150,pady=50)
		elif int(user_id)==1:
			self.forget()
			Admin_menu(root).pack(padx=150,pady=50)
		else:
			self.forget()
			User_menu(root,user=user_id).pack(padx=150,pady=50)

#------------------------Ajoute chambre Forms-----------------------#
class AjouteChambreForm(FormFrame):
	T,title,btn=chambre_user
	def __init__(self, container,user, *args, **kwargs):
		self.user=user
		super().__init__(container, *args, **kwargs)
	def handle(self,T):
		a=cmd(f"reservation -a {T[0]} {self.user} {T[1]} {T[2]} {T[3]} {T[4]} {T[5]} {T[6]}",value=True)
		self.forget()
		User_menu(root).pack(padx=80,pady=60)
		messagebox.showinfo("billets",a)

#------------------------Ajoute Service Forms-----------------------#
class AjouteServiceForm(FormFrame):
	T,title,btn=Service_user
	def __init__(self, container,user, *args, **kwargs):
		self.user=user
		super().__init__(container, *args, **kwargs)
	def handle(self,T):
		a=cmd(f"Demande -a {T[0]} {self.user} {T[1]} {T[2]} {T[3]} {T[4]} {T[5]} {T[6]}",value=True)
		self.forget()
		User_menu(root).pack(padx=80,pady=60)
		messagebox.showinfo("billets",a)

#-----------------------Signup Forms--------------------------------#
class signup(FormFrame):
	T,title,btn=user_admin
	def handle(self,T):
		cmd(f"Client -a {T[0]} {T[1]} {T[2]} {T[3]}")
		self.forget()
		Main_menu(root).pack(padx=150,pady=50)

#-----------------------------------Lists-------------------------------------------------#
#------------------------Liste des chambres--------------------------#
class chambre(ScrollableFrame):
	Liste=lambda currentFrame: chambre(root,[["Numero :","price :"]]+cmd(f"reservation -f",stdout=True),currentFrame).pack()  

#------------------------Liste des Services--------------------------#
class service(ScrollableFrame):
	Liste=lambda currentFrame: service(root,[["Nom :","Price :"]]+cmd(f"Service -s",stdout=True),currentFrame).pack()

#------------------------Liste des utilisatuers----------------------#
class user(ScrollableFrame):
	Liste=lambda currentFrame: user(root,[["id","Nom","Adress","Email"]]+cmd(f"Client -s",stdout=True),currentFrame).pack()

#-----------------------------------Admin section------------------------------------------#
#------------------------Gestion des utilisateur---------------------#
class User_(Admin):	
	T=user_ad
	name="utisateurs"
	handle_ajoute=lambda self,T:	cmd(f"Client -a {T[0]} {T[1]} {T[2]} {T[3]}")	
	handle_update=lambda self,T:	cmd(f"Client -u {T[0]} {T[1]} {T[2]} {T[3]} {T[4]}")
	handle_delete=lambda self,T:	cmd(f"Client -d {T[0]}")
	def retour(self):
		self.forget()
		Admin_menu(root).pack(padx=80,pady=60)
	def show_list(self):
		self.forget()
		print("list user")
		user.Liste(User_)

#------------------------Gestion des Chambres-------------------------#
class Chambre(Admin):	
	T=chambre_admin
	name="Chambres"
	handle_ajoute=lambda self,T:	cmd(f"Chambre -a {T[0]} {T[1]}")	
	handle_update=lambda self,T:	cmd(f"Chambre -u {T[0]} {T[1]} {T[2]}")
	handle_delete=lambda self,T:	cmd(f"Chambre -d {T[0]}")
	def retour(self):
		self.forget()
		Admin_menu(root).pack(padx=80,pady=60)
	def show_list(self):
		self.forget()
		chambre.Liste(Chambre)

#------------------------Gestion des services-------------------------#
class Service(Admin):	
	T=service_admin
	name="services"
	handle_ajoute=lambda self,T:	cmd(f"Service -a {T[0]} {T[1]}")	
	handle_update=lambda self,T:	cmd(f"Service -u {T[0]} {T[1]} {T[2]}")
	handle_delete=lambda self,T:	cmd(f"Service -d {T[0]}")
	def retour(self):
		self.forget()
		Admin_menu(root).pack(padx=80,pady=60)
	def show_list(self):
		self.forget()
		service.Liste(Service)

Main_menu(root).pack(padx=150,pady=50)

root.mainloop()