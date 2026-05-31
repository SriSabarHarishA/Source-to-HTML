#ifndef S2HTML_EVENT_H
#define S2HTML_EVENT_H

#include<stdio.h>

#define MAX_DATA 1024

typedef enum
{
    PEVENT_NULL,
    PEVENT_PREPROCESSOR_DIRECTIVE,
    PEVENT_RESERVE_KEYWORD,
    PEVENT_NUMERIC_CONSTANT,
    PEVENT_STRING,
    PEVENT_HEADER_FILE,
    PEVENT_REGULAR_EXP,
    PEVENT_SINGLE_LINE_COMMENT,
    PEVENT_MULTI_LINE_COMMENT,
    PEVENT_ASCII_CHAR,
    PEVENT_EOF
}pevent_e;

typedef struct
{
    pevent_e event;
    char data[MAX_DATA];
}pevent;

void get_parser_event(FILE *fp, pevent *pevent_obj);

#endif