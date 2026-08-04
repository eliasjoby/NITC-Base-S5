#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
  Disk disk_run;

  unsigned char buffer[BLOCK_SIZE];
  Disk::readBlock(buffer, 7000);
  char message[] = "hello";
  memcpy(buffer + 20, message, 6);
  Disk::writeBlock(buffer, 7000);

  unsigned char buffer2[BLOCK_SIZE];
  char message2[6];
  Disk::readBlock(buffer2, 7000);
  memcpy(message2, buffer2 + 20, 6);
  std::cout << message2 << std::endl;

  //exercise
  unsigned char buffer3[BLOCK_SIZE];
  char message3[2048];
  Disk::readBlock(buffer3, 0);
  memcpy(message3, buffer3, 2048);

  for(auto ch:message3){
    std::cout << ch << " ";
  }
  std::cout << std::endl;

  return 0;
}
