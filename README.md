# 一包辣条钱打造物联网开关

为什么想到这个标题呢?  因为我此刻正在吃辣条.....  大家应该每天面对的是`枯燥`的代码,而今天给大家带来一个不一样的东西,有血有肉有生命.



## 背景

一花一世界,一树一菩提.

在我们程序员的眼里, 一花一树, 大概是一台耐操的电脑加上一台丝滑的显示器, 如果两台显示器,那就是人生巅峰. 咳咳, 不错的,我的世界可以没有女朋友, 但是不能没有电脑,不能与它一起睡觉,我也要把它们摆在我的卧室,占为己有.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/girlfriend.jpg" alt="ESP-01.jpg"  />

心理上得到了满足,可是我生理上却饱受折磨.

每到了我睡觉的时候,显示器上得电源灯,音响得电源灯,路由器的状态灯, 更要命的是,我这台年久的音响,到了晚上,不知道是不是WIFI信号对它有干扰,中觉得它在发出嘟嘟嘟的电流声~~~

我当然可以在睡觉前把总开关关闭,早上起来打开电脑再把开关打开,可是咱们是程序员,这种重复的事情就应该交给程序来做!! 🐶

然后我想到的是米家的智能插座, 配合其他传感器,可以实现各种场景的自动控制. 可偏偏找不到这样的解决方案:



> `电脑开机-> 电源接通`
>
> `电脑关机-> 电源关闭`



找不到现成的解决方案,那我就只能自己做一套了,我在网上找到最廉价的物联网开关`ESP8266`+`物联网继电器`  ,一套不是998更不是99,而是9.9.为了避免广告嫌疑,我就不放链接了,大家自行某宝搜索🔍.

买来之后我的心里也是犯嘀咕的,我一个C#开发,能玩转这种单片机🤪? 然鹅... 我就用一个晚上的时间,真还就被我搞出来了,所以我觉得在座的各位大佬更是没问题.

## ESP8266 科普(硬件准备)📶

**ESP8266** 是一款国产成本极低且具有完整TCP/IP协议栈的Wi-Fi 物联网控制芯片, 并且深受西方创客的喜爱,生态比较丰富,某宝售价6元左右.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/ESP-01.jpg" alt="ESP-01.jpg" style="zoom:50%;" />

与其配套的是这么一个物联网继电器,某宝售价3-4元,把ESP8266插入对应的插孔两即可完美❤结合❤.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/继电器.jpg" alt="ESP-01.jpg" style="zoom:50%;" />



为了给ESP8266注入生命力,还需要购买这么一个ESP8266的烧录器,某宝8元.



<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/烧录器.png" alt="ESP-01.jpg" style="zoom:50%;" />



## 软件准备💽

1. Arduino IDE并安装好esp8266扩展

[Arduino IDE下载地址](https://www.arduino.cc/en/Main/Software) 
[ESP8266扩展包安装方法](https://www.arduino.cn/thread-76029-1-1.html)

2. 下载并安装blinker APP

我需要解释一下,为什么安装这个APP呢? blinker是一家做物联网解决方案的,作为爱好者的我们可以免费接入他们的平台,接入该平台后,我们不管是不是在家,都可以通过手机App控制,并可借助他们的SDK实现小爱同学的语音控制.

Android下载[点击下载](https://github.com/blinker-iot/app-release/releases)或 在android应用商店搜索“blinker”下载安装
IOS下载[点击下载](https://itunes.apple.com/cn/app/id1357907814)或 在app store中搜索“blinker”下载

3. 下载并安装blinker Arduino库

[点击下载](https://github.com/blinker-iot/blinker-library/archive/master.zip)
**Windows：**将下载好的blinker库解压到 **我的电脑>文档>Arduino>libraries** 文件夹中
**Mac OS：**将下载好的blinker库解压到 **文稿>Arduino>libraries** 文件夹中

解压之后目录结构像这样子.

![ESP-01.jpg](https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/blinker.png)

## 获取Secret Key🔑

1. 进入App，点击右上角的“+”号，然后选择 **添加设备**
2. 点击选择**Arduino** > **WiFi接入**
3. 选择要接入的服务商
4. 复制申请到的**Secret Key**

## DIY界面🎨

1. 在设备列表页，点击设备图标，进入设备控制面板

2. 按如下图添加button_on和button_off两个按钮

   <img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/button_on.jpg" alt="ESP-01.jpg" style="zoom:50%;" />

   <img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/button_off.jpg" alt="ESP-01.jpg" style="zoom:50%;" />

## 编译并上传示例程序📃

在我的GitHub下载为大家准备好的代码

[https://github.com/liuzhenyulive/ESP8266SmartSwitch(记得Star噢)](https://github.com/liuzhenyulive/ESP8266SmartSwitch)

双击`blinker_app_xiaoai.ino`用Arduino IDE打开, 输入刚刚在App中申请的Secret Key和你们家的WIFI名称和密码,建议2.4Gwifi, 5Gwifi我没有测试, 还有UDP的监听端口.

![ESP-01.jpg](https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/ESP8266GitHub.png)

```cpp
char auth[] = "2cf492755d68";  //设备key
char ssid[] = "2.4";  //路由器wifi ssid
char pswd[] = "12345678";  //路由器wifi 密码
unsigned int localUdpPort = 4210;  // 局域网中的UDP监听端口
```

编译并上传程序到esp8266开发板,如果提示缺少什么库,就在Arduino的项目->加载库->管理库 中下载缺失的库即可.

![ESP-01.jpg](https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/upload.png)

当看到如下提示,代表上传成功了.

![ESP-01.jpg](https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/finished.png)

此时不要把它从你的电脑上拔掉,登录你们家的路由器,查看该设置的IP地址.

![ESP-01.jpg](https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/iplookup.png)

打开在我GitHub仓库中为大家准备的UDP调试工具和串口调试工具,在UDP调试工具中输入该设备的IP和UDP监听端口,发送on,串口调试工具能接收到on,发送off能接收到off.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/debugtool.png" alt="ESP-01.jpg" style="zoom:50%;" />

同时,我们打开点灯blinker的app,如果你幸运的话它应该已经上线了,在app中点击on或off, 串口调试工具有对应的响应输出.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/app1.jpg" alt="ESP-01.jpg" style="zoom:50%;" />

## 通电⚡

最后也是最🤑躁动人心🤑的一步,给继电器接上5V的供电,拿一根没用的USB线剪开,一般红线是正极,负极请自行尝试,然后把你要控制的设备的火线(红色)**`断电` `断电` `断电`** 后剪断,分别接入**负载入**与**负载出**.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/接线示意图.png" alt="ESP-01.jpg" style="zoom: 80%;" />



通电成功后,设备大概是这样子.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/通电.jpg" alt="ESP-01.jpg" style="zoom: 50%;" />





## UDP控制📧

我用我的老本行.net core给大家写了一个命令行工具 通过如下命令调用该工具,即可实现该设备的开和关.

```bash
CSharpUdpClient.exe 192.168.1.5 4210 on
CSharpUdpClient.exe 192.168.1.5 4210 off
```

## APP控制📱

App的控制,打开电灯blinker app, 该设备在线后,可通过设备内你自定义的两个图标控制该设备的开关.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/app2.jpg" alt="ESP-01.jpg" style="zoom:50%;" />

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/app1.jpg" alt="ESP-01.jpg" style="zoom:50%;" />

## 小爱同学📢

小爱同学的控制就有点复杂了,首先要下载米家app, 在**我的 -> 其他平台设备->绑定`点灯科技`的账号**并同步设备.

然后下载小爱同学app, 用小米账户登录,添加训练,比如打开电脑,关闭电脑,即可语音控制开关.

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/小爱同学.jpg" alt="ESP-01.jpg" style="zoom:50%;" />



## 电脑开关机控制💻

Win+R 输入 gpedit.msc 在**电脑配置->电脑设置-> 开关机脚本**内,添加我在前面UDP控制的那一章节中描述的脚本,即可在电脑开机时自动打开显示器,音响等设备, 晚上睡觉前,电脑关机的时候,也会自动把电源断开.

同理,你也可以新建两个bat文件,在文件里面把命令写入,在我的GitHub中已经把相关文件准备好了,仅供参考. 

<img src="https://raw.githubusercontent.com/liuzhenyulive/ESP8266SmartSwitch/master/Pic/startupandshutdown.png" alt="ESP-01.jpg" style="zoom:50%;" />



所有代码和工具可以去我的GitHub仓库下载, 

好了,今晚总算睡个好觉了(～﹃～)~zZ   能得到心理和生理得满足,我真是个幸福的人😈.

https://github.com/liuzhenyulive/ESP8266SmartSwitch

