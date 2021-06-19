// author:super大大怪
// datetime:2021-6-18-19:00
// software: oled_Project_Screen
// 
#include<U8g2lib.h>
#include<U8x8lib.h>
#include<Wire.h>
#include <WiFi.h>//esp8266用这个库#include <ESP8266WiFi.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);//构建u8g2

uint8_t buff[1024]= {}; ////定义缓冲区 128 * 64 / 8 = 1024
const char* ssid     = "nova 6"; //填写你的wifi名字
const char* password = "123456789"; //填写你的wifi密码
const int httpPort = 8888; //设置上位机端口
char* IP = "192.168.43.133"; //上位机IP
WiFiClient client; //初始化一个客户端对象
//正常图片像素点是逐行式、高位在前，而u8g2.drawXBMP()的bmp格式是低位在前，所以需要将字节反转。
uint8_t byte_reverse(uint8_t* buff);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  u8g2.begin();
  WiFi.begin(ssid, password); //连接wifi
  delay(1000); //等待1秒
  while (WiFi.status() != WL_CONNECTED) {//判断wifi是否连接成功
      delay(1000); //每500毫秒检测一次状态
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawStr(0, 32, "Connect to wifi....");
      } while (u8g2.nextPage());
   
  }
  if (WiFi.status() == WL_CONNECTED) //判断如果wifi连接成功
  {
    Serial.println("wifi is connected!");//串口打印wifi连接信息
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    do {
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(0, 32, "Connect to service");
    } while (u8g2.nextPage());
    if (client.connect(IP, httpPort)) //连接到上位机
    {
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawStr(0, 32, "Service is connected!");
        u8g2.drawStr(0, 50, "Please start send!");
      } while (u8g2.nextPage());
    }
    else
    {
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.drawStr(0, 0, "Faild:");
        u8g2.drawStr(0, 32, "Service not connected!");
      } while (u8g2.nextPage());

    }
  }
}

uint16_t read_count = 0; //读取buff的长度
float start_time, end_time, fps_time, fps = 0;
uint16_t frame_count = 0, last_count = 0; //帧数
void loop() {
  while (client.available()) {
    start_time = millis();
    read_count = client.read(buff, 1024); //向缓冲区读取数据
    byte_reverse(buff);//转换费时间，可考虑pc端处理
    if (read_count == 1024) {
      read_count = 0;
      frame_count++;//帧数计数
      u8g2.clearBuffer();             //清除缓冲区 清屏
      u8g2.drawXBMP(0, 0, 128, 64, buff); //在（坐标x, 坐标y, 图像宽度, 图像高度, 图像数组）绘制图像
      u8g2.sendBuffer();              // 发送到缓冲区 显示
      if (frame_count - last_count == 10) { //每10帧计算一次平均帧率
        fps = 1000 * 10 / (millis() - fps_time);
        last_count = frame_count;
        fps_time = millis();
      }
      end_time = millis(); //计算mcu刷新一张图片的时间，从而算出1s能刷新多少张图，即得出最大刷新率

      Serial.print("正在传输第"); Serial.print(frame_count); Serial.print("帧，帧率为：");
      Serial.print(fps, 2); Serial.print("Fps/s,该MCU支持最大帧率为："); Serial.print(1000 / (end_time - start_time), 2); Serial.println("Fps/s");
    }
  }
}
uint8_t byte_reverse(uint8_t* buff)//低位在前翻转为高位在前
{
  uint8_t c;
  for (int i = 0; i < 1024; i++)
  {
    if (buff[i] == 0xff || buff[i] == 0x00) //0xff 0x00 反转一样，过滤掉
      continue;
    else
    {
      c = buff[i];
      c  =  ( c  &   0x55  )  <<   1   |  ( c  &   0xAA  )  >>   1 ;
      c  =  ( c  &   0x33  )  <<   2   |  ( c  &   0xCC  )  >>   2 ;
      c  =  ( c  &   0x0F  )  <<   4   |  ( c  &   0xF0  )  >>   4 ;
      buff[i] = c;
    }
  }
}
