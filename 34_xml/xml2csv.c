#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <dirent.h>

#include <string.h>
#include <libxml/parser.h>

#define CSVFILE "./train.csv"
#define SUFFIX ".xml"

// clang-11 demo.c -I /usr/local/include/libxml2/ -lxml2 && ./a.out

FILE * csv;

int listXML(char *);
void readXML(char *);
void parserNode(xmlNodePtr, xmlDocPtr);
void parserFileName(xmlNodePtr, xmlDocPtr);
void paserSize(xmlNodePtr, xmlDocPtr);
void paserObject(xmlNodePtr, xmlDocPtr);

int main(int argc, char **argv)
{
    char **files;
    int num;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s path_of_xml \n", *argv);
        return EXIT_FAILURE;
    }
    ++argv;
    csv = fopen(CSVFILE, "w");
    if (NULL == csv)
    {
        perror("");
        fprintf(stderr, "can't open %s file", CSVFILE);
        return EXIT_FAILURE;
    }
    num = listXML(*argv);
    fclose(csv);
    fprintf(stdout, "find %d xml file to wait paser. \n", num);
    return EXIT_SUCCESS;
}

int listXML(char *dirname)
{
    struct dirent *entry = NULL;
    int lenOfDir = strlen(dirname);
    int num = 0;
    DIR *dir = NULL;

    dir = opendir(dirname);
    if (NULL == dir)
    {
        fprintf(stderr, "can't read any info from %s", dirname);
        perror("");
        closedir(dir);
        return -1;
    }

    fprintf(csv, "filename,width,height,class,xmin,ymin,xmax,ymax\n");

    while (NULL != (entry = readdir(dir)))
    {
        char *ret;
        ret = strpbrk(entry->d_name, SUFFIX);
        if (ret && strcmp(SUFFIX, ret))
            continue;

        char *fullName = malloc(lenOfDir + strlen(entry->d_name) + 1);
        strcpy(fullName, dirname);
        strcat(fullName, "/");
        strcat(fullName, entry->d_name);
        readXML(fullName);
        ++num;
        free(fullName);
    }

    closedir(dir);

    return num;
}

void readXML(char *filename)
{
    xmlDocPtr document;
    xmlNodePtr current;
    document = xmlReadFile(filename, NULL, 0);
    current = xmlDocGetRootElement(document)->xmlChildrenNode;
    while (NULL != current)
    {
        parserNode(current, document);
        current = current->next;
    }
}

void parserNode(xmlNodePtr current, xmlDocPtr document)
{
    parserFileName(current, document);
}

void parserFileName(xmlNodePtr current, xmlDocPtr document)
{
    if (xmlStrcmp(current->name, (const xmlChar *)"filename"))
    {
        paserSize(current, document);
        return;
    }

    xmlChar *filename = xmlNodeListGetString(document, current->xmlChildrenNode, 1);
    fprintf(csv, "%s,", filename);
}

void paserSize(xmlNodePtr current, xmlDocPtr document)
{
    if (xmlStrcmp(current->name, (const xmlChar *)"size"))
    {
        paserObject(current, document);
        return;
    }

    current = current->xmlChildrenNode;
    for (int i = 0; i < 4; i++)
    {
        xmlChar *info = xmlNodeListGetString(document, current->xmlChildrenNode, 1);
        if (NULL != info)
        {
            fprintf(csv, "%s,", info);
        }
        current = current->next;
    }
}

void paserObject(xmlNodePtr current, xmlDocPtr document)
{
    if (xmlStrcmp(current->name, (const xmlChar *)"object"))
    {
        return;
    }

    current = current->xmlChildrenNode;
    while (NULL != current)
    {
        if (!xmlStrcmp(current->name, (const xmlChar *)"name"))
        {
            xmlChar *clazz = xmlNodeListGetString(document, current->xmlChildrenNode, 1);
            if (NULL != clazz)
                fprintf(csv, "%s,", clazz);
        }
        if (!xmlStrcmp(current->name, (const xmlChar *)"bndbox"))
        {
            xmlNodePtr box = current->xmlChildrenNode;
            while (NULL != box)
            {
                xmlChar *pos = xmlNodeListGetString(document, box->xmlChildrenNode, 1);
                if (NULL != pos)
                    fprintf(csv, "%s,", pos);
                box = box->next;
            }
            fprintf(csv, "\n");
        }
        current = current->next;
    }
}