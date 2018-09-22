# High-performance handover on srsLTE
## Graduation-Thesis
This is wantong's graduation project (thesis) for undergraduate study at Peking University.
This project is to add X2 Handover feature into an open source LTE software: srsLTE.

# content
有用的其实只有里面srsLTE那一个文件夹,安装和编译过程在readme里都写了,运行的话得用王炜程那里的服务器
几个主文件夹里面
- lib是公用的一些库代码
- srsenb是基站端的代码 
- srsepc是核心网的代码 
- srsue是用户设备端的代码

# wantong修改的部分
- srsue的代码是支持用户设备X2类型基站切换的 所以wantong改的就是lib和srsenb的代码
- lib下面主要写的是include和src文件夹下的asn1下的文件
- 添加了*_x2ap.h/c 这个ASN.1是一种数据结构描述语言 专门用来描述LTE中的各种数据结构信令结构什么的 然后把这两个文件的作用就是把ASN.1语言翻译成c++
- 在srsenb文件夹中，主要写了hdr和src文件夹中，upper文件夹中的x2ap.h/c文件，wantong自己加了这个x2ap模块在里面，X2基站切换基本就在x2ap这个模块里定义的，当然代码根本没写完

# 备注：
- srsLTE已经翻译了一些协议 例如 S1 application protocol，从ASN.1到C++
- wantong就是按照srsLTE已经翻译过的文件的翻译方式翻译的，现在是编译过了，但是只能测个连接，剩下的要完成X2基站切换现在做不到，因为没写完代码，跑起来可能会有很多bug
