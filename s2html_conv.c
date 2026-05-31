#include<stdio.h>

#include "s2html_conv.h"

void html_begin(FILE *fp)
{
    fprintf(fp,
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "<link rel=\"stylesheet\" href=\"styles.css\">\n"
    "</head>\n"
    "<body>\n"
    "<pre>\n");
}

void html_end(FILE *fp)
{
    fprintf(fp,
    "</pre>\n"
    "</body>\n"
    "</html>\n");
}

/* function to print html safe characters */

void print_html_safe(FILE *fp, char *str)
{
    int i;

    for(i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == '<')
        {
            fprintf(fp, "&lt;");
        }

        else if(str[i] == '>')
        {
            fprintf(fp, "&gt;");
        }

        else if(str[i] == '&')
        {
            fprintf(fp, "&amp;");
        }

        else
        {
            fputc(str[i], fp);
        }
    }
}

void source_to_html(FILE *fp, pevent *pevent_obj)
{
    switch(pevent_obj->event)
    {
        case PEVENT_PREPROCESSOR_DIRECTIVE:

            fprintf(fp,
            "<span class=\"preprocessor\">");

            print_html_safe(fp, pevent_obj->data);

            fprintf(fp,
            "</span>");

            break;

        case PEVENT_RESERVE_KEYWORD:

            fprintf(fp,
            "<span class=\"keyword\">");

            print_html_safe(fp, pevent_obj->data);

            fprintf(fp,
            "</span>");

            break;

        case PEVENT_NUMERIC_CONSTANT:

            fprintf(fp,
            "<span class=\"number\">");

            print_html_safe(fp, pevent_obj->data);

            fprintf(fp,
            "</span>");

            break;

        case PEVENT_STRING:

            fprintf(fp,
            "<span class=\"string\">");

            print_html_safe(fp, pevent_obj->data);

            fprintf(fp,
            "</span>");

            break;

        case PEVENT_SINGLE_LINE_COMMENT:

        case PEVENT_MULTI_LINE_COMMENT:

            fprintf(fp,
            "<span class=\"comment\">");

            print_html_safe(fp, pevent_obj->data);

            fprintf(fp,
            "</span>");

            break;

        case PEVENT_ASCII_CHAR:

            fprintf(fp,
            "<span class=\"ascii\">");

            print_html_safe(fp, pevent_obj->data);

            fprintf(fp,
            "</span>");

            break;

        default:

            print_html_safe(fp, pevent_obj->data);
    }
}