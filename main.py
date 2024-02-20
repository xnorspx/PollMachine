import serial.tools.list_ports
import serial
import rich.console
from rich.table import Table
from rich.live import Live
import winsound
import threading

"""
Initiate serial connection
"""
terminal = rich.console.Console()

avail_serial_ports = serial.tools.list_ports.comports()
if len(avail_serial_ports) == 1:
    serial_port = avail_serial_ports[0].name
else:
    # Ask for the desired serial port
    terminal.print("The following are the available serial ports:", style="cyan")
    for item in avail_serial_ports:
        terminal.print(item.name, style="green")
    terminal.print("Please input the serial port that you want to use: ", style="yellow", end="")
    serial_port = terminal.input()

serial_obj = serial.Serial(serial_port, baudrate=115200)
terminal.clear()

"""
Table
"""
global beep
beep = False


def generate_result(init: bool = False):
    global beep
    if init:
        return Table()
    # Fetch update
    text = serial_obj.readline().decode("utf-8")
    text = text.replace("\r\n", "")
    status = text.split("|")
    # Init table
    result = Table(expand=True, style="cyan", show_lines=True, show_footer=True)
    result.add_column("Button", footer="Raw", footer_style="magenta")
    result.add_column("Time Delta(Unit: ms)", footer=text, footer_style="magenta")
    # Data
    status = {
        "start": int(status[0]),
        "1": int(status[1]),
        "2": int(status[2]),
        "3": int(status[3]),
        "4": int(status[4]),
        "5": int(status[5]),
    }
    # Generate table
    status_values = list(status.values())
    status_values.pop(0)
    status_values.sort()
    # # Remove not pressed
    while 0 in status_values:
        status_values.remove(0)
    # # Handle reset
    if len(status_values) == 0:
        beep = False
        return Table()
    # # Fetch initial time
    base = int(status_values[0])
    # # Add data to table
    for items in status_values:
        result.add_row(
            list(status.keys())[list(status.values()).index(items)], str(items - base)
        )
    # Beep
    if (len(status_values) >= 1) and not beep:
        winsound.Beep(2500, 1000)
        beep = True
    return result


with Live(generate_result(init=True), console=terminal) as live:
    while True:
        live.update(generate_result())
