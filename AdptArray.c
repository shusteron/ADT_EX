#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC COPY_FUNC, DEL_FUNC DEL_FUNC,PRINT_FUNC PRINT_FUNC){
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = DEL_FUNC;
	pArr-> copyFunc = COPY_FUNC;
    pArr -> printFunc = PRINT_FUNC;
	return pArr;

}


void DeleteAdptArray(PAdptArray pArr){

    if (pArr == NULL)
        return;
    for(int i=0; i<pArr->ArrSize; ++i){
        if(((pArr->pElemArr)[i])!=NULL){
            pArr -> delFunc((pArr->pElemArr)[i]);
        }
    }
    free(pArr->pElemArr);
	free(pArr);    
}

Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElem){
    PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (index >= pArr->ArrSize)
	{
		
        // Extend Array 
		if ((newpElemArr = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
    if((pArr->pElemArr)[index]!=NULL){
        pArr->delFunc((pArr->pElemArr)[index]);
    }
	(pArr->pElemArr)[index] = pArr->copyFunc(pNewElem);

	// Update Array Size
    if(index >= pArr->ArrSize){
        pArr->ArrSize = index + 1;
    }
	else{
        pArr->ArrSize =pArr->ArrSize;
    } 
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int index){
    if((pArr->pElemArr)[index]==NULL) return FAIL;
    else{
        return pArr->copyFunc((pArr->pElemArr)[index]);
    }

}

int GetAdptArraySize(PAdptArray pArr){
    if( pArr == NULL){
        return -1;
    }
    return pArr -> ArrSize;

}
void PrintDB(PAdptArray pArr){
    for(int i=0; i<pArr->ArrSize;i++){
        if((pArr ->pElemArr)[i] !=NULL){
            pArr->printFunc((pArr->pElemArr)[i]);
        }
    }
}




