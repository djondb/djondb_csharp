djondb csharp 0.3
=================

This is the driver to connect your c# application to djondb.

Installation
============

After executing the installer you will have the following folders installed in your system:

+ bin
+ libs
   - DBootStrapper.dll
   - x64
      +- djondb_csharp.dll
       - pthreadVC2.dll
       - msvcp110.dll
       - msvcr110.dll
   - x86
      +- djondb_csharp.dll
       - pthreadVC2.dll
       - msvcp110.dll
       - msvcr110.dll
+ Uninstall.exe

DBootStrapper: Is a handy library used to dynamically load x86 or x64 dlls
into your AppDomain, this is called side-by-side Assembly load. It's only
required if you are distributing your application and you want to use
"AnyCPU". Otherwise you can reference the dll you need directly.

Usage
==============



