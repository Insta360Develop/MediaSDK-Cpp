# MediaSDK-Cpp
MediaSDK-Cpp is a C++ library to handle stitching, editing of media from Insta360 Cameras.

### Supported platforms

| Platform | Version                                       |
| :------- | :-------------------------------------------- |
| Windows  | Windows 7 or later, only x64 supported        |
| MacOS    | 10.8.2 or later, only x64 supported           |
| Linux    | Ubuntu, other distributions need to be tested |

### Supported fileformat

| filetype | import format | export format |
| :------- | :------------ | :------------ |
| Video    | insv   	   | mp4		   |
| Image    | insp   	   | jpg           |

## Table of contents

- [Running test demo](#demo)
- [Get Started](#started)
  - [Note](#note)
  - [Image stitcher ](#ImageStitcher)
    - [Create ImageStitcher](#imageSticher_create)
    - [Set Parameter](#imageSticher_param)
    - [Start Stitch](#imageSticher_stitch)
  - [Video stitcher](#videoStitcher) 
  	- [Create VideoStitcher](#videoStitcher_create)
    - [Set Parameter](#videoStitcher_param)
    - [Set process callback function](#videoStitcher_process_callback)
    - [Set error callback function](#videoStitcher_error_callback)
    - [Start Stitch](#videoStitcher_StartStitch)
    - [Cancel Stitch](#videoStitcher_cancelStitch)
- [Parameters Guidance](#Guidance)
	- [inputpath](#inputpath)
	- [stitchType](#stitchtype)
	- [HDRType](#hdrType)
	- [EnableFlowState](#flowstate)





## <span id="demo">Running test demo</span>



**On Ubuntu**, you can do it follow the steps before run **stitcherSDKDemo**.

```bash
$ gcc main.cc -o stitcherSDKDemo -I the path of libmediaSDK -lMediaSDK
$ sudo chmod +x  stitcherSDKDemo
$ export LD_LIBRARY_PATH=LD_LIBRARY_PATH:the path of libMediaSDK.so
$ ./stitcherSDKDemo -h
```



## <span id="started">Get Started</span>

### <span id="note">Note</span>

​		The video stitcher does not support HDR, and run it asynchronously during  stitching. Before call the function **`StartStitch`**, you can call the function **`SetStitchProgressCallback`** so that you can know the current process during stitching, and call the function **`SetStitchStateCallback`** so that you can get the error info  if an error occurs during stitching.
​		The image stitcher runs synchronously.


### <span id="ImageStitcher">Image Stitcher</span>
Before run the `Stitch`, you can do follow ways.

##### <span id="imageSticher_create">Create ImageStitcher</span>

```c++
#include <stitcher/stitcher.h>
#include <stitcher/common.h>

auto imageStitcher = std::make_shared<ins_media::ImageStitcher>();
```

##### <span id="imageSticher_param"> Set Parameter</span>

```c++
imageStitcher->SetInputPath(input_paths); 

imageStitcher->SetStitchType(stitch_type);

imageStitcher->SetHDRType(hdr_type);

imageStitcher->SetOutputPath(output_path);

imageStitcher->SetOutputSize(output_width, output_height);

imageStitcher->EnableFlowState(bEnableFlowState);
```

##### <span id="imageSticher_stitch">Start Stitch</span>

```c++
imageStitcher->Stitch();
```



### <span id="videoStitcher">Video Stitcher</span>

Before run the **`StartStitch`**, you can do follow ways.

##### <span id="videoStitcher_create">Create VideoStitcher</span>

```c++
#include <stitcher/stitcher.h>
#include <stitcher/common.h>

auto videoStitcher = std::make_shared<ins_media::VideoStitcher>();
```

#####  <span id="videoStitcher_param">Set Parameter</span>

```c++
 videoStitcher->SetInputPath(input_paths);
 videoStitcher->SetOutputPath(output_path);
 videoStitcher->SetStitchType(stitch_type);
 videoStitcher->SetOutputSize(output_width, output_height);
 videoStitcher->SetOutputBitRate(output_bitrate);
 videoStitcher->EnableFlowState(bEnableFlowState);
```

##### <span id="videoStitcher_process_callback">Set process callback function</span>

```c++
void process_callback(long lContext, int process, int error) {
    printf("\rprocess = %d%% ", process);
}

...
    
videoStitcher->SetStitchProgressCallback(process_callback, 0);
```

##### <span id="videoStitcher_error_callback">Set error callback function</span>

```c++
void error_callback(long lContext, int error, const char* errinfo) {
	//you can print the error info 
}
...

videoStitcher->SetStitchStateCallback(error_callback, 0);
```

##### <span id="videoStitcher_StartStitch">Start Stitch</span>

```c++
videoStitcher->StartStitch();
```

##### <span id="videoStitcher_cancelStitch"> Cancel Stitch</span>

```c++
videoStitcher->CancelStitch();
```





## <span id="Guidance">Parameters Guidance</span>

#### <span id="inputpath">InputPaths</span>

The parameter is the vector , you can enter multiple paths, or one.

***On video***  The maximum value of the vector is 2. 

***On image***  Generally the size of the vector is 1 , if you turn on HDR , may be you can enter multiple paths.



#### <span id = "stitchtype">StitchType</span>

The parameter has three choices.

```c++
enum class STITCH_TYPE {
    TEMPLATE,
    OPTFLOW,
    DYNAMICSTITCH,
};
```

In terms of speed , **template** is fastest and **optflow** is slowest. default ***TEMPLATE***.



####  <span id="hdrType">HDRType</span>

The parameter has four choices.

```c++
enum class HDR_TYPE {
    ImageHdr_NONE = -1,
    SingleImageHdr = 0,
    MultiImageHdr_mbb = 1,
    MultiImageHdr_mpl = 2,
};
```

if you choice the **<u>ImageHdr_None</u>**, the HDR is turn off. default **<u>ImageHdr_None</u>**

if you has only one image  and you want turn on hdr, you can choice the **<u>SingleImageHdr</u>**

fi you has multiple images and you want turn on hdr . you can choice the **<u>MultiImageHdr_mbb</u>** or **<u>MultiImageHdr_mpl</u>**

**<u>MultiImageHdr_mpl</u>** is faster than **<u>MultiImageHdr_mbb</u>** on running time.



default hdr is turn off , it used for imagestitcher.

#### <span id="flowstate">EnableFlowState</span>

The parameter is turn off or turn on **the flowstate**. if turn on it, the image or the video is more  smooth and steady. 

