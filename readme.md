1. My linux project for test.
2. Os source base linux-4.18.5, busybox source base busybox-1.30.1.
3. App module test environment
(1) RabbitMQ Server http://192.168.0.108:15672/ admin 123456
(2) RabbitMQ C-client /home/xucheeng/Downloads/os/rabbitmq-c-master/rabbitmq-c-master
(3) Appache HTTP Server http://192.168.0.105/ 
(4) Sipp 192.168.0.105 /home/xucheeng/Downloads/os/sipp-3.4.1 	

RabbitMQ 测试流程
1. 启动server（192.168.0.108）
（1）cd /usr/lib/rabbitmq/bin 
./rabbitmq-server start
（2）启动Web管理
rabbitmq-plugins enable rabbitmq_management 
可能需要关闭防火墙才能访问
sudo systemctl stop firewalld 临时关闭
sudo systemctl disable firewalld ，然后reboot 永久关闭
sudo systemctl status  firewalld 查看防火墙状态。

2. 启动测试生成者和消费者 192.168.0.105
（1）启动消费者
cd /home/xucheeng/Downloads/os/rabbitmq-c-master/rabbitmq-c-master/build/examples
./amqp_listen 192.168.0.108 5672 amq.direct test
（2）启动生成者
./amqp_sendstring 192.168.0.108 5672 amq.direct test "hello world"

3. MFC 生成者
MFC test_rabbitmq 代替 105 上面的生成者