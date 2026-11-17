#include "invert.h"

//-------------------------------------------------------------------------------------------------//

int insert_file(file_t **files, char *fname)
{
    file_t *newnode = malloc(sizeof(file_t));
    
    if(newnode == NULL)
        return FAILURE;
    strcpy(newnode->fname,fname);
    newnode->link = NULL;

    if(*files == NULL)
    {
        *files = newnode;
        return SUCCESS;
    }

    file_t *temp = *files;

    while(temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = newnode;
    return SUCCESS;
}

//-------------------------------------------------------------------------------------------------//

int isduplicate_file(char *fname, file_t *files)
{
    while(files!=NULL)
    {
        if(strcmp(files->fname,fname) == 0)
            return SUCCESS;

        files = files->link;
    }
    return FAILURE;
}

//-------------------------------------------------------------------------------------------------//

int insert_word(char *fname, char *word, mainnode_t *arr[])
{
    int index;
    
    if(isupper(word[0]))
        index = word[0] - 'A';
    else if(islower(word[0]))
        index = word[0] - 'a';
    else
        index = 26;

    if(arr[index] == NULL)
    {
        subnode_t *S_newnode = malloc(sizeof(subnode_t));
        strcpy(S_newnode->file_name,fname);
        S_newnode->word_count = 1;
        S_newnode->link = NULL;

        mainnode_t *M_newnode = malloc(sizeof(mainnode_t));
        strcpy(M_newnode->word,word);
        M_newnode->file_count = 1;
        M_newnode->sub_link = S_newnode;
        M_newnode->link = NULL;

        arr[index] = M_newnode;
        return SUCCESS;
    }
    
    mainnode_t *M_temp = arr[index];
    mainnode_t *M_prev = NULL;

    while(M_temp !=NULL)
    {
        if(strcmp(M_temp->word,word) == 0)
        {
            subnode_t *S_temp = M_temp->sub_link;
            subnode_t *S_prev = NULL;
        
            while(S_temp!=NULL)
            {
                if(strcmp(S_temp->file_name,fname) == 0)
                {
                    (S_temp->word_count)++;
                    return SUCCESS;
                }
                S_prev = S_temp;
                S_temp = S_temp->link;
            }

            subnode_t *S_newnode = malloc(sizeof(subnode_t));
            strcpy(S_newnode->file_name,fname);
            S_newnode->word_count = 1;
            S_newnode->link = NULL;
        
            S_prev->link = S_newnode;
            (M_temp->file_count)++;
            return SUCCESS;
        }
        M_prev = M_temp;
        M_temp = M_temp->link;
    }
  
    subnode_t *S_newnode = malloc(sizeof(subnode_t));
    strcpy(S_newnode->file_name,fname);
    S_newnode->word_count = 1;
    S_newnode->link = NULL;
        
    mainnode_t *M_newnode = malloc(sizeof(mainnode_t));
    strcpy(M_newnode->word,word);
    M_newnode->file_count = 1;
    M_newnode->sub_link = S_newnode;
    M_newnode->link = NULL;

    M_prev->link = M_newnode;
    return SUCCESS;
}

//-------------------------------------------------------------------------------------------------//