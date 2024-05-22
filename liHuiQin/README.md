# APUE

## p132
- 缓冲区的作用:大多数情况下是好事，合并系统调用
    - 行缓冲：换行时候刷新，满了的时候刷新，强制刷新(标准输出是这样的，终端设备都如此)
    - 全缓冲：满了的时候刷新，强制刷新(默认，除非不是终端设备)
    - 无缓冲：如stderr,需要立即输出的内容

## P136
- cache是读的加速机制，buff是写的加速机制

<table border="1"  width="600px" cellspacing="0px">
  <thead align="center">
    <td>标准IO</td>
    <td>系统调用</td>
  </thead>
  <tbody></tbody>
  <tr>
    <td>r</td>
    <td>O_RDONLY</td>
  </tr>
  <tr>
    <td>r+</td>
    <td>O_RDWR</td>
  </tr>
  <tr>
    <td>w</td>
    <td>O_WRONLY | O_CREAT | O_TRUNC</td>
  </tr>
  <tr>
    <td>w+</td>
    <td>O_RDWR | O_CREAT | O_TRUNC</td>
  </tr>

</table>

## p138
- 跟踪系统调用
```sh
strace ./ab
```
## p149
- 目录
  - glob()
  - opendir()
  - closedir()
  - readdir(3)
  - rewinddir()
  - seekdir()
  - telldir()
- 使用glob函数解析目录内容
## p150
- 使用目录相关函数完成目录解析
## p155
- shadow文件内容$algorithm$salt$digest$
  - getspnam();
  - crypt();
## p156
- 时间戳:time_t char * struct tm
  - time();
  - gmtime();
  - localtime();
  - mktime();
  - strftime();