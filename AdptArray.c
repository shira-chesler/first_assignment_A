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

/// @brief creating an AdptArray
/// @param copy copy function for the elements inside adptArry
/// @param delete delete function for the elements inside adptArry 
/// @param print print function for the elements inside adptArry
/// @return pointer to the new adptArray
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete,PRINT_FUNC print)
{
    if (copy==NULL || delete==NULL || print==NULL) //one of the function's null
    {
        return NULL;
    }
    PAdptArray paa = (PAdptArray) malloc(sizeof(AdptArray));
    if (!paa) //allocation failed
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

/// @brief deletes the AdptArray
/// @param paa pointer to the AdptArray
void DeleteAdptArray(PAdptArray paa)
{
    if(!paa) //pointer null
    {
        return;
    }
    if(!(paa->pElemArr)) //array doesn't exists
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
/// @brief set AdptArray at given index
/// @param paa pointer to AdptArray
/// @param idx index to set AdptArray at
/// @param p_new_e pointer to the new element to put at the AdptArray
/// @return if seting the new element at the AdptArray succeded or not
Result SetAdptArrayAt(PAdptArray paa, int idx, PElement p_new_e)
{
    if (paa == NULL || idx < 0)
    {
        return FAIL;
    }
    
    int arr_size = paa->ArrSize;
    
    if (idx >= arr_size) //needs to allocate new memory
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
        free(paa->pElemArr); //frees old AdptArray container
        paa->pElemArr = new_arr;
    }
    if(paa->pElemArr[idx])
    {
        paa->delete_function(paa->pElemArr[idx]); //replacing element (?)
    }
    paa->pElemArr[idx] = paa->copy_function(p_new_e);//placing element (!)
    if(idx>=arr_size) //needs to change container size
    {
        paa->ArrSize=idx+1;
    }
    return SUCCESS;
}

/// @brief get AdptArray element at specific index
/// @param paa pointer to the AdptArray
/// @param idx index to get from at array
/// @return the element at requested index
PElement GetAdptArrayAt(PAdptArray paa, int idx)
{
    if(paa==NULL || paa->pElemArr==NULL || idx>paa->ArrSize-1 || idx < 0) //request is not proper
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

/// @brief gets the container AdptArray size
/// @param paa pointer to the AdptArray
/// @return the size of the AdptArray
int GetAdptArraySize(PAdptArray paa)
{
    if(!paa)
    {
        return -1;
    }
    return paa->ArrSize;
}

/// @brief prints all the objects inside the DB
/// @param paa pointer to the AdptArray
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
