import tkinter as tk
from tkinter import messagebox

# Function to display greeting
def greet():
    name = name_entry.get()
    if name:
        messagebox.showinfo("Greeting", f"Hello, {name}!")
    else:
        messagebox.showwarning("Input Error", "Please enter your name.")

# Create the main window
root = tk.Tk()
root.title("Greeting Application")
root.geometry("300x200")  # Width x Height

# Create a label
label = tk.Label(root, text="Enter your name:")
label.pack(pady=10)  # Add some vertical padding

# Create an entry box
name_entry = tk.Entry(root)
name_entry.pack(pady=10)

# Create a button
greet_button = tk.Button(root, text="Greet", command=greet)
greet_button.pack(pady=10)

# Run the application
root.mainloop()
