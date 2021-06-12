from datetime import datetime

def log(msg, args: list):
    trace = "[" + "][".join(args) + "]"
    now = datetime.now()
    time_str = now.strftime("[%H:%M:%S]")
    print(time_str + trace + " " + msg)