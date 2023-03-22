#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>

//at the struct definition
typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delete_function;
    COPY_FUNC copy_function;
    PRINT_FUNC print_function;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete,PRINT_FUNC print)
{
    if (copy==NULL || delete==NULL || print==NULL)
    {
        return NULL;
    }
    PAdptArray paa = (PAdptArray) malloc(sizeof(AdptArray));
    if (!paa) 
    {
        return NULL;
    }
    paa->ArrSize=0;
    PElement* pElemArr=NULL;
    paa->pElemArr=pElemArr;
    paa->delete_function = delete;
    paa->copy_function = copy;
    paa->print_function = print;
    return paa;
}
void DeleteAdptArray(PAdptArray paa)
{
    if(!paa)
    {
        return;
    }
    if(!(paa->pElemArr))
    {
        free(paa);
        return;
    }
    for (int i = 0; i < paa->ArrSize; ++i) 
    {
        if(paa->pElemArr[i])
        {
            paa->delete_function(paa->pElemArr[i]);
        }
    }
    free(paa->pElemArr);
    free(paa);
    return;
}

//at this function (setadptarray) I used my solution for question 4 in the Moed A in software systems 1 test
//also, I used the given code in the test for the parts that I didn't had to write on my own there as basis for this function
Result SetAdptArrayAt(PAdptArray paa, int idx, PElement p_new_e)
{
    if (paa == NULL || idx < 0)
    {
        return FAIL;
    }
    int arr_size = paa->ArrSize;
    if (idx >= arr_size)
    {
        PElement* new_arr = (PElement*) calloc((idx + 1), sizeof(PElement));
        if (!new_arr)
        {
            return FAIL;
        }
        for (int i = 0; i < arr_size; ++i) 
        {
            new_arr[i] = paa->pElemArr[i];
        }
        free(paa->pElemArr);
        paa->pElemArr = new_arr;
    }
    if(paa->pElemArr[idx])
    {
        paa->delete_function(paa->pElemArr[idx]);
    }
    paa->pElemArr[idx] = paa->copy_function(p_new_e);
    if(idx>=arr_size)
    {
        paa->ArrSize=idx+1;
    }
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray paa, int idx)
{
    if(paa==NULL || paa->pElemArr==NULL || idx>paa->ArrSize-1 || idx < 0)
    {
        return NULL;
    } 
    else
    {
        if(!(paa->pElemArr[idx]))
        {
            return NULL;
        } 
        else
        {
            return paa->copy_function(paa->pElemArr[idx]);
        }
    }
}
int GetAdptArraySize(PAdptArray paa)
{
    if(!paa)
    {
        return -1;
    }
    return paa->ArrSize;
}
void PrintDB(PAdptArray paa)
{
    if(paa==NULL || paa->pElemArr==NULL)
    {
        return;
    }
    for (int i = 0; i < paa->ArrSize; ++i) 
    {
        if(paa->pElemArr[i])
        {
            paa->print_function(paa->pElemArr[i]);
        }
    }
}