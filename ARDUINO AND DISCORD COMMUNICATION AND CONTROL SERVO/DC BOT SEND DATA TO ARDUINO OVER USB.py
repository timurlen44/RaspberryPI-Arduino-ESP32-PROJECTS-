import discord
from discord.ext import commands
import serial
arduino = serial.Serial("COM8", '9600', timeout=2)

def send_to_arduino(data):
    data +='\n'
    arduino.write(data.encode('utf-8'))
    

Bot = commands.Bot(command_prefix ="!! ")

@Bot.event
async def on_ready():
    print("BOT HAZIR İŞLEME BAŞLIYABİLİRSİNİZ")
    
    
@Bot.command()    
async def SERVO_DONDUR(ctx, *args):
    data = args[0] + '\n'
    arduino.write(data.encode('utf-8'))
    print(args[0])
    
Bot.run('OTY1MjQ1MjMzNjM1OTIxOTMy.YlwYrQ.CGWbTAGFebpNXofD5fZglcXPRjE')