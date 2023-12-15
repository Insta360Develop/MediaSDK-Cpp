1、安装SDK包

```bash
`sudo dpkg -i libMediaSDK-dev_2.0-0_amd64_ubuntu18.04.deb`
```

   <img src=".\pic\install.jpg" alt="image-20231208150840440" style="zoom:80%;" />

2、安装以后，运行 MediaSDKDemo, 出现下面信息，说明libMediaSDK安装成功

   <img src=".\pic\demo.jpg" alt="image-20231208151044846" style="zoom:80%;" />

3、可以直接使用MediaSDKDemo进行调试，也可以通过当前目录example下的main.cc进行修改进行调试，demo

​	编译指令如下：

```bash
`g++ main.cc -std=c++11 -lMediaSDK -o testSDKDemo`
```

4、卸载SDK包

```bash
`sudo dpkg -r libMediaSDK-dev`
```

5、Note:

​	cuda版本： 11.1

​    g++版本:     g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0