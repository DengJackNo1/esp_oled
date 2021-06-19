# esp32 wifi 投屏到oled显示
![输入图片说明](https://images.gitee.com/uploads/images/2021/0618/220421_c973b67e_8230134.jpeg "DEF36BFE50827F5CBBBB3FA28807F911.jpg")
#### 介绍
有arduino 和microPython两个版本，esp8266和esp32均支持，wifi无线投屏

B站：super大大怪i

oled显示助手v1.1链接：

    复制这段内容后打开百度网盘App，操作更方便哦。 
    链接:https://pan.baidu.com/s/1vYzb4HZ_ok3S7kn4yLdSwQ 
    提取码:m1ys
    
oled显示助手v1.2链接：请看版本更新说明

    链接：https://pan.baidu.com/s/12cyvd74OJ7UvAfkQ6g56_A 
    提取码：s56g 
    复制这段内容后打开百度网盘手机App，操作更方便哦

关于软件，大家可以提出意见或想法，我会优化


#### 软件架构
    esp32用的arduino

    oled显示助手由Python-tkinter编写  

#### 接线说明
    esp32 iic默认引脚（scl=22，sda=21）
    
    esp8266 iic默认引脚（scl=5，sda=4）

也可以在u8g2构建对象那里参数更改为其他引脚，但是建议使用硬件IIC，速度更快


#### 使用说明
![输入图片说明](https://images.gitee.com/uploads/images/2021/0619/111937_b159057d_8230134.png "J@019IC`NFC2@9SKC~M$RPS.png")

使用该软件之前，你需要修改程序里wifi信息，ip填写上位机打开服务端后显示的地址，端口固定8888

![修改wifi信息](https://images.gitee.com/uploads/images/2021/0619/113031_5a920c86_8230134.png "4LNB1UOKY$R8_L1VIG~7}6H.png")

让esp32连接到同一个局域网中（同一路由器或电脑热点），连接成功后，OLED会显示连接成功

![连接说明](https://images.gitee.com/uploads/images/2021/0619/140333_291e2a59_8230134.png "[`C`~4CZ04{T(~FG9VYC{8K.png")

![wifi连接](https://images.gitee.com/uploads/images/2021/0619/113516_f13c384a_8230134.png "ML~C~G)CB[TH(IZ{W~Y`TJ6.png")

![服务端连接成功](https://images.gitee.com/uploads/images/2021/0619/113239_73ba6e47_8230134.png "OUHT[)UOZ4_`{Z]LZKNUDZI.png")

服务端连接成功后，就可以投屏啦，自由的发送图片和视频！


oled显示助手的帧速度设置，计算方法为1/视频的帧率 如（1/30帧=0.034s，1/24帧=0.41),即可以达到原视频的帧率，如果你的mcu达不到每帧显示（microPython较慢，需要跳帧），你可以将取帧频率设置为2，就是间隔一帧发送一次（30张图发送15张），从而保证OELD帧数的提高，跳帧后你需要调高你的帧速设置（30帧的视频取帧频率为2，要保持30帧的流畅度，你需要将帧数设置为 1/15=0.066s）

定义：图像的二值化，就是将图像上的像素点的灰度值设置为0或255，也就是将整个图像呈现出明显的只有黑和白的视觉效果。

灰度值0：黑，灰度值255：白

一幅图像包括目标物体、背景还有噪声，要想从多值的数字图像中直接提取出目标物体，常用的方法就是设定一个阈值T，用T将图像的数据分成两部分：大于T的像素群和小于T的像素群。这是研究灰度变换的最特殊的方法，称为图像的二值化（Binarization）。

二值化的方法选择，其中numpy,OTSU(大律法),mean（均值），gauus（高斯），这些都是cv2里的自适应阈值的方法，同时我加入了自定义阈值设置，用户可以根据自己的需要，去调节黑白的对比度。



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
![取模不同对比](https://images.gitee.com/uploads/images/2021/0619/121235_be614fc8_8230134.png "002.png")

![输入图片说明](https://images.gitee.com/uploads/images/2021/0619/121141_3cedc100_8230134.jpeg "4A40F9E224B3C9D4E8101970D76DF9C3.jpg")


#### 关于投屏

本软件的投屏，是不断的截取屏幕的画面，经过cv2处理后发送给esp32显示，

方法用的是Python自带库 PIL 中的ImageGrab.grab()函数截取图片

截取图片的致命缺点就是速度，该方法截取1080-1920(全屏)的时间为50ms左右，也就是说，它的最大帧率只有20帧左右，所以我们投过去的画面都是跳帧后显示的，比如播放一个30帧的视频，而截屏频率为15帧/s，你就会发现画面非常卡顿，并不是像发送视频那样，每一帧都发送过去显示了的。

真正意义上的投屏，是将视频音频一起投过去，用DNLA、Miracast，这种专有的投屏协议，家里的电视机大多就是采用的DNLA协议。


#### OLED显示助手版本更新说明


![1.2](https://images.gitee.com/uploads/images/2021/0619/163056_ca022862_8230134.png "3AM0_}9JY4{$NG3_X%D$761.png")

今天b站有粉丝发现 OLED显示助手获取本地IP出错导致无法连接，原来是由于多个网络适配器造成上位机获取IP不准确，目前已经更新，获取的IP是正在上网的IP，完善了 同步帧速 功能，帧速=1/（视频帧率/取帧频率），如（1/（30/1）=0.033），同时将投屏截图频率速度提高了40%，可能esp8266 microPython使用会有花屏的情况，这是由于发送速度过快，而处理速度过慢造成的，如出现花屏。可继续使用1.1版本（如出现获取ip不正确，电脑设置打开网络适配器，除wifi以外，关闭其他的网络适配器）



