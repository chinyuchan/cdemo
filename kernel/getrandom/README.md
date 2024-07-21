# getrandom

getrandom函数的出现，主要是为了解决之前Linux系统中存在的一些随机数生成漏洞和不稳定性。
在过去，Linux系统中的`/dev/random和/dev/urandom`设备是用来生成随机数的， 但是这两个设备存在一些问题。
`/dev/random`会在随机数池中的熵用尽时阻塞进程，导致系统性能下降；而`/dev/urandom`虽然不会阻塞，但可能产生不够安全的随机数。
于是，Linux内核引入了getrandom函数，以提供更加安全可靠的随机数生成机制。

```c
#include <sys/random.h>

ssize_t getrandom(void buf[.buflen], size_t buflen, unsigned int flags);
```
* 功能：产生指定长度的随机数
* 返回值：
  * 成功：返回拷贝到buf的字符数，有可能返回的字符数小于`buflen`，则需要重新调用
  * 出错：返回`-1`并设置`errno`



