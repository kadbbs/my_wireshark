import tkinter as tk
from tkinter import messagebox
import psutil

def start_capture():
    selected_interface = interface_var.get()
    messagebox.showinfo("提示", f"开始捕获网络数据包，使用网卡：{selected_interface}")

# 创建主窗口
window = tk.Tk()
window.title("Wireshark GUI")

# 获取网卡列表
available_interfaces = psutil.net_if_addrs()
interface_names = list(available_interfaces.keys())

# 选择网卡
interface_frame = tk.Frame(window)
interface_frame.pack(pady=10)

interface_label = tk.Label(interface_frame, text="选择网卡:")
interface_label.pack(side=tk.LEFT)

interface_var = tk.StringVar()
interface_var.set(interface_names[0])
interface_option_menu = tk.OptionMenu(interface_frame, interface_var, *interface_names)
interface_option_menu.pack(side=tk.LEFT)

# 开始按钮
start_button = tk.Button(window, text="Start", command=start_capture)
start_button.pack(pady=10)

# 进入主事件循环
window.mainloop()

