import socket,framebuf,time,machine
from machine import I2C,Pin
from ssd1306 import SSD1306_I2C
import wifi

i2c = I2C(scl = Pin(4),sda = Pin(5))
display = SSD1306_I2C(128,64,i2c)
display.text('Wifi',0,0)
display.text('Connecting......',0,20)
display.show()

wifi.oldconnect()#连接WiFi

display.fill(0)
display.text('Server',0,0)
display.text('Connecting......',0,20)
display.show()


host ='172.21.74.50'
port =8888

s = socket.socket()
addr = (host,port)
s.connect(addr)#连接服务器
display.fill(0)
display.text('Server',0,0)
display.text('Connected!',0,20)
display.show()


i = 0

while True:
    data1 =s.recv(1024)
    data2=s.recv(1024)
    data=data1+data2
    if len(data) > 10:#其实这个要不要无所谓，没影响
        fbuf = framebuf.FrameBuffer(bytearray(data),128,64,framebuf.MONO_HLSB)#这个参数不能换
        display.fill(0)
        display.blit(fbuf,0,0)#居中19
        display.show()
        del data,data1,data2
