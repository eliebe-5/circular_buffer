# Circular buffer for c

Simple to use circular buffer to be used in multithread or network applications.

# How To

Create and init buffer.
```
circular_buffer cb;
if(init_circular_buffer(512, &cb) != OK_SIGNAL)
  return ERROR_SIGNAL;
```

Write to buffer.
```
char str[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\n'};
write_buffer(&cb, str, 14);
```

Read from buffer.
```
byte out;
while(read_buffer(&cb, &out) == OK_SIGNAL)
  printf("%c", out);
```

See example using threads in test.c
