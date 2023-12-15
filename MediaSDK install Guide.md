1. Install the SDK Package   

   Use the following command to install the Media SDK package on a system with Ubuntu 18.04:

​	`sudo dpkg -i libMediaSDK-dev_2.0-0_amd64_ubuntu18.04.deb`	



2. Post-Installation Check for MediaSDK

​	Once installation is complete, run MediaSDKDemo. If you see the messages below, it confirms that 	libMediaSDK has been installed successfully.



3. Debugging with MediaSDKDemo   

   You can debug directly using MediaSDKDemo, or you can modify and debug using the `[main.cc](http://main.cc)` file located in the `example` directory. Use the following command to compile the demo:

`g++ main.cc -std=c++11 -lMediaSDK -o testSDKDemo`



4. Uninstall the SDK Package   

   To remove the Media SDK package from your system, execute:

     `sudo dpkg -r libMediaSDK-dev`

5. Note:   
   - CUDA version: 11.1   
   - g++ version: g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0