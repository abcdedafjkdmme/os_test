void kmain() {
  char *video_addr = (char *)0xb8000;
  *video_addr = 'X';
  char strsas[] = "hello";
}
