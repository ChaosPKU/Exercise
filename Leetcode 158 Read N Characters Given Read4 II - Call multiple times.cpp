/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.
*/
//int read4(char *buf)表示的是从文件中读取数据存入buf中。
//会被调用多次，但read4每读一次文件指针便会后移，且不可逆，所以必须设置全局变量来记录每次读的内容，以及已经使用了其中哪部分数据。
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    char buf4[4];
    int i4 = 0, n4 = 0;
    int read(char *buf, int n) {
        int i = 0;
        while(i < n && (i4 < n4 || ((i4 = 0) < (n4 = read4(buf4)))))
            buf[i++] = buf4[i4++];
        return i;
    }
};
