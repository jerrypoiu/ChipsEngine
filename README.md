# __ChipsEngine__  
## __Description__    
1. Source code (C++) engine based on DirectX11.  
2. The framework is implemented in Component Based Development (CBD).  
3. LDR(Low Dynamic Range), Forward Rendering.  
4. Class structure and function interface are similar to Unity, familiar to Unity users.  

__Video (Click)__  
[![Video](https://img.youtube.com/vi/Y8z6awMjyoc/0.jpg)](https://www.youtube.com/watch?v=Y8z6awMjyoc) 

__Class Diagram__  
![classdiagram](/DescriptionImage/classDiagram.png)  
 
__File Format__  
|Type|Format|  
|:-------:|----------------------------------|  
|3D|fbx|  
|Texture|dds|  
|Sound|mp3, wav, ther FMOD-enabled formats|  
|Font|spritefont|  

 __Core Features__
> - Transform (Scene Graph)
> - Physics Engine (PhysX) – Rigidbody, Collider
> - Light System – Directional, Spot, Point, Shadow
> - Basic Geometric Rendering, Sky Rendering
> - Mesh, Skin Rendering and Skeletal Animation (FBX SDK)
> - Particle Rendering
> - UI Rendering – Text, Image, Button
> - Post Processing
> - 3D, 2 Sound (FMOD)
> - Input System - Keyboard, Mouse
> - Schedule System
> - Debug Rendering
> - Auto Memory Management  
 
__Post Processing Stack__  
> - Ray Marching
> - Screen Space Ambient Occlusion (SSAO)
> - Dark
> - Depth Of Field
> - Motion Blur
> - Gaussian Blur, Box Blur
> - Vertical Blur, Horizontal Blur
> - Rain
> - Blood
> - Chromatic Aberration
> - Bloom
> - Vignetting
> - Gamma
> - Contrast
> - Bright
> - Saturate
> - Smooth Step
> - Tint
> - Sepia
> - Gray Scale
> - Inverse
> - LUT (2D)
> - Tonemap-ACES, Unreal, Reinhard
> - Old Game Style
> - Edge
> - Embossed
> - Flicker
> - Cartoon
> - Mosaic
> - Vertical Lines, Horizontal Lines
> - Noise
> - Cinematic Line
> - Fade In, Fade Out

## __Requirements__
[FbxSDK](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2019-0)
 - important! you have to download "FBX SDK 2019.0 VS2015 version" and make a "FBXSDK_DIR"(Environment Variable).
 - FBX® SDK is a free, easy-to-use, C++ software development platform and API toolkit that allows application and content vendors to transfer existing content into the FBX format with minimal effort.  
 
[Resource](https://drive.google.com/file/d/1b5gKnsMSfgWKhYkCK3A19AtoijYiqyRl/view?usp=sharing)  
 - Download the resource and extract it to the 01_Asset folder.
 
[Lib, Dll](https://drive.google.com/file/d/1IzhkCYr7YYKaj9h9ftfQW_yliZ2I7n-K/view?usp=sharing)  
 - Download the resource and extract it to the 03_Lib, 04_Dll folder.  
 
[FbxSDK bin](https://drive.google.com/file/d/1z8lkl08F_j2KhMRP0ReUHIHmjNIUNUMu/view?usp=sharing)  
 - Download the resource and extract it to the 02_Script\PhysXSDK\PhysX folder. 

## __Using Library, SDK__

DirectX11 
 - DirectX is a collection of application programming interfaces (APIs) for handling tasks related to multimedia, especially game programming and video, on Microsoft platforms.
 
[tinyxml2](https://github.com/leethomason/tinyxml2)    
 - TinyXML-2 is a simple, small, efficient, C++ XML parser that can be easily integrated into other programs.
 - zlib License  

[DirectXTK](https://github.com/jerrypoiu/DirectXTK)  
 - This package contains the "DirectX Tool Kit", a collection of helper classes for writing Direct3D 11 C++ code for Universal Windows Platform (UWP) apps for Windows 10, Xbox One, and Win32 desktop applications for Windows 7 Service Pack 1 or later.  
 - MIT License  

[FMOD](https://www.fmod.com/)  
 - FMOD is the solution for adaptive audio.

 - Non-Commercial License

[PhysX-3.4](https://developer.nvidia.com/physx-sdk%20)  
 -   The NVIDIA PhysX SDK is a scalable multi-platform physics solution supporting a wide range of devices, from smartphones to high-end multicore CPUs and GPUs.

[FbxSDK](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-0)  
 - FBX® SDK is a free, easy-to-use, C++ software development platform and API toolkit that allows application and content vendors to transfer existing content into the FBX format with minimal effort.
