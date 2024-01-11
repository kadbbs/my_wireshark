import tkinter as tk

def start_capture():
    selected_interface = interface_var.get()
    feedback_label.config(text=f"开始捕获网络数据包，使用网卡：{selected_interface}")

# 创建主窗口
window = tk.Tk()
window.title("Wireshark GUI")

# 选择网卡
interface_frame = tk.Frame(window)
interface_frame.pack(pady=10)

interface_label = tk.Label(interface_frame, text="选择网卡:")
interface_label.pack(side=tk.LEFT)

interface_var = tk.StringVar()
interface_var.set("")

interface_option_menu = tk.OptionMenu(interface_frame, interface_var, "")
interface_option_menu.pack(side=tk.LEFT)

# 开始按钮
start_button = tk.Button(window, text="Start", command=start_capture)
start_button.pack(pady=10)

# 反馈消息的标签
feedback_label = tk.Label(window, text="")
feedback_label.pack(pady=10)

# 进入主事件循环
window.mainloop()

