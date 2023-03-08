# ofdm-hls
This project is about an OFDM communication system with multipath channel.
The system can be built up through direct connection and composable pipeline, and the corresponding source codes are attached.

### > Motivation：

Orthogonal Frequency Division Multiplexing (OFDM) is a multiplexing technology which is widely used in 4G and 5G. The system utilizes OFDM’s orthogonal property, which admit us to set subcarriers closer without interference in the frequency domain. Compared with single carrier system, we can transmit more data through same resource. In this way, higher transmit rate could be reached. And due to its narrowband property, we can use a one-tap equalizer for channel compensation, which can reduce the complexity a lot. In this project, we tried to construct an end-to-end OFDM communication system by HLS.

![image](https://user-images.githubusercontent.com/102524142/174599266-031b3a6c-852f-442a-858c-c50b011f02cd.png)


### > Problem Statement：

In wireless communication system, multipath and fading noise are the two main purposes we would like to solve. We can’t control how signal transmitted from transmitter to receiver in wireless system. Each path may arrived receiver through different channel fading gain and wastes different time. This may cause some difficulties for receiver to recover the transmit data. Due to the reason we mentioned, we tried to construct a system based on OFDM which have the ability to conquer all of the non-ideal effects.


### > Folder Structure :

1. Direct Conntection  
All sub-kernels will be wrapped in the top_module, which connect to the host code with hls master interface. Those sub-kernels will connect to each other with hls stream interface.

2. Composable Pipeline  
The whole system will be connected by the hls stream interface.
