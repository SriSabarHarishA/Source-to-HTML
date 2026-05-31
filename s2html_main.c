#include<stdio.h>
#include<stdlib.h>

#include "s2html_event.h"
#include "s2html_conv.h"

int main(int argc, char *argv[])
{
    FILE *fptr_src;
    FILE *fptr_dest;

    pevent pevent_obj;

    char output_file[100];

    if(argc < 2)
    {
        printf("Usage : ./a.out <input_file>\n");
        return 1;
    }

    fptr_src = fopen(argv[1], "r");

    if(fptr_src == NULL)
    {
        printf("Unable to open source file\n");
        return 1;
    }

    sprintf(output_file, "%s.html", argv[1]);

    fptr_dest = fopen(output_file, "w");

    if(fptr_dest == NULL)
    {
        printf("Unable to create html file\n");
        return 1;
    }

    html_begin(fptr_dest);

    while(1)
    {
        get_parser_event(fptr_src, &pevent_obj);

        if(pevent_obj.event == PEVENT_EOF)
        {
            break;
        }

        source_to_html(fptr_dest, &pevent_obj);
    }

    html_end(fptr_dest);

    fclose(fptr_src);
    fclose(fptr_dest);

    printf("HTML generated successfully\n");

    return 0;
}