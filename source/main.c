extern print(char* data);

void kmain(void* mbd,unsigned int magic)
{
unsigned char*videoram=(unsigned char*)0xb8000;
videoram[0]=65;
videoram[1]=7;
videoram[2]=0x07;
}
