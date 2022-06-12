#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>

// clang-11 demo.c -I /usr/local/include/libxml2/ -lxml2

int main1(int argc, char **argv)
{
    xmlDoc *document;
    xmlNode *root, *first_child, *node;
    char *filename;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename.xml\n", argv[0]);
        return 1;
    }
    filename = argv[1];

    document = xmlReadFile(filename, NULL, 0);
    root = xmlDocGetRootElement(document);
    fprintf(stdout, "Root is <%s> (%i)\n", root->name, root->type);
    first_child = root->children;
    for (node = first_child; node; node = node->next)
    {
        fprintf(stdout, "\t Child is <%s> (%i)\n", node->name, node->type);
    }
    fprintf(stdout, "...\n");
    return 0;
}

int main()
{
    xmlDocPtr document;
    document = xmlReadFile("/home/afterloe/Datasets/sp/1651908063-421-2.xml", NULL, 0);

    xmlNodePtr current;
    fprintf(stdout, "filename,width,height,class,xmin,ymin,xmax,ymax\n");
    current = xmlDocGetRootElement(document);
    current = current->xmlChildrenNode;
    while (NULL != current)
    {
        if (!xmlStrcmp(current->name, (const xmlChar *)"filename"))
        {
            xmlChar *filename = xmlNodeListGetString(document, current->xmlChildrenNode, 1);
            fprintf(stdout, "%s,", filename);
        }
        if (!xmlStrcmp(current->name, (const xmlChar *)"size"))
        {
            xmlNodePtr size = current->xmlChildrenNode;
            for (int i = 0; i < 4; i++)
            {
                xmlChar *filename = xmlNodeListGetString(document, size->xmlChildrenNode, 1);
                if (NULL != filename)
                {
                    fprintf(stdout, "%s,", filename);
                }
                size = size->next;
            }
        }
        if (!xmlStrcmp(current->name, (const xmlChar *)"object"))
        {
            xmlNodePtr object = current->xmlChildrenNode;
            while (NULL != object)
            {
                if (!xmlStrcmp(object->name, (const xmlChar *)"name"))
                {
                    xmlChar *clazz = xmlNodeListGetString(document, object->xmlChildrenNode, 1);
                    if (NULL != clazz)
                        fprintf(stdout, "%s,", clazz);
                }
                if (!xmlStrcmp(object->name, (const xmlChar *)"bndbox"))
                {
                    xmlNodePtr box = object->xmlChildrenNode;
                    while (NULL != box)
                    {
                        xmlChar *pos = xmlNodeListGetString(document, box->xmlChildrenNode, 1);
                        if (NULL != pos)
                            fprintf(stdout, "%s,", pos);
                        box = box->next;
                    }
                }
                object = object->next;
            }
        }
        current = current->next;
    }
    fprintf(stdout, "\n");

    xmlFreeDoc(document);
    return EXIT_SUCCESS;
}