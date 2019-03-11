#include "hello.pb.h"


int main()
{
  //1.序列化
  //按照二进制方式进行序列化
  //优点：效率比较高（压缩的效率高，网络传输或者数据存储的时候资源开销就小）
  //缺点:可读性差，不方便调式
  Hello hello;
  hello.set_name("xjh");
  hello.set_score(100);
  std::string buf;
  hello.SerializeToString(&buf);
  std::cout<<buf<<std::endl;

  //反序列化
  Hello hello_result;
  hello_result.ParseFromString(buf);
  std::cout<<hello_result.name()<<", "<<hello_result.score()<<std::endl;
}
