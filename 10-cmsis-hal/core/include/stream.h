#ifndef STREAM_H
#define STREAM_H

typedef enum {
	USART,
} STREAM;

void stream_init(STREAM stream_type);
void stream_write(STREAM stream_type, const char *data);

#endif
