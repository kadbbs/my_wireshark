import tkinter as tk
from tkinter import messagebox

def show_full_message(message):
    new_window = tk.Toplevel(window)
    new_window.title("完整消息")
    new_window.geometry("300x200")
    
    message_label = tk.Label(new_window, text=message)
    message_label.pack(pady=20)

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

# 展示消息
message_frame = tk.LabelFrame(window, text="消息")
message_frame.pack(padx=10, pady=10)

message_box = tk.Listbox(message_frame, height=10)
message_box.pack(fill=tk.BOTH, expand=True)

# 添加示例消息
messages = [
    "Message 1",
    "Message 2",
    "Message 3",
    "Message 4",
    "Message 5"
]

for message in messages:
    message_box.insert(tk.END, message)

# 点击事件
def on_message_select(event):
    selected_message = message_box.get(tk.ACTIVE)
    show_full_message(selected_message)

message_box.bind("<<ListboxSelect>>", on_message_select)

# 进入主事件循环
window.mainloop()

