# UE4Ovrvision
* http://dev.ovrvision.com/doc_ja/index.php?downloads#sdk v2.16 を DL (download v2.16)
* コピーする (copy)
~~~
copy C:\ovrvisionsdk_windows\include\*.h UE4Ovrvision\ThirdPaty\ovrvisionsdk_windows\include
copy C:\ovrvisionsdk_windows\bin\x64\*.lib UE4Ovrvision\ThirdPaty\ovrvisionsdk_windows\bin\x64\
copy C:\ovrvisionsdk_windows\bin\x64\*.dll UE4Ovrvision\ThirdPaty\ovrvisionsdk_windows\bin\x64\
~~~
* .uproject を右クリック(right click .uproject) → Generate Visual Studio project files → .sln を開いてビルド (open .sln and build)