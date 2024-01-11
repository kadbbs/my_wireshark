import tkinter as tk
from tkinter import messagebox

def show_full_message(message):
    messagebox.showinfo("Full Message", message)

def create_new_box(message):
    new_box = tk.LabelFrame(scrollable_frame, text="Message")
    new_box.pack(pady=5)

    box_label = tk.Label(new_box, text=message, cursor="hand2", fg="blue")
    box_label.pack(padx=10, pady=5)
    box_label.bind("<Button-1>", lambda event, text=message: show_full_message(text))

# 创建主窗口
window = tk.Tk()
window.title("GUI Example")

# 大框
scrollable_frame = tk.LabelFrame(window, text="Scrollable Frame")
scrollable_frame.pack(padx=10, pady=10)

scrollbar = tk.Scrollbar(scrollable_frame)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

box_canvas = tk.Canvas(scrollable_frame, yscrollcommand=scrollbar.set)
box_canvas.pack(fill=tk.BOTH, expand=True)

scrollbar.config(command=box_canvas.yview)

box_frame = tk.Frame(box_canvas)
box_canvas.create_window((0, 0), window=box_frame, anchor=tk.NW)

# 生成框并添加点击事件
messages = ["Message 1", "Message 2", "Message 3", "Message 4", "Message 5"]

for message in messages:
    create_new_box(message)

box_canvas.update_idletasks()  # 更新画布大小

# 绑定滚动事件
box_canvas.config(scrollregion=box_canvas.bbox("all"))

# 进入主事件循环
window.mainloop()

