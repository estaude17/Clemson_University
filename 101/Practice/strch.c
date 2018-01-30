int main(void)
{
  char str[] = "abcabcabc";
  printf("%d", strchr(&str[4], 'a')-str);
}
