import tkinter as tk
from tkinter import messagebox
from tkinter.scrolledtext import ScrolledText

def create_new_box():
    new_box = tk.LabelFrame(scrollable_frame, text="New Box")
    new_box.pack(pady=5)

def submit_input():
    input_text = input_entry.get()
    if input_text:
        messagebox.showinfo("Input", f"Input: {input_text}")

# 创建主窗口
window = tk.Tk()
window.title("GUI Example")

# 选择框
select_frame = tk.Frame(window)
select_frame.pack(pady=10)

select_label = tk.Label(select_frame, text="Select:")
select_label.pack(side=tk.LEFT)

select_var = tk.StringVar()
select_var.set("Option 1")
select_option_menu = tk.OptionMenu(select_frame, select_var, "Option 1", "Option 2", "Option 3")
select_option_menu.pack(side=tk.LEFT)

# 输入按钮
input_frame = tk.Frame(window)
input_frame.pack(pady=10)

input_label = tk.Label(input_frame, text="Input:")
input_label.pack(side=tk.LEFT)

input_entry = tk.Entry(input_frame)
input_entry.pack(side=tk.LEFT)

submit_button = tk.Button(input_frame, text="Submit", command=submit_input)
submit_button.pack(side=tk.LEFT)

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

for i in range(10):
    box = tk.LabelFrame(box_frame, text=f"Box {i+1}")
    box.pack(pady=5)

# 生成新框按钮
create_button = tk.Button(window, text="Create New Box", command=create_new_box)
create_button.pack(pady=10)

# 进入主事件循环
window.mainloop()

