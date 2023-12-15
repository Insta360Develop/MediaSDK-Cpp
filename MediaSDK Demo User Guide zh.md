###### 1、单独执行stitcherSDKDemo.exe, 输出如图

```powershell
PS E:\workspace\MediaSDK\bin\MediaSDK20231212(windows)\MediaSDK\bin> .\stitcherSDKDemo.exe
can not find input_file
{-help                 | default               | print this message            }
{-inputs               | None                  | input files                   }
{-output               | None                  | out path                      }
{-stitch_type          | template              | template                      }
{                                              | optflow                       }
{                                              | dynamicstitch                 }
{-hdr_type             | None                  | singleimagehdr                }
{                                              | multiimagehdr_mbb             }
{                                              | multiimagehdr_mpl             }
{-bitrate              | same as input vidoe   | the bitrate of ouput file     }
{-enable_flowstate     | OFF                   | open flowstate                }
{-enable_directionlock | OFF                   | open directionlock            }
{-output_size          | 1920x960              | the resolution of output      }
{-disable_cuda         | true                  | disable_cuda                  }
{-enable_stitchfusion  | OFF                   | stitch_fusion                 }
{-enable_denoise       | OFF                   | enable denoise                }
{-enable_colorplus     | OFF                   | enable colorplus              }
{-colorplus_model      |                       | colorplus_model path          }
{-enable_h265_encoder  | OFF                   | default h264                  }
{-image_sequence_dir   | None                  | the output dir of image_sequence }
{-image_type           | jpg                   | jpg                           }
{                                                png                           }
{-gpu_no               | default 0             | gpu number begin with 0       }
```

###### 2、"**-inputs**"参数 

​	输入的素材种类有两种: 视频和图像

​	对于视频，会有两种模式 5.7K和非5.7K的素材。

​	5.7K的素材会有两个insv的文件, 分别为00和10文件(每个文件保存一个鱼眼)，输入格式如下:

```
-inputs /path/to/*00*.insv /path/to/*10*.insv
```

​	非5.7K的素材有只有一个文件(一个文件中保存的两个鱼眼)，输入格式如下:

```
-inputs /path/to/*.insv
```

​	对于图片只有一种模式，因为拍摄的时候会将两个鱼眼图片合并到一张图中保存，输入格式如下(支持两个格式insp和jpg)：

```powershell
-inputs /path/to/*.insp
-inputs /path/to/*.jpg
```

###### 3、"**-output**"参数

​	输入用于输出文件的路径.要指定路径和文件后缀名

​	对于视频(支持格式为mp4)

```powershell
-output /path/to/*.mp4
```

​	对于图片(支持格式为jpg)

```powershell
-output /path/to/*.jpg
```

###### 4、"**-image_sequence_dir**"参数

​	这个参数的功能主要是将视频输出成图片序列。设置了这个参数以后，就不要设置"**-output**"的这个参数了 。 对这个参数只	是需要设置路径就好. "-image_type"这个参数可以指定输出图片的格式，目前支持png和jpg。默认是jpg。 

```powershell
-image_sequence_dir /path/to/
```

###### 5、"**-output_size**"参数
​	这个参数设置输出分辨率。注意要宽高比要设置2:1,同时数值为偶数

###### 6、"**-enable_h265_encoder**"参数
​	这个参数的主要作用是开启h265的编码，主要作用是为了解决在cuda环境下大于4k分辨率不能开启硬件编码的问题。默认	是h264编码

###### 7、"-stitch_type"参数

​	这个参数是设置拼接类型。有三种模板拼接(template)、动态拼接(dynamicstitch)、光流拼接(optflow)。效果方面，依次拼接效果是越来越好。性能上，消耗时间越来越多。

###### 8、"-bitrate"参数

​	这个参数是设置导出码率。

###### 9、"-enable_flowstate"参数

​	这个参数用于开启防抖功能

###### 10、"-enable_directionlock"参数

​	这个参数参数用于开启方向锁定，同时要设置"-enable_flowstate"

###### 11、"-enable_stitchfusion"参数

​	这个参数用于开启消色差的功能.

###### 12、"-enable_denoise"参数

​	这个参数用于开启降噪功能

###### 13、"-enable_colorplus"参数

​	这个参数用于开启色彩增强功能，同时指定模型文件，可以使用参数"-colorplus_model"指定模型文件路径

###### 14、Note
​	对于全景素材的播放默认，建议使用insta360的stuido或者potplayer，通过设置选项进行全景查看。