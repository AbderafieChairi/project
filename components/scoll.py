import tkinter as tk
from tkinter import ttk

class ScrollableFrame(ttk.Frame):
    def __init__(self, container,T,currentFrame=None,demande=False,admin=False, *args, **kwargs):
        super().__init__(container, *args, **kwargs)
        self.T=T
        self.container=container
        if currentFrame!=None:
            self.currentFrame=currentFrame
        canvas = tk.Canvas(self)
        scrollbar = ttk.Scrollbar(self, orient="vertical", command=canvas.yview)
        self.scrollable_frame = ttk.Frame(canvas)

        self.scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(
                scrollregion=canvas.bbox("all")
            )
        )

        canvas.create_window((0, 0), window=self.scrollable_frame, anchor="nw")

        canvas.configure(yscrollcommand=scrollbar.set)

        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")
        for i in range(len(self.T)):
            for j in range(len(self.T[0])) :
                tk.Label(self.scrollable_frame,text=self.T[i][j],padx=15).grid(row=i+1, column=j)
        tk.Button(self.scrollable_frame,text="retour",bg="#AAB6C6",command=self.handle).grid(row=0,column=0)
    def handle(self):
        self.forget()
        self.currentFrame(self.container).pack(padx=150,pady=50)

    #decorators
    def dec(self,func,item):
        def f():
            return func(item)
        return f

