## 有向图两点间路径规划
### 其分为两个版本
- path.cpp
- path_file.cpp
  
#### <注>path.cpp为控制台读入版本，path_file.cpp为文件读入版本
读入格式(两种版本读入格式相同):<br/>
城市数m 路径数n<br/>
(以下n行 从A城到B城)<br/>
A城 B城 车费<br/>
(查询 从A城到B城，可无限查询，结束应输入0 0)<br/>
A城 B城<br/>
例：<br/>
3 2 //3城市 2路径<br/>
1 2 3 //1城 到 2城 3车费<br/>
2 3 4 //2城 到 3城 4车费<br/>
1 3 //查询1城 到 3城 路径<br/>
2 3 //查询2城 到 3城 路径<br/>
0 0 //查询停止标志<br/>

#### <注>path_file.cpp版本，应将文件写在path.in中，其输出文件为path.out，可直接调用path_file.exe文件，要与path.in放置在同一目录下

#### 项目链接 https://github.com/himcrh/Data-Structure-Meaning