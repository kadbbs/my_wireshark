import tkinter as tk
from tkinter.scrolledtext import ScrolledText
from tkinter import messagebox

# 选择网卡
def select_interface():
    selected_interface = interface_var.get()
    messagebox.showinfo("选中的网卡", selected_interface)

# 展示消息
def show_details(message):
    messagebox.showinfo("完整消息", message)

# 创建主窗口
window = tk.Tk()
window.title("Wireshark GUI")

# 选择网卡
interface_frame = tk.Frame(window)
interface_frame.pack(pady=10)

interface_label = tk.Label(interface_frame, text="选择网卡:")
interface_label.pack(side=tk.LEFT)

interface_var = tk.StringVar()
interface_var.set("eth0")
interface_option_menu = tk.OptionMenu(interface_frame, interface_var, "eth0", "eth1", "wlan0", "wlan1")
interface_option_menu.pack(side=tk.LEFT)

select_button = tk.Button(interface_frame, text="选择", command=select_interface)
select_button.pack(side=tk.LEFT)

# 消息展示区
message_frame = tk.LabelFrame(window, text="消息")
message_frame.pack(padx=10, pady=10)

message_box = ScrolledText(message_frame, height=10)
message_box.pack(fill=tk.BOTH, expand=True)

# 添加一些示例消息
messages = [
    "Message 1",
    "Message 2",
    "Message 3",
    "Message 4",
    "Message 5"
]

for message in messages:
    message_box.insert(tk.END, f"{message}\n")

# 绑定点击事件
message_box.bind("<Double-Button-1>", lambda event: show_details(message_box.get(tk.ACTIVE, tk.END)))

# 进入主事件循环
window.mainloop()

