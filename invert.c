#include "invert.h"

//-------------------------------------------------------------------------------------------------//

void display_file(file_t *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("\nhead -> ");
    while(head!=NULL)
    {
        printf("%s -> ",head->fname);
        head = head->link;
    }
    printf("NULL\n");
}

//-------------------------------------------------------------------------------------------------//

int validate_arguments(char *argv[],file_t **files)
{
    for(int i=1;argv[i]!=0;i++)
    {
        char *dot=strrchr(argv[i],'.');
        if(strcmp(dot,".txt")!=0)
        {
            printf("[ ERROR ] %s file should be \".txt\" type\n",argv[i]);
            continue;
        }

        FILE *fptr = fopen(argv[i],"r");

        if(fptr == NULL)
        {
            fclose(fptr);
            printf("[ ERROR ] Unable to open %s file\n",argv[i]);
            continue;
        }
        if(fgetc(fptr)==EOF)
        {
            printf("[ ERROR ] %s is an empty file\n",argv[i]);
            continue;
        }
        if(isduplicate_file(argv[i], *files)==SUCCESS)
        {
            printf("[ ERROR ] File %s is already Exists\n",argv[i]);
            continue;
        }

        insert_file(files,argv[i]);
        fclose(fptr);
    }
    display_file(*files);
}

//-------------------------------------------------------------------------------------------------//

int Create_Database(file_t *files, mainnode_t *arr[])
{
    char word[size];
    while(files!=NULL)
    {
        FILE *fptr = fopen(files->fname,"r");
        if(fptr == NULL)
        {
            printf("[ ERROR ] Unable to open %s file\n",files->fname);
            files = files->link;
            continue;
        }
        while(fscanf(fptr,"%s",word) != EOF)
        {
            insert_word(files->fname,word,arr);
        }
        fclose(fptr);
        files = files->link;
    }
    return SUCCESS;
}

//-------------------------------------------------------------------------------------------------//

int Display_Database (mainnode_t *arr[])
{
    for(int i=0;i<27;i++)
    {
        if(arr[i] == NULL)
            continue;

        mainnode_t *M_temp = arr[i];
        while(M_temp!=NULL)
        {
            printf("%d\t%s\t%d\t",i,M_temp->word,M_temp->file_count);
            if(M_temp->sub_link!=NULL)
            {
                subnode_t *S_temp = M_temp->sub_link;
                while(S_temp!=NULL)
                {
                    printf("%s\t%d\t",S_temp->file_name,S_temp->word_count);
                    S_temp = S_temp->link;
                }
                printf("\n");
            }
            M_temp = M_temp->link;
        }
    }
}

//-------------------------------------------------------------------------------------------------//

int Search_Database(char *word, mainnode_t *arr[])
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
        printf("%s not found\n",word);
        return FAILURE;
    }
    mainnode_t *M_temp = arr[index];

    while(M_temp!=NULL)
    {
        if(strcmp(M_temp->word,word) == 0)
        {
            printf("\nWord %s is present in %d files\n",word,M_temp->file_count);
            if(M_temp->sub_link!=NULL)
            {
                subnode_t *S_temp = M_temp->sub_link;
                while(S_temp!=NULL)
                {
                    printf("In %s: %d times",S_temp->file_name,S_temp->word_count);
                    S_temp = S_temp->link;
                    if(S_temp!=NULL)
                        printf("\n");
                }
            }
        }
        M_temp = M_temp->link;
    }
    printf("\n");
    

}

//-------------------------------------------------------------------------------------------------//

int Update_Database()
{

}

//-------------------------------------------------------------------------------------------------//

int Save_Database(mainnode_t *arr[])
{
    FILE *fptr = fopen("Database.csv","w+");
    if(fptr == NULL)
    {
        printf("[ ERROR ] Unable to open Database.csv file\n");
        return FAILURE;
    }

    for(int i=0;i<27;i++)
    {
        if(arr[i] == NULL)
            continue;

        mainnode_t *M_temp = arr[i];
        while(M_temp!=NULL)
        {
            fprintf(fptr,"#%d;%s;%d;",i,M_temp->word,M_temp->file_count);
            if(M_temp->sub_link!=NULL)
            {
                subnode_t *S_temp = M_temp->sub_link;
                while(S_temp!=NULL)
                {
                    fprintf(fptr,"%s;%d;",S_temp->file_name,S_temp->word_count);
                    S_temp = S_temp->link;
                }
                fprintf(fptr,"#\n");
            }
            M_temp = M_temp->link;
        }
    }
    fclose(fptr);
    return SUCCESS;
}

//-------------------------------------------------------------------------------------------------//