#ifndef S2HTML_CONV_H
#define S2HTML_CONV_H

#include<stdio.h>
#include "s2html_event.h"

void html_begin(FILE *fp);
void html_end(FILE *fp);

void source_to_html(FILE *fp, pevent *pevent_obj);

#endif