#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main()
	int fd;
	struct termios options;

	// открываем последовательный порт для Bluetooth модуля
	fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
    	std::cerr << "Error opening serial port" << std::endl;
    	return 1;
	

	// настраиваем параметры последовательного порта
	tcgetattr(fd,	options);
	cfsetispeed(   options, B9600);
	cfsetospeed(   options, B9600);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(fd, TCSANOW,	options);

	// читаем данные из Bluetooth модуля и выводим их в терминал
	char buffer[256];
  while (true){
	// читаем данные из Bluetooth модуля и выводим их в терминал
	int bytes_read = read(fd, buffer, 255);
	if (bytes_read > 0)
    	buffer[bytes_read] = '';
    	std::cout << "Received: " << buffer;
	

	// читаем пользовательский ввод и отправляем его в Bluetooth модуль
	std::string input;
	std::cout << "Enter a message: ";
	std::getline(std::cin, input);
	write(fd, input.c_str(), input.length());

	usleep(100000);
  }
	close(fd); // закрываем последовательный порт
	return 0;
