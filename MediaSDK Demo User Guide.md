###### 1、Running `stitcherSDKDemo.exe` Standalone   When executed without additional arguments, `stitcherSDKDemo.exe` will produce output similar to the provided illustration:

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
{-camera_accessory_type| default 0             | refer to 'common.h'           }
{-enable_area_sample   | OFF                   | used to Eliminate moiré       }
```

###### 2、 "-inputs" 

​	 Input media can be categorized as video or image:

​	 - For videos, the files are distinguished by resolution:

​	 	- 5.7K videos consist of a pair of '.insv' files, labeled as '00' and '10', each corresponding to content from one of the fisheye lenses. The input format should be as depicted:

```
-inputs /path/to/*00*.insv /path/to/*10*.insv
```

​		- Non-5.7K videos are combined into a single file accommodating both fisheye lens outputs. The input format should be as depicted:

```
-inputs /path/to/*.insv
```

​	 \- For images, they are typically saved as one file containing both fisheye image projections, with the following input format (supporting '.insp' and '.jpg'):

```powershell
-inputs /path/to/*.insp
-inputs /path/to/*.jpg
```

###### 3、 "-output"

​	 Designate the file path and filename, including its extension, for the processed output. 

​	- Applicable for videos with an '.mp4' format.

```powershell
-output /path/to/*.mp4
```

​	- Applicable for images with an 'jpg' format)

```powershell
-output /path/to/*.jpg
```

###### 4、"-image_sequence_dir" 

​	Assigns the folder destination for outputting video frames as an image sequence. When this parameter is used, there is no need to define `-output`, simply providing the directory path is sufficient. Use `-image_type` to choose the format of the sequence images from either 'png' or 'jpg', with 'jpg' set as the default filetype.

```powershell
-image_sequence_dir /path/to/
```

###### 5、"-output_size" 
​	  Specifies the target resolution for output media. Ensure the aspect ratio is maintained at 2:1 and input even number values for width and height.

###### 6、"-enable_h265_encoder" 
​	Activates H265 (HEVC) encoding, particularly useful for circumventing hardware encoding limitations in CUDA environments when dealing with resolutions beyond 4K. Defaults to H264 if unspecified.

###### 7、"-stitch_type" 

​	Determines the method of combining captured images into a seamless panorama: 'template' for template stitching, 'dynamicstitch' for dynamic stitching, and 'optflow' for optical flow stitching. Quality of result enhances from template to optflow, but processing time also increases proportionally.

###### 8、"-bitrate"

​	 Defines the targeted bitrate for the output file, impacting file size and quality.

###### 9、"-enable_flowstate"

​	 Enables a stabilization feature to reduce motion-induced irregularities in the footage.

###### 10、"-enable_directionlock"

​	 Locks the viewing direction to ensure a fixed orientation during playback. Stabilization via `-enable_flowstate` must also be activated for this to function.

###### 11、"-enable_stitchfusion"

​	 Activates stitch fusion to reduce chromatic aberrations in stitched panoramic images.

###### 12、"-enable_denoise"

​	Turns on noise reduction to minimize undesired grain and noise from the final output.

###### 13、"-enable_colorplus"

​	Engages enhanced color correction features. When using this option, the model file path can be specified using the parameter `-colorplus_model`.

###### 14、"-camera_accessory_type"

​	This parameter is used to set the type of camera accessory.

###### 15、"-enable_area_sample"

​	This participation is used to eliminate moiré when exporting to low resolution.

###### 14、Note
​	For optimal viewing of panoramic content, using Insta360's Studio or PotPlayer is recommended, with appropriate panorama viewing settings enabled.