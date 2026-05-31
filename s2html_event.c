#include<stdio.h>
#include<string.h>
#include<ctype.h>

#include "s2html_event.h"

char *keywords[] =
{
    "int",
    "char",
    "float",
    "double",
    "return",
    "if",
    "else",
    "while",
    "for",
    "void",
    "break",
    "continue",
    NULL
};

int is_keyword(char *word)
{
    int i = 0;

    while(keywords[i] != NULL)
    {
        if(strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }

        i++;
    }

    return 0;
}

void get_parser_event(FILE *fp, pevent *pevent_obj)
{
    char ch;
    int i = 0;

    ch = fgetc(fp);

    if(ch == EOF)
    {
        pevent_obj->event = PEVENT_EOF;
        return;
    }

    /* PREPROCESSOR */

    if(ch == '#')
    {
        pevent_obj->data[i++] = ch;

        while((ch = fgetc(fp)) != '\n' && ch != EOF)
        {
            pevent_obj->data[i++] = ch;
        }

        pevent_obj->data[i] = '\0';

        pevent_obj->event =
        PEVENT_PREPROCESSOR_DIRECTIVE;

        return;
    }

    /* SINGLE LINE COMMENT */

    if(ch == '/')
    {
        char next = fgetc(fp);

        if(next == '/')
        {
            pevent_obj->data[i++] = '/';
            pevent_obj->data[i++] = '/';

            while((ch = fgetc(fp)) != '\n' && ch != EOF)
            {
                pevent_obj->data[i++] = ch;
            }

            pevent_obj->data[i] = '\0';

            pevent_obj->event =
            PEVENT_SINGLE_LINE_COMMENT;

            return;
        }

        else
        {
            pevent_obj->data[0] = ch;
            pevent_obj->data[1] = '\0';

            pevent_obj->event =
            PEVENT_REGULAR_EXP;

            ungetc(next, fp);

            return;
        }
    }

    /* STRING */

    if(ch == '"')
    {
        pevent_obj->data[i++] = ch;

        while((ch = fgetc(fp)) != '"')
        {
            pevent_obj->data[i++] = ch;
        }

        pevent_obj->data[i++] = '"';
        pevent_obj->data[i] = '\0';

        pevent_obj->event = PEVENT_STRING;

        return;
    }

    /* ASCII CHAR */

    if(ch == '\'')
    {
        pevent_obj->data[i++] = ch;

        while((ch = fgetc(fp)) != '\'')
        {
            pevent_obj->data[i++] = ch;
        }

        pevent_obj->data[i++] = '\'';
        pevent_obj->data[i] = '\0';

        pevent_obj->event = PEVENT_ASCII_CHAR;

        return;
    }

    /* NUMBER */

    if(isdigit(ch))
    {
        pevent_obj->data[i++] = ch;

        while(isdigit(ch = fgetc(fp)))
        {
            pevent_obj->data[i++] = ch;
        }

        pevent_obj->data[i] = '\0';

        pevent_obj->event =
        PEVENT_NUMERIC_CONSTANT;

        ungetc(ch, fp);

        return;
    }

    /* IDENTIFIER OR KEYWORD */

    if(isalpha(ch) || ch == '_')
    {
        pevent_obj->data[i++] = ch;

        while(isalnum(ch = fgetc(fp)) || ch == '_')
        {
            pevent_obj->data[i++] = ch;
        }

        pevent_obj->data[i] = '\0';

        if(is_keyword(pevent_obj->data))
        {
            pevent_obj->event =
            PEVENT_RESERVE_KEYWORD;
        }
        else
        {
            pevent_obj->event =
            PEVENT_REGULAR_EXP;
        }

        ungetc(ch, fp);

        return;
    }

    pevent_obj->data[0] = ch;
    pevent_obj->data[1] = '\0';

    pevent_obj->event = PEVENT_REGULAR_EXP;
}