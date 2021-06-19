# esp32 wifi 投屏到oled显示
![输入图片说明](https://images.gitee.com/uploads/images/2021/0618/220421_c973b67e_8230134.jpeg "DEF36BFE50827F5CBBBB3FA28807F911.jpg")
#### 介绍
有arduino 和microPython两个版本，esp8266和esp32均支持，wifi无线投屏

B站：super大大怪i

oled显示助手链接：
复制这段内容后打开百度网盘App，操作更方便哦。 
链接:https://pan.baidu.com/s/1vYzb4HZ_ok3S7kn4yLdSwQ 
提取码:m1ys

关于软件，大家可以提出意见或想法，我会优化
后续再写简介····


#### 软件架构
软件架构说明


#### 安装教程

1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明
![输入图片说明](https://images.gitee.com/uploads/images/2021/0619/111937_b159057d_8230134.png "J@019IC`NFC2@9SKC~M$RPS.png")

使用该软件之前，你需要修改程序里wifi信息，ip填写上位机打开服务端后显示的地址，端口固定8888

![修改wifi信息](https://images.gitee.com/uploads/images/2021/0619/113031_5a920c86_8230134.png "4LNB1UOKY$R8_L1VIG~7}6H.png")

让esp32连接到同一个局域网中（同一路由器或电脑热点），连接成功后，OLED会显示连接成功

![wifi连接](https://images.gitee.com/uploads/images/2021/0619/113516_f13c384a_8230134.png "ML~C~G)CB[TH(IZ{W~Y`TJ6.png")

![服务端连接成功](https://images.gitee.com/uploads/images/2021/0619/113239_73ba6e47_8230134.png "OUHT[)UOZ4_`{Z]LZKNUDZI.png")

服务端连接成功后，就可以投屏啦，自由的发送图片和视频！


#### 问题发现

由于用的是i2c协议，开始信号，应答信号，数据传输等，全在一根线上，有系统开销，速度慢是很正常的，我找到他们之间的区别。

IIC总线速度为从0Hz到3.4MHz。它没有SPI 那样快，但对于系统管理器件如温度传感器来说则非常理想。IIC 存在系统开销，这些开销包括起始位/停止位、确认位和从地址位，但它因此拥有流控机制。

SPI 时钟速度很快，范围可从几兆赫兹到几十兆赫兹，且没有系统开销。SPI 在系统管理方面的缺点是缺乏流控机制，无论主器件还是从器件均不对消息进行确认，主器件无法知道从器件是否繁忙。

esp32 SPI最高速度可以设置为80MHz，对于彩屏数据传输非常快，有兴趣的朋友可以去试试

esp8266 和esp32 使用 arduino 版本的程序最大帧速对比

![输入图片说明](https://images.gitee.com/uploads/images/2021/0619/115001_59fe4664_8230134.png ")U4F0E25)3NCDXZ7X)6{YAS.png")

![输入图片说明](https://images.gitee.com/uploads/images/2021/0619/115019_4b85d57c_8230134.png "7$4)VG0W0Y0Y%1E3V]C)90C.png")

从准备接受数据到刷新图片结束耗费的时间，称为显示一张图片所需要的时间，esp32大概40ms刷新完一张图片，也就是说1s=1000ms能刷新25张图片，这也直接得出esp32支持该IIC协议OLED的最大帧率为25帧Fps/s,由于我没有SPI接口的OLED，本次没有做对比，估计肯定是SPI速度翻倍甚至更多，大家感兴趣可以试试。

另外，电脑的图片数据字节排列顺序一般是 逐行式-由高到底排列，而u8g2.drawXBMP()函数要求的顺序是，逐行式-由底到高排列，这个问题我没发现之前困扰了我一下午，发过去的图片和视频都是花的，我以为是u8g2库有问题，乱码，后面经过显示多张图片发现，黑白顺序有所颠倒，才想到图片的取模方式是否有问题，所以编写了个字节反转函数byte_reverse()得以解决




#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
