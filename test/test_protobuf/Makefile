PROTOC=/home/xjhah/ThirdPartLibForCpp/el7.x86_64/third_part/bin/protoc 
main:main.cc hello.pb.cc 
	g++ $^ -o $@ -I /home/xjhah/ThirdPartLibForCpp/el7.x86_64/third_part/include -L /home/xjhah/ThirdPartLibForCpp/el7.x86_64/third_part/lib -lprotobuf
hello.pb.cc:hello.proto 
	$(PROTOC) hello.proto --cpp_out=.
