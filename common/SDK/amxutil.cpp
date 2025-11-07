#include "amx.h"
#include <cstring>

// Implementation of AMX utility functions

int AMXAPI amx_GetAddr(AMX *amx, cell amx_addr, cell **phys_addr)
{
    unsigned char *data = (amx->data != NULL) ? amx->data : amx->base + ((AMX_HEADER *)amx->base)->dat;
    *phys_addr = (cell *)(data + (int)amx_addr);
    return AMX_ERR_NONE;
}

int AMXAPI amx_StrLen(const cell *cstring, int *length)
{
    int len = 0;
    if (cstring != NULL)
    {
        while (*cstring++ != 0)
            len++;
    }
    *length = len;
    return AMX_ERR_NONE;
}

int AMXAPI amx_GetString(char *dest, const cell *source, int use_wchar, size_t size)
{
    if (dest == NULL || source == NULL || size == 0)
        return 0;

    int len = 0;
    while (len < (int)size - 1 && *source != 0)
    {
        dest[len] = (char)*source;
        source++;
        len++;
    }
    dest[len] = '\0';
    return len;
}

int AMXAPI amx_SetString(cell *dest, const char *source, int pack, int use_wchar, size_t size)
{
    if (dest == NULL || source == NULL)
        return 0;

    int len = 0;
    if (pack)
    {
        // Packed string
        cell *ptr = dest;
        while (*source != '\0' && len < (int)size)
        {
            *ptr = (cell)*source;
            source++;
            ptr++;
            len++;
        }
        *ptr = 0;
    }
    else
    {
        // Unpacked string
        while (*source != '\0' && len < (int)size)
        {
            *dest = (cell)*source;
            source++;
            dest++;
            len++;
        }
        *dest = 0;
    }
    return len;
}

int AMXAPI amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number)
{
    AMX_HEADER *hdr = (AMX_HEADER *)amx->base;
    AMX_FUNCSTUBNT *natives = (AMX_FUNCSTUBNT *)(amx->base + hdr->natives);
    
    int numnatives = (hdr->libraries - hdr->natives) / hdr->defsize;
    
    if (number == -1)
    {
        // Count natives
        number = 0;
        while (nativelist[number].name != NULL)
            number++;
    }
    
    for (int i = 0; i < number; i++)
    {
        if (nativelist[i].name == NULL)
            break;
            
        // Find native in AMX
        for (int j = 0; j < numnatives; j++)
        {
            char *name = (char *)(amx->base + natives[j].nameofs);
            if (strcmp(name, nativelist[i].name) == 0)
            {
                // Register native
                natives[j].address = (ucell)nativelist[i].func;
                break;
            }
        }
    }
    
    return AMX_ERR_NONE;
}
